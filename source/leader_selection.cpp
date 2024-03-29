// Leader selection
//
// Copyright (C) 2014 David Stone
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include "leader_selection.hpp"

#include <limits>
#include <random>
#include <vector>

#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/numeric.hpp>

#include "score.hpp"

namespace {

using Contenders = std::vector<std::reference_wrapper<Node>>;

void send_score(Contenders const & contenders, Score const my_score) {
	for (Node & contender : contenders) {
		contender.send(my_score);
	}
}

void send_claim(Contenders const & contenders, Claim const claim) {
	for (Node & contender : contenders) {
		contender.send(static_cast<std::uint8_t>(claim));
	}
}

bool lower_score_than_all_contenders(Contenders const & contenders, Score const my_score) {
	// This cannot break out early because we still have to clear the read
	// buffer for all of the contenders.
	//
	// TODO: consider making this asynchronous?
	if (contenders.empty()) {
		return true;
	}
	auto const least_score = [](Score const least, Node & node) { return std::min(least, node.receive<Score>()); };
	return my_score <= boost::accumulate(contenders, std::numeric_limits<Score>::max(), least_score);
}

bool received_claim(Contenders const & contenders, Claim const claim) {
	bool any_sent_claim = false;
	for (Node & node : contenders) {
		node.receive_claim();
		if (node.claim() == claim) {
			any_sent_claim = true;
		}
	}
	return any_sent_claim;
}

// TODO: Should this force a revote among all of my neighbors, or just those
// still considered contenders?
void handle_conflicting_leader_claims(Contenders const & contenders) {
	send_claim(contenders, Claim::force_revote);
	// We have to wait for all of our contenders to possibly also request a
	// revote so that we can ensure there are no timing issues. If we just sent
	// out our request for a revote, someone else may have done the same thing,
	// but we would take their revote request to be part of the next set of
	// messages. This keeps everything in sync, even though we don't care about
	// the result.
	received_claim(contenders, Claim::force_revote);
}

void remove_followers(Contenders & contenders) {
	boost::remove_erase_if(contenders, [](Node const & node) { return node.claim() == Claim::follower; });
}

}	// namespace

Claim leader_selection(std::vector<Node> & neighbors, std::mt19937 & random_engine) {
	using ScoreDistribution = std::uniform_int_distribution<Score>;
	ScoreDistribution distribution(std::numeric_limits<Score>::min(), std::numeric_limits<Score>::max());
	Contenders contenders(neighbors.begin(), neighbors.end());
	while (true) {
		Score const my_score = distribution(random_engine);
		send_score(contenders, my_score);
		bool const is_leader = lower_score_than_all_contenders(contenders, my_score);

		send_claim(contenders, is_leader ? Claim::leader : Claim::undecided);
		bool const is_follower = received_claim(contenders, Claim::leader);

		if (is_follower and is_leader) {
			handle_conflicting_leader_claims(contenders);
			continue;
		}
		// I cannot break out here because someone else may force a revote.
		send_claim(contenders, is_follower ? Claim::follower : Claim::undecided);
		bool const revote_requested = received_claim(contenders, Claim::force_revote);
		
		if (revote_requested) {
			continue;
		}
		if (is_leader) {
			return Claim::leader;
		} else if (is_follower) {
			return Claim::follower;
		} else {
			remove_followers(contenders);
		}
	}
}


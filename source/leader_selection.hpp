// Leader selection algorithm, adapted from
// http://dcg.ethz.ch/lectures/fs09/distcomp/lecture/mis.pdf
//
// Copyright (C) 2014 David Stone
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#ifndef ASIO_PEER_TO_PEER_LEADER_SELECTION_HPP
#define ASIO_PEER_TO_PEER_LEADER_SELECTION_HPP

#include <random>
#include <vector>

enum class Claim {
	leader, follower, undecided
};

class Node {
};

Claim leader_selection(std::vector<Node> & neighbors, std::mt19937 & random_engine);

#endif // ASIO_PEER_TO_PEER_LEADER_SELECTION_HPP

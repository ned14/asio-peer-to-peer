// A node in the peer-to-peer network
//
// Copyright (C) 2014 David Stone
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#ifndef ASIO_PEER_TO_PEER_NODE_HPP
#define ASIO_PEER_TO_PEER_NODE_HPP

#include <type_traits>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>

class Node {
public:
	Node(boost::asio::ip::tcp::socket socket):
		m_socket(std::move(socket)) {
	}
	template<typename T>
	void send(T const number) {
		static_assert(std::is_integral<T>::value, "Can only send integer values.");
		// TODO: endian conversions
		boost::asio::write(m_socket, boost::asio::buffer(&number, sizeof(number)));
	}
	
	template<typename T>
	T read() {
		static_assert(std::is_integral<T>::value, "Can only read integer values.");
		// TODO: endian conversions
		T value;
		boost::asio::read(m_socket, boost::asio::buffer(&value, sizeof(value)));
		return value;
	}
private:
	boost::asio::ip::tcp::socket m_socket;
};

#endif // ASIO_PEER_TO_PEER_NODE_HPP

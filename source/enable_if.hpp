// A slight simplification of std::enable_if, modified from
// http://flamingdangerzone.com/cxx11/2012/06/01/almost-static-if.html
//
// Copyright (C) 2014 David Stone
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#ifndef ASIO_PEER_TO_PEER_ENABLE_IF_HPP_
#define ASIO_PEER_TO_PEER_ENABLE_IF_HPP_

#include <type_traits>

#if 0

// Usage:
template<typename T, EnableIf<1 + 1 == 2>...>
void f() {
}

// Usage if you want to use a clang workaround:
template<typename T, EnableIf<1 + 1 == 2> = dummy>
void f() {
}

#endif

namespace detail {
enum class enabler {};
}	// namespace detail

constexpr detail::enabler dummy = {};
template<bool condition>
using EnableIf = typename std::enable_if<condition, detail::enabler>::type;

#endif // ASIO_PEER_TO_PEER_ENABLE_IF_HPP_

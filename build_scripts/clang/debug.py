# Debugging options
#
# Copyright (C) 2014 David Stone
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt

class debug:
	__generate_debug_symbols = '-g'
	compile_flags = [
		__generate_debug_symbols,
	]
	compile_flags_release = [
		__generate_debug_symbols,
	]

	link_flags = [
	]
	link_flags_release = [
	]


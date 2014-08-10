# Optimizations if building with clang
#
# Copyright (C) 2014 David Stone
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt

class optimize:
	compile_flags = [
		'-Ofast',
		'-march=native',
		'-fomit-frame-pointer',
	]

	link_flags = compile_flags

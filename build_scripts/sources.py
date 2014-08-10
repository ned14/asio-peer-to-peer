# List of sources
#
# Copyright (C) 2014 David Stone
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt

from program import Program

source_directory = 'source'

sources = [
	'main.cpp'	
]

programs = [
	Program(
		name = 'asio-peer-to-peer',
		sources = sources,
		libraries = [],
	),
]
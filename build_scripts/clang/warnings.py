# Warnings if building with clang
#
# Copyright (C) 2014 David Stone
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt

# -Wno-c++98-compat is used because I do not care about being compatible with
# old versions of the standard. I use -Wno-c++98-compat-pedantic because I still
# do not care.
#
# -Wno-exit-time-destructors warns about any static variable that has a
# destructor. I use a few static const variables, but they do not depend on each
# other for their destruction (or any global variable), so my usage is safe.
#
# -Wpadded is turned on occasionally to optimize the layout of classes, but it
# is not left on because not all classes have enough elements to remove padding
# at the end. In theory I could get some extra variables for 'free', but it's
# not worth the extra effort of maintaining that (if my class size changes,
# it's not easy to remove those previously free variables).
#
# -Wswitch-enum isn't behavior that I want. I don't want to handle every switch
# statement explicitly. It would be useful if the language had some mechanism
# to activate this on specified switch statements (to ensure that future
# changes to the enum are handled everywhere that they need to be), but it's
# overkill for an "all-or-nothing" setting.
#

warnings = [
	'-Weverything',
	'-Werror',
	'-Wno-c++98-compat',
	'-Wno-c++98-compat-pedantic',
	'-Wno-exit-time-destructors',
	'-Wno-padded',
	'-Wno-switch-enum',
	'-Wno-unused-member-function',
	'-Wno-unused',
	'-Wno-unused-parameter',
]

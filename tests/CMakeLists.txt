# Copyright (C) 2015 FourC AS, http://www.fourc.eu/
# All Rights Reserved.
#
# This file is part of PngChecker.
#
# PngChecker is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# PngChecker is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with PngChecker.  If not, see <http://www.gnu.org/licenses/>.

IF (NOT CMAKE_CROSSCOMPILING)
	if (BUILD_UNIT_TESTS OR BUILD_SYSTEM_TESTS)
		enable_testing()
    	add_subdirectory(gmock)
	endif (BUILD_UNIT_TESTS OR BUILD_SYSTEM_TESTS)
ENDIF (NOT CMAKE_CROSSCOMPILING)

if (BUILD_UNIT_TESTS)
    add_subdirectory(unittests)
endif (BUILD_UNIT_TESTS)

if (BUILD_SYSTEM_TESTS)
    add_subdirectory(systemtests)
endif (BUILD_SYSTEM_TESTS)

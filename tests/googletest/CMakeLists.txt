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

# This file configures Google Mocks as an external project to the PngChecker build,
# iff testing is enabled.

include(ExternalProject)

if (NOT CMAKE_GTEST_VERSION)
  SET(CMAKE_GTEST_VERSION "release-1.10.0" CACHE STRING "Google Test version")
  MESSAGE(STATUS "CMAKE_GTEST_VERSION not set. Defaulting to '${CMAKE_GTEST_VERSION}'")
endif ()

# Add googletest
ExternalProject_Add(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG ${CMAKE_GTEST_VERSION}
        TIMEOUT 30
        INSTALL_COMMAND ""
)

ExternalProject_Get_Property(googletest source_dir binary_dir)

SET(GMOCK_INCLUDE_DIR "${source_dir}/googlemock/include" CACHE STRING "GMock include directory")
SET(GTEST_INCLUDE_DIR "${source_dir}/googletest/include" CACHE STRING "GTest include directory")

SET(GTEST_INCLUDE_DIRS ${GMOCK_INCLUDE_DIR} ${GTEST_INCLUDE_DIR} CACHE STRING "GTest and GMock include directories")

SET(GMOCK_LIBRARY "${binary_dir}/lib/libgmock.a" CACHE STRING "GMock library")
SET(GTEST_LIBRARY "${binary_dir}/lib/libgtest.a" CACHE STRING "GTest library")
SET(GTEST_LIBRARIES ${GMOCK_LIBRARY} ${GTEST_LIBRARY} CACHE STRING "GTest libraries")

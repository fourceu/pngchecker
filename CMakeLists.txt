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


CMAKE_MINIMUM_REQUIRED (VERSION 2.8.2)

project(pngchecker CXX)

include (version.cmake)
SET (APPLICATION_NAME "${PROJECT_NAME}")
SET (APPLICATION_CODENAME "${PROJECT_NAME}")
SET (APPLICATION_COPYRIGHT_YEARS "2014")
SET (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}")
SET (APPLICATION_VENDOR_ID "eu.fourc")
SET (APPLICATION_VENDOR_NAME "FourC AS")
SET (APPLICATION_VENDOR_URL "fourc.eu")
SET (APPLICATION_ID "${APPLICATION_VENDOR_ID}.${PROJECT_NAME}")

option(BUILD_UNIT_TESTS "Include unit tests" ON)
option(BUILD_SYSTEM_TESTS "Include system tests" OFF)
option(BUILD_DOCUMENTATION "Generate the project documentation" OFF)
set(BUILD_GTEST_FILTER "" CACHE STRING "Filter GTest test names to be executed (glob expr)")

IF (UNIX)
    set(CMAKE_CXX_FLAGS "-Wextra -Wall -Werror -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -pedantic -std=c++11 -DBOOST_LOG_DYN_LINK")
ENDIF (UNIX)


FIND_PACKAGE(Boost 1.54 COMPONENTS log regex REQUIRED)

set(${PROJECT_NAME}_LIBS ${Boost_LIBRARIES})

set(${PROJECT_NAME}_LIB_SRCS
  src/fourc/graphics/pngchecker/PngChecker.cxx
  src/fourc/graphics/pngchecker/PngCheckerException.cxx
  src/fourc/graphics/pngchecker/PngDataChunk.cxx
  src/fourc/graphics/pngchecker/PngHeaderChunk.cxx
)

INCLUDE_DIRECTORIES(include)

ADD_LIBRARY(${PROJECT_NAME} ${${PROJECT_NAME}_LIB_SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
	VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}"
	OUTPUT_NAME ${PROJECT_NAME}
	CLEAN_DIRECT_OUTPUT 1)

if (BUILD_DOCUMENTATION)
    ADD_SUBDIRECTORY(doc)
endif ()
ADD_SUBDIRECTORY(tests)

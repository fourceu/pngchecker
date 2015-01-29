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

project(systemtests CXX)

include_directories("../../src" ${CMAKE_CURRENT_BINARY_DIR} ${GTEST_BOTH_INCLUDE_DIRS})

FILE (GLOB_RECURSE test_SRCS *.cxx)

ADD_EXECUTABLE(${PROJECT_NAME} ${test_SRCS})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
add_dependencies(${PROJECT_NAME} googlemock)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CMAKE_PROJECT_NAME} ${${CMAKE_PROJECT_NAME}_LIBS} ${GMOCK_LIBRARY} pthread)

if (BUILD_GTEST_FILTER)
    SET(GTEST_FILTER --gtest_filter=${BUILD_GTEST_FILTER}) 
endif ()

# Example .png file
set(EXAMPLE_PNG_FILE "${CMAKE_CURRENT_BINARY_DIR}/example.png")
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/example.png" ${EXAMPLE_PNG_FILE} COPYONLY)
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/SystemTestConstantsGenerated.h.in" "${CMAKE_CURRENT_BINARY_DIR}/SystemTestConstantsGenerated.h")

ADD_CUSTOM_TARGET(systemtest
    COMMAND "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX}" "--gtest_output=xml"	
    ${GTEST_FILTER}
    DEPENDS ${PROJECT_NAME} googlemock
    COMMENT "Executing system tests..."
    VERBATIM SOURCES ${test_SRCS})

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

project(unittests CXX)

# Set the target name policy to allow the reserved target name "test" to be used
if (POLICY CMP0037)
    message(STATUS "Setting target name policy to OLD (allowing use of reserved target names)")
    cmake_policy(SET CMP0037 OLD)
endif ()

IF (NOT CMAKE_CROSSCOMPILING)
    include_directories("../../src/" "../../include" ${GTEST_INCLUDE_DIRS})

    FILE (GLOB_RECURSE test_SRCS *.cxx)

    ADD_EXECUTABLE(${PROJECT_NAME} ${test_SRCS})
    SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
    add_dependencies(${PROJECT_NAME} googletest)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CMAKE_PROJECT_NAME} ${${CMAKE_PROJECT_NAME}_LIBS} ${GTEST_LIBRARIES} pthread
    )

    if (BUILD_GTEST_FILTER)
        SET(GTEST_FILTER --gtest_filter=${BUILD_GTEST_FILTER})
    endif ()

    ADD_CUSTOM_TARGET(test "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX}"
        --gtest_output=xml
        ${GTEST_FILTER}
        DEPENDS ${PROJECT_NAME}
        COMMENT "Executing unit tests..."
        VERBATIM SOURCES ${test_SRCS})
ENDIF (NOT CMAKE_CROSSCOMPILING)

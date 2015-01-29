// Copyright (C) 2015 FourC AS, http://www.fourc.eu/
// All Rights Reserved.
//
// This file is part of PngChecker.
//
// PngChecker is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// PngChecker is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with PngChecker.  If not, see <http://www.gnu.org/licenses/>.

/**
 * Implements a main() method for a unit testing process
 */

#include <gtest/gtest.h>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>

int main(int argc, char **argv) {
  boost::log::core::get()->set_filter(
      boost::log::trivial::severity >= boost::log::trivial::info);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

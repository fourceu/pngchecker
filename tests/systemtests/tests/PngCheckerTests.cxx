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

#include <gmock/gmock.h>

#include "../SystemTestConstants.h"

#include <fourc/graphics/pngchecker/PngChecker.h>

#include <fstream>

using namespace fourc::graphics::pngchecker;

TEST(PngCheckerTests, readRealPng) {
  std::ifstream ifs(fourc::graphics::pngchecker::testing::EXAMPLE_PNG_FILE_NAME);

  PngChecker pngChecker;
  pngChecker.verifyPng(ifs);

  ifs.close();
}

TEST(PngCheckerTests, readRealPngVector) {
  std::ifstream ifs(fourc::graphics::pngchecker::testing::EXAMPLE_PNG_FILE_NAME);
  ifs.seekg(0, std::ios::end);
  std::streampos length(ifs.tellg());
  std::vector<char> data;
  if (length) {
    ifs.seekg(0, std::ios::beg);
      data.resize(static_cast<std::size_t>(length));
      ifs.read(&data.front(), static_cast<std::size_t>(length));
  }

  ifs.close();

  PngChecker pngChecker;
  pngChecker.verifyPng(data);
}

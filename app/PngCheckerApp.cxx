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

#include <fourc/graphics/pngchecker/PngChecker.h>
#include <fourc/graphics/pngchecker/PngCheckerException.h>

#include <fstream>
#include <iostream>

using namespace fourc::graphics::pngchecker;

int main(int argc, char** argv) {
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    if (ifs.good()) {
      try {
        PngChecker checker;
        checker.verifyPng(ifs);

        return 0;
      } catch (const PngCheckerException& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
      }
    } else {
      std::cout << "Could not read input file: " << argv[1] << std::endl;
      return 2;
    }
  } else {
    std::cout << "Usage:" << std::endl;
    std::cout << "pngchecker <png file>" << std::endl;
    return 2;
  }

  return 3; // Shouldn't arrive here but we'll add it for safety
}

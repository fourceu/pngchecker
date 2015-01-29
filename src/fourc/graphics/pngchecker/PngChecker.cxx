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
#include "PngHeaderChunk.h"
#include "PngDataChunk.h"

#include <vector>

namespace fourc {
namespace graphics {
namespace pngchecker {

void PngChecker::verifyPng(DataType& data) {
  // Verify header
  PngHeaderChunk header(data);

  // Read all chunks, verifying length and checksum
  std::vector<PngDataChunk> chunks;
  while (data.eof()) {
    chunks.push_back(PngDataChunk(data));

    data.peek(); // Triggers EOF (WHY?! :( )
  }

  // TODO: Verify that all critical sections are present
}

}}} // Namespaces

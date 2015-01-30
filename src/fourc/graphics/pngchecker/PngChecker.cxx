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

#include "PngHeaderChunk.h"
#include "PngDataChunk.h"
#include "PngChunkNames.h"

#include <sstream>
#include <iostream>

namespace fourc {
namespace graphics {
namespace pngchecker {

void PngChecker::verifyPng(DataType& data) {
  // Verify header
  PngHeaderChunk header(data);

  // Read all chunks, verifying length and checksum
  std::vector<PngDataChunk> chunks;
  data.peek(); // Triggers EOF (WHY?! :( )
  while (!data.eof()) {
    chunks.push_back(PngDataChunk(data));

    data.peek(); // Triggers EOF (WHY?! :( )
  }

  // Verify that all critical sections are present

  // IHDR
  if (chunks.empty()) {
    throw PngCheckerException("No data chunks found");
  }
  PngDataChunk ihdr = chunks.at(0);
  if (ihdr.getType() != PngChunkNames::IHDR) {
    throw PngCheckerException("First data chunk should have been type IHDR but was " + ihdr.getType());
  }

  // PLTE
  // From Wikipedia: The PLTE chunk is essential for color type 3 (indexed color). It is optional for color types 2 and 6 (truecolor and truecolor with alpha)
  // and it must not appear for color types 0 and 4 (grayscale and grayscale with alpha).

  // TODO: Need to interpret IHDR chunk more to decide whether PLTE chunk should exist

  // There should be at least one IDAT chunk
  bool foundIDAT = false;
  for (PngDataChunk idat : chunks) {
    if (idat.getType() == PngChunkNames::IDAT) {
      foundIDAT = true;
      break;
    }
  }
  if (!foundIDAT) {
    throw PngCheckerException("No IDAT chunks found");
  }

  // IEND
  PngDataChunk iend = chunks.at(chunks.size() -1);
  if (iend.getType() != PngChunkNames::IEND) {
    throw PngCheckerException("Last data chunk should have been type IEND but was " + iend.getType());
  }
}

void PngChecker::verifyPng(const std::vector<char>& data) {
  // Create a char buffer backed pair of in/out streams
  std::stringbuf buf;
  std::ostream os(&buf);
  std::istream is(&buf);

  // Write data to buffer
  os.write(data.data(), data.size());

  verifyPng(is);
}

}}} // Namespaces

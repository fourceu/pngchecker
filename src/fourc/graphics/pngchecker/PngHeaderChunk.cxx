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

#include "PngHeaderChunk.h"
#include <fourc/graphics/pngchecker/PngCheckerException.h>

#include <vector>

namespace fourc {
namespace graphics {
namespace pngchecker {

constexpr unsigned char PngHeaderChunk::VALID_PNG_HEADER[HEADER_LENGTH];

PngHeaderChunk::PngHeaderChunk(DataType& data) {
  // Convert header bytes to a vector of signed chars
  const DataType::char_type* signed_header = reinterpret_cast<const DataType::char_type*>(VALID_PNG_HEADER);
  std::vector<DataType::char_type> valid_header(signed_header, signed_header + HEADER_LENGTH);

  // Read header bytes from input stream to vector
  std::vector<DataType::char_type> header_chunk(HEADER_LENGTH);
  data.read(header_chunk.data(), HEADER_LENGTH);
  if (!data) {
    throw PngCheckerException("Truncated header");
  }

  // Verify input stream matches header bytes
  if (header_chunk != valid_header) {
    throw PngCheckerException("Invalid header");
  }
}

size_t PngHeaderChunk::getLength() const {
  return HEADER_LENGTH;
}

}}} // Namespaces

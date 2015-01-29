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

#include "PngDataChunk.h"
#include <fourc/graphics/pngchecker/PngCheckerException.h>

#include <boost/crc.hpp>

#include <iostream>
#include <algorithm>
#include <cstring> // std::memcpy

namespace fourc {
namespace graphics {
namespace pngchecker {

PngDataChunk::PngDataChunk(DataType& data) {
  // Read length bytes from input stream to vector
  length = getChunkLength(data);

  // Read chunk body
  std::vector<DataType::char_type> body = getChunkBody(data);

  // Verify CRC
  verifyCRC(body);

  // get chunk type
  type = getChunkType(body);
}

size_t PngDataChunk::getLength() const {
  return length;
}

uint32_t PngDataChunk::getChunkLength(DataType& data) const {
  uint32_t length = 0;
  data.read(reinterpret_cast<char*>(&length), sizeof(uint32_t));

  if (!data) {
    std::cout << "Truncated chunk: read only " << data.gcount() << " bytes instead of 4" << std::endl;
    throw PngCheckerException("Truncated chunk length field");
  }

  // Correct enidanness
  reverseBytesInPlace(length);

  return length;
}

std::vector<DataType::char_type> PngDataChunk::getChunkBody(DataType& data) const {
  uint32_t bytesToRead = length + 2 * sizeof(uint32_t); // Chunk type and CRC fields

  std::vector<DataType::char_type> chunk_body(bytesToRead);
  data.read(chunk_body.data(), bytesToRead);

  if (!data) {
    throw PngCheckerException("Truncated chunk body");
  }

  return chunk_body;
}

std::string PngDataChunk::getChunkType(std::vector<DataType::char_type>& chunkBody) const {
  uint32_t type;

  std::memcpy(&type, chunkBody.data(), sizeof(uint32_t));

  std::string type_str(reinterpret_cast<char*>(&type), sizeof(uint32_t));

  return type_str;
}

void PngDataChunk::verifyCRC(std::vector<DataType::char_type>& chunkBody) const {
  // Build a new vector not including the final checksum bytes
  std::vector<DataType::char_type> data(chunkBody.begin(), chunkBody.end() - sizeof(uint32_t));

  // Read the stated CRC from the body
  uint32_t stated_crc;
  std::memcpy(&stated_crc, chunkBody.data() + chunkBody.size() - sizeof(uint32_t), sizeof(uint32_t));

  // Correct endianness
  reverseBytesInPlace(stated_crc);

  // Compute CRC of remaining data
  boost::crc_32_type crc_computer;
  crc_computer.process_bytes(data.data(), data.size());
  uint32_t crc = crc_computer.checksum();

  // Verify computed and stated CRC match
  if (stated_crc != crc) {
    throw PngCheckerException("CRC mismatch on data chunk");
  }
}

}}} // Namespaces

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

#include <fourc/graphics/pngchecker/PngDataChunk.h>
#include <fourc/graphics/pngchecker/PngCheckerException.h>

#include <boost/crc.hpp>

#include <vector>
#include <sstream>
#include <iostream>

using namespace fourc::graphics::pngchecker;

template<typename T> void reverseBytesInPlace(T& value) {
  char* start = reinterpret_cast<char*>(&value);
  std::reverse(start, start + sizeof(T));
}

template<typename T> T reverseBytesValue(const T& value) {
  T reversed = value; // Take a copy so we don't pervert the original

  reverseBytesInPlace(reversed);

  return reversed;
}

// Convenience method to construct (hopefully) valid png chunks
void writePngChunk(std::ostream& os, const std::string& type, DataType::char_type* data, uint32_t data_len);
void writePngChunk(std::ostream& os, const std::string& type, DataType::char_type* data, uint32_t data_len) {
    uint32_t length_reversed = reverseBytesValue(data_len);

  // Compute CRC
  boost::crc_32_type crc_computer;
  crc_computer.process_bytes(type.c_str(), type.size());
  crc_computer.process_bytes(data, data_len);
  uint32_t crc = crc_computer.checksum();

  uint32_t crc_reversed = reverseBytesValue(crc);

  os.write(reinterpret_cast<char*>(&length_reversed), sizeof(uint32_t));
  os.write(type.c_str(), type.size());
  os.write(data, data_len);
  os.write(reinterpret_cast<char*>(&crc_reversed), sizeof(uint32_t));
}

TEST(PngDataChunkTests, readTrivialBlock) {

  std::stringbuf buf;
  std::ostream os(&buf);
  std::istream is(&buf);

  char data[3]{0x00, 0x00, 0x01};
  writePngChunk(os, "IHDR", data, 3);

  // This would throw an exception if anything went wrong - no other test verification required.
  PngDataChunk chunk(is);
}

TEST(PngDataChunkTests, readIHDRBlock) {

  std::stringbuf buf;
  std::ostream os(&buf);
  std::istream is(&buf);

  const uint32_t length = 13;

  unsigned char data[length]{
    0x00, 0x00, 0x00, 0xE9, // width
    0x00, 0x00, 0x00, 0x58, // height
    0x08, 0x02, 0x00, 0x00, // bit depth
    0x00                    // colour type
  };
  writePngChunk(os, "IHDR", reinterpret_cast<char*>(data), length);

  // This would throw an exception if anything went wrong - no other test verification required.
  PngDataChunk chunk(is);
}

TEST(PngDataChunkTests, getLength) {

  std::stringbuf buf;
  std::ostream os(&buf);
  std::istream is(&buf);

  const uint32_t length = 13;

  unsigned char data[length]{
    0x00, 0x00, 0x00, 0xE9, // width
    0x00, 0x00, 0x00, 0x58, // height
    0x08, 0x02, 0x00, 0x00, // bit depth
    0x00                    // colour type
  };
  writePngChunk(os, "IHDR", reinterpret_cast<char*>(data), length);

  PngDataChunk chunk(is);

  EXPECT_EQ(length, chunk.getLength());
}

TEST(PngDataChunkTests, getType) {

  std::stringbuf buf;
  std::ostream os(&buf);
  std::istream is(&buf);

  const uint32_t length = 13;
  std::string type = "IHDR";

  unsigned char data[length]{
    0x00, 0x00, 0x00, 0xE9, // width
    0x00, 0x00, 0x00, 0x58, // height
    0x08, 0x02, 0x00, 0x00, // bit depth
    0x00                    // colour type
  };
  writePngChunk(os, type, reinterpret_cast<char*>(data), length);

  PngDataChunk chunk(is);

  EXPECT_EQ(type, chunk.getType());
}


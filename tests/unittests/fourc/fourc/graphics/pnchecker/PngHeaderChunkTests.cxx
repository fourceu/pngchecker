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

#include <fourc/graphics/pngchecker/PngHeaderChunk.h>
#include <fourc/graphics/pngchecker/PngCheckerException.h>

#include <vector>
#include <sstream>
#include <iostream>

using namespace fourc::graphics::pngchecker;

const size_t HEADER_LENGTH = 8;
const unsigned char VALID_PNG_HEADER[HEADER_LENGTH]{0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
const unsigned char INVALID_PNG_HEADER[HEADER_LENGTH]{0x89, 0x50, 0x4E, 0x47, 0x0D, 0x10, 0x1A, 0x0A};
const unsigned char TRUNCATED_PNG_HEADER[HEADER_LENGTH]{0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A};

TEST(PngHeaderChunkTests, readHeaderChunk) {
  const char * array = reinterpret_cast<const char*>(VALID_PNG_HEADER);

  std::stringbuf buf;
  std::ostream os(&buf);
  std::istream is(&buf);

  os << array;

  PngHeaderChunk header(is);
}

TEST(PngHeaderChunkTests, readHeaderChunkExtendedStream) {
  const char * array = reinterpret_cast<const char*>(VALID_PNG_HEADER);

  std::stringbuf buf;
  std::ostream os(&buf);
  std::istream is(&buf);

  for (int i = 0; ++i < 10;)
    os << array;

  PngHeaderChunk header(is);

  // Verify the correct number of bytes were read
  EXPECT_EQ(static_cast<signed>(HEADER_LENGTH), is.tellg());
}

TEST(PngHeaderChunkTests, readHeaderChunkTruncatedStream) {
  const char * array = reinterpret_cast<const char*>(TRUNCATED_PNG_HEADER);

  std::stringbuf buf;
  std::ostream os(&buf);
  std::istream is(&buf);

  os << array;

  try {
    PngHeaderChunk header(is);

    FAIL() << "Expected exception not thrown";
  } catch (PngCheckerException& expected) {
    EXPECT_STREQ("Truncated header", expected.what());
  }
}

TEST(PngHeaderChunkTests, readInvalidHeaderChunk) {
  const char * array = reinterpret_cast<const char*>(INVALID_PNG_HEADER);

  std::stringbuf buf;
  std::ostream os(&buf);
  std::istream is(&buf);

  os << array;

  try {
    PngHeaderChunk header(is);

    FAIL() << "Expected exception not thrown";
  } catch (PngCheckerException& expected) {
    EXPECT_STREQ("Invalid header", expected.what());
  }
}

TEST(PngHeaderChunkTests, getLength) {

  const char * array = reinterpret_cast<const char*>(VALID_PNG_HEADER);

  std::stringbuf buf;
  std::ostream os(&buf);
  std::istream is(&buf);

  os << array;

  PngHeaderChunk header(is);

  EXPECT_EQ(HEADER_LENGTH, header.getLength());
}

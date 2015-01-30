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

#ifndef SRC_FOURC_GRAPHICS_PNGCHECKER_PNGHEADERCHUNK_H_
#define SRC_FOURC_GRAPHICS_PNGCHECKER_PNGHEADERCHUNK_H_

#include "PngChunk.h"
#include <fourc/graphics/pngchecker/PngDataType.h>

namespace fourc {
namespace graphics {
namespace pngchecker {

/**
 * \brief Reads an 8-byte header chunk from a png data stream
 *
 * From http://en.wikipedia.org/wiki/Portable_Network_Graphics#File_header:
 * 89  Has the high bit set to detect transmission systems that do not support 8 bit data and to reduce the chance that a text file is mistakenly interpreted as a PNG, or vice versa.
 * 50 4E 47  In ASCII, the letters PNG, allowing a person to identify the format easily if it is viewed in a text editor.
 * 0D 0A A DOS-style line ending (CRLF) to detect DOS-Unix line ending conversion of the data.
 * 1A  A byte that stops display of the file under DOS when the command type has been used—the end-of-file character
 * 0A  A Unix-style line ending (LF) to detect Unix-DOS line ending conversion.
 *
 */
class PngHeaderChunk : public PngChunk {
public:
  static const uint32_t HEADER_LENGTH = 8;
  static constexpr unsigned char VALID_PNG_HEADER[HEADER_LENGTH]{0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

  PngHeaderChunk(DataType& data);
  virtual ~PngHeaderChunk() = default;

  virtual uint32_t getLength() const;
};

}}} // Namespaces

#endif /* SRC_FOURC_GRAPHICS_PNGCHECKER_PNGHEADERCHUNK_H_ */

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

#ifndef SRC_FOURC_GRAPHICS_PNGCHECKER_PNGDATACHUNK_H_
#define SRC_FOURC_GRAPHICS_PNGCHECKER_PNGDATACHUNK_H_

#include "PngChunk.h"
#include <fourc/graphics/pngchecker/PngDataType.h>

#include <vector>
#include <algorithm>

namespace fourc {
namespace graphics {
namespace pngchecker {

/**
 * \brief Reads variable-length data chunks from a png data stream, also verifying stated an actual chunk CRC.
 */
class PngDataChunk : public PngChunk {
public:
  PngDataChunk(DataType& data);
  virtual ~PngDataChunk() = default;

  virtual uint32_t getLength() const;
  virtual std::string getType() const;

protected:
  uint32_t length;
  std::string type;

  uint32_t getChunkLength(DataType& data) const;
  std::vector<DataType::char_type> getChunkBody(DataType& data) const;
  std::string getChunkType(std::vector<DataType::char_type>& chunkBody) const;
  void verifyCRC(std::vector<DataType::char_type>& chunkBody) const;

  /**
   * \brief Reverses bytes of any type for endian corrections
   */
  template<typename T> T reverseBytesValue(const T& value) const {
    T reversed = value; // Take a copy so we don't corrupt the original

    reverseBytesInPlace(reversed);

    return reversed;
  }
  template<typename T> void reverseBytesInPlace(T& value) const {
    char* start = reinterpret_cast<char*>(&value);
    std::reverse(start, start + sizeof(T));
  }
};

}}} // Namespaces

#endif /* SRC_FOURC_GRAPHICS_PNGCHECKER_PNGDATACHUNK_H_ */

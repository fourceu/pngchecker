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

#ifndef SRC_FOURC_GRAPHICS_PNGCHECKER_PNGCHUNK_H_
#define SRC_FOURC_GRAPHICS_PNGCHECKER_PNGCHUNK_H_

#include <cstdint>

namespace fourc {
namespace graphics {
namespace pngchecker {

/**
 * \brief Abstract base class for all Png data chunks (including the initial header bytes)
 */
class PngChunk {
public:
  PngChunk() = default;
  virtual ~PngChunk() = default;

  /**
   * Chunk length, either a constant according to the specification or a dynamic length read from the data.
   */
  virtual uint32_t getLength() const = 0;
};

}}} // Namespaces

#endif /* SRC_FOURC_GRAPHICS_PNGCHECKER_PNGCHUNK_H_ */

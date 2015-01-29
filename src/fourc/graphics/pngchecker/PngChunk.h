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

#include <cstddef>

namespace fourc {
namespace graphics {
namespace pngchecker {

class PngChunk {
public:
  PngChunk() = default;
  virtual ~PngChunk() = default;

  virtual size_t getLength() const = 0;
};

}}} // Namespaces

#endif /* SRC_FOURC_GRAPHICS_PNGCHECKER_PNGCHUNK_H_ */

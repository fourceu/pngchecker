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

#ifndef SRC_FOURC_GRAPHICS_PNGCHECKER_PNGCHUNKNAMES_H_
#define SRC_FOURC_GRAPHICS_PNGCHECKER_PNGCHUNKNAMES_H_

#include <string>

namespace fourc {
namespace graphics {
namespace pngchecker {

/**
 * \brief String constants for the names of the Png data chunks
 * Chunk names are case-sensitive: the first letter of the chunk name denotes whether it is a critical chunk
 * (upper case)(must be supported by decoders) or an ancillary chunk (lower case).
 *
 */
class PngChunkNames {
public:
  // Critical chunks
  static const std::string IHDR;
  static const std::string PLTE;
  static const std::string IDAT;
  static const std::string IEND;

  // Ancillary chunks
};

}}} // Namespaces

#endif /* SRC_FOURC_GRAPHICS_PNGCHECKER_PNGCHUNKNAMES_H_ */

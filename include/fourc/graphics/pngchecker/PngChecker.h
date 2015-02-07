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

#ifndef FOURC_GRAPHICS_PNGCHECKER_PNGCHECKER_H_
#define FOURC_GRAPHICS_PNGCHECKER_PNGCHECKER_H_

#include "PngDataType.h"

#include <vector>

namespace fourc {
namespace graphics {
namespace pngchecker {

class PngDataChunk;

class PngChecker {
public:
  PngChecker() = default;
  virtual ~PngChecker() = default;

  /**
   * \brief Reads and verifies Png data from a stream.
   */
  void verifyPng(DataType& data);

  /**
   * \brief Convenience overload. Wraps the given vector in a stream and defers to stream overload.
   *
   * \throws PngCheckerException if any problems are found with the Png data stream.
   *
   */
  void verifyPng(const std::vector<char>& data);

  /**
   * \brief Locates a chunk of the given name in the list read from the data stream.
   * Used internally but left with public accessibility in case it could be useful elsewhere.
   *
   * \note The pointer returned remains owned by the PngCheck instance. Do not modify.
   */
  const PngDataChunk* findChunk(std::vector<PngDataChunk>& chunks, const std::string& chunkName);
};

}}} // Namespaces

#endif // FOURC_GRAPHICS_PNGCHECKER_PNGCHECKER_H_

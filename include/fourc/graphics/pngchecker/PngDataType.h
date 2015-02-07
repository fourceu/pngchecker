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

#include <istream>

#ifndef FOURC_GRAPHICS_PNGCHECKER_PNGDATATYPE_H_
#define FOURC_GRAPHICS_PNGCHECKER_PNGDATATYPE_H_

namespace fourc {
namespace graphics {
namespace pngchecker {

/**
 * \brief Defines the data type used to provide a Png data stream to the checker.
 */
typedef std::istream DataType;

}}} // Namespaces

#endif // FOURC_GRAPHICS_PNGCHECKER_PNGDATATYPE_H_

# pngchecker
C++ png data validation library

This project is designed to give easy access to the following features:
* Programatically verify the validity of png headers and data blocks
* Verify that certain mandatory data blocks are present in the stream
* Operate on storage-agnostic structures (currently supported: ```std::istream``` and ```std::vector<char>```)

Project priorities include:
* Easy to integrate with CMake projects (eg: via the ExternalProjects module)
* Minimal dependencies (requires c++-11 compiler and boost:crc)

The following CMakeLists.txt example can be used to pull pngchecker from this repository and make its include dirs and link library available by setting the PNGCHECKER_INCLUDE_DIRS and PNGCHECKER_LIBRARY vaiables (note that this will currently link statically which may have licensing implications).
```cmake
include(ExternalProject)

# Add pngchecker
ExternalProject_Add(
    pngchecker
    GIT_REPOSITORY https://github.com/fourceu/pngchecker.git
    TIMEOUT 30
    CMAKE_ARGS "-DBUILD_UNIT_TESTS=off" # Don't pull gtest into the pngchecker build
    UPDATE_COMMAND "" # Don't keep updating
    INSTALL_COMMAND ""
    )
    
ExternalProject_Get_Property(pngchecker source_dir binary_dir)

SET(PNGCHECKER_INCLUDE_DIRS "${source_dir}/include" CACHE STRING "PngChecker include directory")

SET(PNGCHECKER_LIBRARY "${binary_dir}/libpngchecker.a" CACHE STRING "PngChecker library")
```

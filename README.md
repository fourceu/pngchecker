# pngchecker
Png data validation library

This project is designed to give easy access to the following features:
* Programatically verify the validity of png headers and data blocks
* Verify that certain mandatory data blocks are present in the stream
* Operate on storage-agnostic structures (currently supported: std::istream and std::vector<char>)
Project priorities include:
* Easy to integrate with CMake projects (eg: via the ExternalProjects module)
* Minimal dependencies (requires c++-11 compiler and boost:crc)

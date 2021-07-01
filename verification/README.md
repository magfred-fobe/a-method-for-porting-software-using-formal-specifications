# Verification Tests

This directory conains the source for the library tests, or "agnostic tests", since they can be run on any implementation as long as it is a subclass of "LinkedList" \
There are 3 library implementationsm, they will be built by CMake automatically and linked into the project.
- Clib: A standalone library with the original C source code.
- RustLib: A vector backed version of the linked list in Rust.
- RustLib_Uns: A reference based version of the linked list library in Rust.

##### Prerequisites
- cargo 
- cbindgen

Directory structure \
└─/ - scripts, cmake root \
&nbsp;&nbsp;&nbsp;&nbsp;├─lib - generated libraries \
&nbsp;&nbsp;&nbsp;&nbsp;├─src - A copy of the C source code \
&nbsp;&nbsp;&nbsp;&nbsp;├─test - test \
&nbsp;&nbsp;&nbsp;&nbsp;└───lib_impl - library interface, library wrappers: rust, rust, and c

CMake instructions:
```
$ mkdir build && cd build
$ cmake ..
$ make
$ ./verification_test
```
This should download the dependencies gtest and rapidcheck and build the project.

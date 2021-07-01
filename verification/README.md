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

#### CLion instructions
- Press run ▶️

#### Manual CMake instructions:
```
$ mkdir build && cd build
$ cmake ..
$ make
$ ./verification_test
```


#### Note 
The tests only run on one library at a time, and needs a recompile to change the target.\
Available targets are: 
- RustLib: vector backed Rust implementation
- RustLib_Uns: reference based Rust implementation
- Clib: Reference C library
```
lib_agnostic_SLIST_test.cpp:
...
18: using CurListType = LIBRARY_NAME;
...
```

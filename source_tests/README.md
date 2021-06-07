This directory conains the source of the queue structure and the property based tests \
The tests can be built and run using CMake. If you are using CLion, the project can be built and run by pressing "run".

The directory also contains the verification tests that runs on the linkable binaries. These are built when making the project and \
tests also run when building it. Therefore 

- cargo 
- cbindgen

Are prerquisites for building the project.

Directory structure \
└─/ - scripts, cmake root \
&nbsp;&nbsp;&nbsp;&nbsp;├─lib - generated libraries \
&nbsp;&nbsp;&nbsp;&nbsp;├─src - source implementation and C-library source \
&nbsp;&nbsp;&nbsp;&nbsp;├─test - test implementations \
&nbsp;&nbsp;&nbsp;&nbsp;└───lib_impl - library interface, library wrappers: rust, rust, and c

CMake instructions:

$ mkdir build && cd build \
$ cmake .. \
$ make

This should download the dependencies gtest and rapidcheck and build the project.


To generate coverage report:

If using CLion:\
$ ./coverage_report.sh

Otherwise \
First run the executable once to generate coverage data, then:

$ cd build/CMakeFiles/project.dir/src \
$ gcov queue_impl.cpp.gcno \
$ lcov --capture --directory .  --rc lcov_branch_coverage=1 --output-file gtest_coverage.info \
$ genhtml gtest_coverage.info --branch-coverage --output-directory ../../../../COVERAGE_VIEW 

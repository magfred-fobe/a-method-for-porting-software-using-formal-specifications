# II142X_exjobb_project

This repository includes the tests and the formal specification derived from them of the freeBSD queue.h code. 

The test code is located in source_tests. The tests can be built and run using CMake. If you are using CLion, the project can be built and run by pressing "run".


CMake instructions:

$ mkdir build && cd build \
$ cmake .. \
$ make

To generate coverage report:

If using CLion:\
$ ./coverage_report.shj

Otherwise

$ cd build/CMakeFiles/project.dir/src \
$ gcov queue_impl.cpp.gcno \
$ lcov --capture --directory .  --rc lcov_branch_coverage=1 --output-file gtest_coverage.info \
$ genhtml gtest_coverage.info --branch-coverage --output-directory ../../../../COVERAGE_VIEW 

This should download the dependencies gtest and rapidcheck and build the project.

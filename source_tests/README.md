# Source Tests 

This directory conains the source of the queue structure and the property based tests \
The purpose of the tests is to ascertain the actual behaviour of the source code, as a basis for the formal specification.
The tests can be built and run using CMake. If you are using CLion, the project can be built and run by pressing "run".

#### Directory structure \
└─/ - scripts, cmake root \
&nbsp;&nbsp;&nbsp;&nbsp;├─src - source implementation and C-library source \
&nbsp;&nbsp;&nbsp;&nbsp;└─test - test implementations \

#### Running:
##### Using CLion:
- Press run ▶️

Generate coverage report
```
$ ./coverage_report.sh
```

##### Using CMake manually:
Build and run:
```
$ mkdir build && cd build
$ cmake ..
$ make
$ ./project
```
Generate coverage report
```
$ cd build/CMakeFiles/project.dir/src
$ gcov queue_impl.cpp.gcno
$ lcov --capture --directory . --rc lcov_branch_coverage=1 --output-file gtest_coverage.info
$ genhtml gtest_coverage.info --branch-coverage --output-directory ../../../../COVERAGE_VIEW
```


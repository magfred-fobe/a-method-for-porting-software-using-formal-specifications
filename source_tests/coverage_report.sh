#!/bin/bash

STARTDIR=$(pwd)

cd cmake-build-debug/CMakeFiles/project.dir/src
gcov queue_impl.cpp.gcno
lcov --capture --directory .  --rc lcov_branch_coverage=1 --output-file gtest_coverage.info
genhtml gtest_coverage.info --branch-coverage --output-directory ../../../../COVERAGE_VIEW
cd $STARTDIR
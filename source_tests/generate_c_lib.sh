#!/bin/sh
WORKING_DIR=$(pwd)
C_SOURCE_PATH="src/clibsrc/"
C_SOURCE_BASE_FILENAME="singly_linked_list_c"
C_LIB_FILENAME="libsingly_linked_list_c.a"
INTERMEDIATE_OUTPUT_DIR="tmp"
mkdir -p lib
cd ${C_SOURCE_PATH}
mkdir -p ${INTERMEDIATE_OUTPUT_DIR}
echo "Building c library"
g++ -c ${C_SOURCE_BASE_FILENAME}.cpp
ar rvs ${C_LIB_FILENAME} ${C_SOURCE_BASE_FILENAME}.o
mv ${C_LIB_FILENAME} ../../lib/
rm ${C_SOURCE_BASE_FILENAME}.o
cd ${WORKING_DIR}
echo "Done"
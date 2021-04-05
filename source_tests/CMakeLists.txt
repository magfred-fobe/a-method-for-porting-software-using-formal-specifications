cmake_minimum_required(VERSION 3.17)

# Enable coverage
set(CMAKE_CXX_FLAGS --coverage)

# Download and unpack googletest
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)


# Add the source and test files
add_executable(project test/SLIST_test.cpp test/STAILQ_test.cpp src/queue.h src/queue_impl.h src/queue_impl.cpp test/STAILQ_test.cpp test/LIST_test.cpp)

# Now link against gtest or gtest_main as needed. Eg
target_link_libraries(project gtest_main)
target_link_libraries(project gtest)
add_test(NAME example_test COMMAND example)

# Link against rapidcheck
# Download and unpack rapidcheck
configure_file(CMakeLists.txt.rc rapidcheck-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/rapidcheck-download )
if(result)
    message(FATAL_ERROR "CMake step for rapidcheck failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/rapidcheck-download )
if(result)
    message(FATAL_ERROR "Build step for rapidcheck failed: ${result}")
endif()

# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/rapidcheck-src
        ${CMAKE_CURRENT_BINARY_DIR}/rapidcheck-build
        EXCLUDE_FROM_ALL)

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/rapidcheck-src/extras/gtest
        EXCLUDE_FROM_ALL)

target_link_libraries(project rapidcheck_gtest rapidcheck)

#this file needs to be linked to another path so Clion can give syntax highlighting
add_custom_command(TARGET project POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_CURRENT_BINARY_DIR}/rapidcheck-src/extras/gtest/include/rapidcheck/gtest.h
        ${CMAKE_CURRENT_BINARY_DIR}/rapidcheck-src/include/rapidcheck_gtest.h)

project(project)

set(CMAKE_CXX_STANDARD 20)
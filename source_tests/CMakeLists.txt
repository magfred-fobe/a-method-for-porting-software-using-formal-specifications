cmake_minimum_required(VERSION 3.17)
# Download and unpack googletest at configure time
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

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(project test.cpp integerlists.h)
target_link_libraries(project gtest_main)
add_test(NAME example_test COMMAND example)

# Link against rapidcheck
# Wasn't able to include the module directly.
target_include_directories(project PRIVATE ${CMAKE_SOURCE_DIR}/rapidcheck/include)
target_include_directories(project PRIVATE ${CMAKE_SOURCE_DIR}/rapidcheck/extras/gtest/include)


target_link_libraries(project)


#target_link_libraries(project rapidcheck_gtest)

project(project)

set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.1)

# build third parties
add_subdirectory(third-party)


project(nsp)

find_package(Boost)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    "src/employee.cpp"
    "src/solution.cpp")

set(TEST_SOURCES
    "test/test_date.cpp")

# build main
add_executable(main "nsp.cpp" ${SOURCES})
target_include_directories(main PRIVATE "include")

#build test
enable_testing()
add_executable(unittest "test/main.cpp" ${TEST_SOURCES})
target_link_libraries(unittest gtest gtest_main)
target_include_directories(unittest PRIVATE "include")
target_include_directories(unittest PRIVATE "third-party/googletest/googletest/include")
add_test(gtest unittest)

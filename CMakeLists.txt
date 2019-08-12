cmake_minimum_required(VERSION 3.1)

project(nsp)

# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.
set(JSON_BuildTests OFF CACHE INTERNAL "")
# build third parties
add_subdirectory(third-party)

find_package(Boost)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(SOURCES
    "src/employee.cpp"
    "src/solution.cpp"
    "src/solver.cpp"
    "src/configuration_factory.cpp"
    "src/date.cpp"
    "src/json_configuration.cpp"
    "src/utils.cpp")

set(TEST_SOURCES
    "test/test_date.cpp")



# build main
add_executable(main "nsp.cpp" ${SOURCES})
target_include_directories(main PRIVATE "include")
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)


#build test
enable_testing()
add_executable(unittest "test/main.cpp" ${TEST_SOURCES})
target_link_libraries(unittest gtest gtest_main nlohmann_json::nlohmann_json)
target_include_directories(unittest PRIVATE "include")
target_include_directories(unittest PRIVATE "third-party/googletest/googletest/include")
add_test(gtest unittest)

cmake_minimum_required(VERSION 3.1)
project(nsp)

find_package(Boost)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SOURCE
    "src/employee.cpp"
    "src/solution.cpp")

add_executable(main "nsp.cpp" ${SOURCE})
target_include_directories(main PRIVATE "include")
cmake_minimum_required(VERSION 3.1)

project(nsp)

# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.
set(JSON_BuildTests OFF CACHE INTERNAL "")

# build third parties
enable_testing()
add_subdirectory(third-party)

find_package(Boost COMPONENTS system filesystem REQUIRED)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -DBOOST_NO_CXX11_SCOPED_ENUMS")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(SOURCES
    "src/employee.cpp"
    "src/solution.cpp"
    "src/solver.cpp"
    "src/configuration_factory.cpp"
    "src/date.cpp"
    "src/json_configuration.cpp"
    "src/utils.cpp"
    "src/rules/consecutive_days_rule.cpp"
    "src/rules/max_hours_per_week_rule.cpp"
    "src/rules/min_hours_per_week_rule.cpp"
    "src/rules/rooster_requirement_rule.cpp"
    "src/rules/shop_closed_rule.cpp"
    "src/rules/vacation_days_rule.cpp"
    "src/rules/rule_engine.cpp"
    "src/schedule.cpp"
    "src/solution_factory.cpp"
    "src/printers.cpp"
    )

set(TEST_SOURCES
    "test/test_date.cpp"
    "test/test_configuration.cpp"
    "test/test_schedule.cpp"
    )

  set(TO_LINK_LIBRARIES 
    nlohmann_json::nlohmann_json 
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY})

# build main
add_executable(main "nsp.cpp" ${SOURCES})
target_include_directories(main PRIVATE "include")
target_link_libraries(main PRIVATE ${TO_LINK_LIBRARIES})


#build test

add_executable(unittest "test/main.cpp" ${SOURCES} ${TEST_SOURCES})
target_link_libraries(unittest gtest gtest_main ${TO_LINK_LIBRARIES})
target_include_directories(unittest PRIVATE "include")
target_include_directories(unittest PRIVATE "third-party/googletest/googletest/include")
add_test(
    NAME unittest 
    COMMAND unittest 
)

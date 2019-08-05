#pragma once
#include <vector>
#include <map>

namespace nsp
{

class Employee;
enum class RuleType
{
    HARD,
    SOFT
};

enum class ShiftType : int
{
    NORMAL = 10,
    SHORT = 8,
    OFF = 0
};

enum class Grade
{
    Regular,
    Manager
};

using Penalty = unsigned int;
using ShiftPattern = std::vector<ShiftType>;
using Schedule = std::map<Employee, ShiftPattern>;
}
#pragma once
#include <vector>
#include <map>

namespace nsp
{

class Employee;
enum class RuleType {
  MaxHoursPerWeek,
  MinHoursPerWeek,
  VacationDays,
  ConsecutiveDays,
  RoosterRequirement,
  ShopClosed
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
    Manager,    // has more duties(handle invoices, etc...)
    Intern,     // starting out; requires trainig
    Owner       // owner of the shop
};

using Penalty = unsigned int;
// using ShiftPattern = std::vector<ShiftType>;
// using Schedule = std::map<Employee, ShiftPattern>;
}

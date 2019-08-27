#pragma once
#include <ostream>
#include <string>
#include "date.h"
#include "nsp_types.h"

namespace nsp {
Grade stringToGrade(std::string);
std::string gradeToString(Grade);
RuleType stringToRuleType(std::string);
std::string ruleTypeToString(RuleType);
Month stringToMonth(std::string);
std::string monthToString(Month);
Day stringToDay(std::string);
int daysInMonth(Month);
std::string dayToString(Day);
std::string shiftTypeToString(ShiftType);
// print type of object template
// std::cout << type_name<decltype(ci)>() << '\n';
template <typename T> std::string type_name();
}

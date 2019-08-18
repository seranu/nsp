#pragma once
#include <date.h>
#include <nsp_types.h>
#include <ostream>
#include <string>

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
// print type of object template
// std::cout << type_name<decltype(ci)>() << '\n';
template <typename T> std::string type_name();
}

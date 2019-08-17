#pragma once
#include <date.h>
#include <employee.h>
#include <iconfiguration.h>
#include <nsp_types.h>
#include <ostream>
#include <rules/irule.h>
#include <string>

namespace nsp {
Grade stringToGrade(std::string);
std::string gradeToString(Grade);
RuleType stringToRuleType(std::string);
std::string ruleTypeToString(RuleType);
Month stringToMonth(std::string);
std::string monthToString(Month);
Day stringToDay(std::string);
std::string dayToString(Day);
std::ostream &operator<<(std::ostream &, const Employee &);
std::ostream &operator<<(std::ostream &, const IRule &);
std::ostream &operator<<(std::ostream &, const IConfiguration &);
// print type of object template
// std::cout << type_name<decltype(ci)>() << '\n';
template <typename T> std::string type_name();
}

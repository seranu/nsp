#pragma once
#include "rules/consecutive_days_rule.h"
#include "rules/max_hours_per_week_rule.h"
#include "rules/min_hours_per_week.h"
#include "rules/rooster_requirement_rule.h"
#include "rules/shop_closed_rule.h"
#include "rules/vacation_days_rule.h"
#include <employee.h>
#include <nsp_types.h>
#include <ostream>
#include <string>

namespace nsp {
Grade stringToGrade(std::string);
std::string gradeToString(Grade);
RuleType stringToRule(std::string);
std::string ruleToString(RuleType);
Month stringToMonth(std::string);
std::string monthToString(Month);
Day stringToDay(std::string);
std::string dayToString(Day);
std::ostream &operator<<(std::ostream &, const Employee &);
std::ostream &operator<<(std::ostream &, const MinHoursPerWeekRule &);
std::ostream &operator<<(std::ostream &, const MaxHoursPerWeekRule &);
std::ostream &operator<<(std::ostream &, const ConsecutiveDaysRule &);
std::ostream &operator<<(std::ostream &, const RoosterRequirementRule &);
std::ostream &operator<<(std::ostream &, const VacationDaysRule &);
std::ostream &operator<<(std::ostream &, const ShopClosedRule &);
}

#include "utils.h"
#include <algorithm>
#include <cassert>
#include <unordered_map>

namespace nsp {
Grade stringToGrade(std::string grade) {
  static std::unordered_map<std::string, Grade> s_grades = {
      {"regular", Grade::Regular},
      {"intern", Grade::Intern},
      {"manager", Grade::Manager},
      {"owner", Grade::Owner}};

  std::transform(grade.begin(), grade.end(), grade.begin(), ::tolower);
  assert(s_grades.find(grade) != s_grades.end() && "Unknown grade!");
  return s_grades[grade];
}

std::string gradeToString(Grade grade) {
  static std::unordered_map<Grade, std::string> s_gradeStrings = {
      {Grade::Regular, "Regular"},
      {Grade::Intern, "Intern"},
      {Grade::Manager, "Manager"},
      {Grade::Owner, "Owner"}};
  assert(s_gradeStrings.find(grade) != s_gradeStrings.end());
  return s_gradeStrings[grade];
}

RuleType stringToRuleType(std::string ruleStr) {
  static std::unordered_map<std::string, RuleType> s_rules = {
      {"minhoursperweek", RuleType::MinHoursPerWeek},
      {"maxhoursperweek", RuleType::MaxHoursPerWeek},
      {"vacationdays", RuleType::VacationDays},
      {"consecutivedays", RuleType::ConsecutiveDays},
      {"shopclosed", RuleType::ShopClosed},
      {"roosterrequirement", RuleType::RoosterRequirement}};
  std::transform(ruleStr.begin(), ruleStr.end(), ruleStr.begin(), ::tolower);
  assert(s_rules.find(ruleStr) != s_rules.end() && "Unknown Rule");
  return s_rules[ruleStr];
}

std::string ruleTypeToString(RuleType rule) {
  static std::unordered_map<RuleType, std::string> s_ruleStrings = {
      {RuleType::MinHoursPerWeek, "MinHoursPerWeek"},
      {RuleType::MaxHoursPerWeek, "MaxHoursPerWeek"},
      {RuleType::VacationDays, "VacationDays"},
      {RuleType::ConsecutiveDays, "ConsecutiveDays"},
      {RuleType::ShopClosed, "ShopClosed"},
      {RuleType::RoosterRequirement, "RoosterRequirement"}};
  assert(s_ruleStrings.find(rule) != s_ruleStrings.end() && "Unknown Rule");
  return s_ruleStrings[rule];
}

Month stringToMonth(std::string month) {
  static std::unordered_map<std::string, Month> s_months = {
      {"january", Month::January},
      {"february", Month::February},
      {"march", Month::March},
      {"april", Month::April},
      {"may", Month::May},
      {"june", Month::June},
      {"july", Month::July},
      {"august", Month::August},
      {"september", Month::September},
      {"october", Month::October},
      {"november", Month::November},
      {"december", Month::December}};
  std::transform(month.begin(), month.end(), month.begin(), ::tolower);
  assert(s_months.find(month) != s_months.end() && "Unknown month!");
  return s_months[month];
}

std::string monthToString(Month month) {
  static std::unordered_map<Month, std::string> s_monthStrings = {
      {Month::January, "January"},
      {Month::February, "February"},
      {Month::March, "March"},
      {Month::April, "April"},
      {Month::May, "May"},
      {Month::June, "June"},
      {Month::July, "July"},
      {Month::August, "August"},
      {Month::September, "September"},
      {Month::October, "October"},
      {Month::November, "November"},
      {Month::December, "December"}};
  assert(s_monthStrings.find(month) != s_monthStrings.end() && "Unknown month");
  return s_monthStrings[month];
}

Day stringToDay(std::string day) {
  static std::unordered_map<std::string, Day> s_days = {
      {"sunday", Day::Sunday},     {"monday", Day::Monday},
      {"tuesday", Day::Tuesday},   {"wednesday", Day::Wednesday},
      {"thursday", Day::Thursday}, {"friday", Day::Friday},
      {"saturday", Day::Saturday}};
  std::transform(day.begin(), day.end(), day.begin(), ::tolower);
  assert(s_days.find(day) != s_days.end() && "Unknown day!");
  return s_days[day];
}

std::string dayToString(Day day) {
  static std::unordered_map<Day, std::string> s_dayStrings = {
      {Day::Sunday, "Sunday"},     {Day::Monday, "Monday"},
      {Day::Tuesday, "Tuesday"},   {Day::Wednesday, "Wednesday"},
      {Day::Thursday, "Thursday"}, {Day::Friday, "Friday"},
      {Day::Saturday, "Saturday"}};
  assert(s_dayStrings.find(day) != s_dayStrings.end() && "Unknown day!");
  return s_dayStrings[day];
}

std::ostream &operator<<(std::ostream &str, const Employee &emp) {
  EmployeeHash h;
  str << "Employee: [ name = \"" << emp.name() << "\" employeeId = \"" << h(emp)
      << "\" grade = \"" << gradeToString(emp.grade())
      << "\" min_weekly_hours = \"" << emp.minWeeklyHours()
      << "\" max_weekly_hours = \"" << emp.maxWeeklyHours() << "\" ]\n";
  return str;
}

std::ostream &operator<<(std::ostream &os, const IRule &rule) {
  os << rule.print();
  return os;
}

std::ostream &operator<<(std::ostream &os, const IConfiguration &config) {
  os << "\n********** Configuration **************\n";
  os << "Month: " << monthToString(config.month()) << "\n";
  os << "Employees: \n";
  for (const auto &employee : config.employees()) {
    os << "\t" << employee << "\n";
  }
  os << "Rules: \n";
  for (const auto &rule : config.rules()) {
    os << "\t" << *rule << "\n";
  }
  os << "***************************************\n";
  return os;
}

} // namespace nsp

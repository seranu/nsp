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

std::ostream &operator<<(std::ostream &str, const Employee &emp) {
  str << "Employee: [ name = \"" << emp.name() << "\" grade = \""
      << gradeToString(emp.grade()) << "\" min_monthly_hours = \""
      << emp.minMonthlyHours() << "\" max_monthly_hours = \""
      << emp.maxMonthlyHours() << "\" ]\n";
  return str;
}

} // namespace nsp

#include "employee.h"
#include <utils.h>
#include <boost/functional/hash.hpp>

namespace nsp
{
std::size_t EmployeeHash::operator()(const Employee &e) const {
  std::size_t seed = 0;
  boost::hash_combine(seed, e.name());
  boost::hash_combine(seed, e.grade());
  return seed;
}
std::ostream &operator<<(std::ostream &str, const Employee &emp) {
  EmployeeHash h;
  str << "Employee: [ name = \"" << emp.name() << "\" employeeId = \"" << h(emp)
      << "\" grade = \"" << gradeToString(emp.grade())
      << "\" min_weekly_hours = \"" << emp.minWeeklyHours()
      << "\" max_weekly_hours = \"" << emp.maxWeeklyHours() << "\" ]\n";
  return str;
}
}  // namespace nsp

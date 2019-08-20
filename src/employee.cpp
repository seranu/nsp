#include "employee.h"
#include <utils.h>
#include <boost/functional/hash.hpp>
#include <cassert>
#include <unordered_map>

namespace nsp
{
std::size_t EmployeeHash::operator()(const Employee &e) const {
  std::size_t seed = 0;
  boost::hash_combine(seed, e.name());
  boost::hash_combine(seed, e.grade());
  return seed;
}

int roosterScore(Grade g) {
  static std::unordered_map<Grade, int> s_scores = {{Grade::Regular, 110},
                                                    {Grade::Manager, 150},
                                                    {Grade::Intern, 100},
                                                    {Grade::Owner, 150}};
  assert(s_scores.find(g) != s_scores.end());
  return s_scores[g];
}

std::ostream &operator<<(std::ostream &str, const Employee &emp) {
  EmployeeHash h;
  str << "Employee: [ name = \"" << emp.name() << "\" employeeId = \"" << h(emp)
      << "\" grade = \"" << gradeToString(emp.grade()) << "\" ]\n";
  return str;
}
}  // namespace nsp

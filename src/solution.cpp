#include "solution.h"
#include <boost/functional/hash.hpp>
#include <cassert>
#include <iostream>
#include <vector>
#include "rules/rule_engine.h"

namespace nsp 
{
std::size_t SolutionHash::operator()(const Solution &s) const {
  ScheduleHash sh;
  std::size_t seed = sh(s.schedule());
  boost::hash_combine(seed, s.penalty());
  return seed;
}

Solution Solution::morph(const ScheduleAction &action) const {
  Schedule sch(m_schedule);
  action.execute(sch);
  return Solution(sch);
}

std::ostream &operator<<(std::ostream &os, const Solution &s) {
  os << s.schedule();
  return os;
}
}  // namespace nsp

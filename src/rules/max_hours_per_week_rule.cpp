#include <rules/max_hours_per_week_rule.h>
#include <sstream>
#include <string>
#include <utils.h>

namespace nsp {
std::string MaxHoursPerWeekRule::print() const {
  std::stringstream os;
  os << "Rule [ type = \"" << ruleTypeToString(RuleType::MaxHoursPerWeek)
     << "\" employeeId = \"" << m_employeeId << "\" value = \"" << m_value
     << "\" ];";
  return os.str();
}
} // namespace nsp

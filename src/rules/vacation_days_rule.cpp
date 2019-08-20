#include <rules/vacation_days_rule.h>
#include <sstream>
#include <string>
#include <utils.h>

namespace nsp {
bool VacationDaysRule::satisfied(const Schedule &) {}

std::string VacationDaysRule::print() const {
  std::stringstream os;
  os << "Rule [ type = \"" << ruleTypeToString(RuleType::VacationDays)
     << "\" value = \""
     << "{ ";
  for (auto day : m_vacationDays) {
    os << day << " ";
  }
  os << "} \" ]";
  return os.str();
}
} // namespace nsp

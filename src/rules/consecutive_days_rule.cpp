#include <rules/consecutive_days_rule.h>
#include <sstream>
#include <string>
#include <utils.h>

namespace nsp {
std::string ConsecutiveDaysRule::print() const {
  std::stringstream os;
  os << "Rule [ type = \"" << ruleTypeToString(RuleType::ConsecutiveDays)
     << "\" value = \"" << m_value << "\" ];";
  return os.str();
}

} // namespace nsp

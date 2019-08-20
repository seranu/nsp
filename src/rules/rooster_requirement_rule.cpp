#include <rules/rooster_requirement_rule.h>
#include <sstream>
#include <string>
#include <utils.h>

namespace nsp {
bool RoosterRequirementRule::satisfied(const Schedule &schedule) {}

std::string RoosterRequirementRule::print() const {
  std::stringstream os;
  os << "Rule [ type = \"" << ruleTypeToString(RuleType::RoosterRequirement)
     << "\" value = \"" << dayToString(m_day) << ": " << m_value << "\" ];";
  return os.str();
}
} // namespace nsp

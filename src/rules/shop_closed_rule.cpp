#include <rules/shop_closed_rule.h>
#include <sstream>
#include <string>
#include <utils.h>

namespace nsp {
std::string ShopClosedRule::print() const {
  std::stringstream os;
  os << "Rule [ type = \"" << ruleTypeToString(RuleType::ShopClosed)
     << "\" value = \""
     << "{ ";
  for (auto day : m_daysClosed) {
    os << day << " ";
  }
  os << "} \" ]";
  return os.str();
}
} // namespace nsp
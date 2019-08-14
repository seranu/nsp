#pragma once

#include <rules/irule.h>
#include <vector>

namespace nsp {
class ShopClosedRule : public IRule {
public:
  ShopClosedRule(std::vector<unsigned short> values)
      : m_daysClosed(move(values)) {}
  RuleType type() const override { return RuleType::ShopClosed; }
  virtual bool satisfied(const Schedule &schedule) override;
  std::vector<unsigned short> value() const { return m_daysClosed; }
  std::string print() const override;

private:
  std::vector<unsigned short> m_daysClosed;
};
} // namespace nsp

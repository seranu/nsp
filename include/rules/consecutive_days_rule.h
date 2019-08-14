#pragma once

#include <rules/irule.h>

namespace nsp {
class ConsecutiveDaysRule : public IRule {
public:
  ConsecutiveDaysRule(int value) : m_value(value) {}
  RuleType type() const override { return RuleType::ConsecutiveDays; }
  virtual bool satisfied(const Schedule &schedule) override;
  unsigned short value() const { return m_value; }
  std::string print() const override;

private:
  unsigned short m_value;
};
} // namespace nsp

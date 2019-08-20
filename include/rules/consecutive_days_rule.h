#pragma once

#include <rules/irule.h>

namespace nsp {
class ConsecutiveDaysRule : public IRule {
public:
 ConsecutiveDaysRule(int value, int penalty) : m_value(value) {
   setPenalty(penalty);
 }
 RuleType type() const override { return RuleType::ConsecutiveDays; }
 int apply(const Schedule &schedule) override;
 unsigned short value() const { return m_value; }
 std::string print() const override;

private:
  unsigned short m_value;
};
} // namespace nsp

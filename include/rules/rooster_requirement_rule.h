#pragma once

#include <date.h>
#include <rules/irule.h>
#include <utility>

namespace nsp {
class RoosterRequirementRule : public IRule {
public:
 RoosterRequirementRule(Day day, int value, int penalty)
     : m_day(day), m_value(value) {
   setPenalty(penalty);
 }
 RuleType type() const override { return RuleType::RoosterRequirement; }
 int apply(const Schedule &schedule) override;
 std::pair<Day, int> value() const { return std::make_pair(m_day, m_value); }
 std::string print() const override;

private:
  Day m_day;
  int m_value;
};
} // namespace nsp

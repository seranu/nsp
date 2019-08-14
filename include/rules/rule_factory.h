#pragma once
#include "consecutive_days_rule.h"
#include "irule.h"
#include "max_hours_per_week_rule.h"
#include "min_hours_per_week_rule.h"
#include "rooster_requirement_rule.h"
#include "shop_closed_rule.h"
#include "vacation_days_rule.h"
#include <cassert>
#include <memory>
#include <nsp_types.h>

namespace nsp {
class RuleFactory {
public:
  template <typename... Args>
  static std::shared_ptr<IRule> create(RuleType type, Args... args) {
    switch (type) {
    case RuleType::MaxHoursPerWeek:
      return std::make_shared<MaxHoursPerWeekRule>(args...);
    case RuleType::MinHoursPerWeek:
      return std::make_shared<MinHoursPerWeekRule>(args...);
    case RuleType::VacationDays:
      return std::make_shared<VacationDaysRule>(args...);
    case RuleType::ConsecutiveDays:
      return std::make_shared<ConsecutiveDaysRule>(args...);
    case RuleType::RoosterRequirement:
      return std::make_shared<RoosterRequirementRule>(args...);
    case RuleType::ShopClosed:
      return std::make_shared<ShopClosedRule>(args...);
    default:
      assert(false && "Unknown rule type");
    }
    return nullptr;
  }
};
}

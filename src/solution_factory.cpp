#include "solution_factory.h"
#include <employee.h>
#include <rules/include_all_rules.h>
#include <utils.h>
#include <unordered_map>

namespace nsp {
Solution SolutionFactory::createRandomSolution(const IConfiguration& config) {
  Schedule schedule(config.month());
  // TODO: use vector<Employee*>
  std::vector<Employee> employees = config.employees();
  auto numDays = daysInMonth(config.month());
  const auto year = currentYear();
  std::unordered_map<Day, int> roosterRequirements;
  for (const auto& rule : config.rules()) {
    if (rule->type() == RuleType::RoosterRequirement) {
      const auto* rrRule =
          dynamic_cast<const RoosterRequirementRule*>(rule.get());
      assert(rrRule);
      const auto& [day, value] = rrRule->value();
      roosterRequirements[day] = value;
    }
  }

  // determine day of the week for 1st of the month
  auto day = dayOfWeek(1, config.month(), year);
  for (auto i = 0; i < numDays; i++) {
    int rScore = 0;
    int tail = employees.size() - 1;
    while (tail >= 0) {
      if (rScore < roosterRequirements[day]) {
        // pick random employee and add a shift to it's schedule
        // swap it with employees[cIdx], dec cIdx
        // avoid division by 0
        auto idx = tail ? rand() % tail : 0;
        schedule.addShift(employees[idx], i, ShiftType::NORMAL);
        rScore += roosterScore(employees[idx].grade());
        std::swap(employees[tail], employees[idx]);
      } else {
        // add empty shift
        schedule.addShift(employees[tail], i, ShiftType::OFF);
      }
      tail--;
    }
    day = nextDay(day);
  }

  return Solution(schedule);
}

}  // namespace nsp

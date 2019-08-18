#include "solution_factory.h"
#include <employee.h>
#include <rules/rule_factory.h>
#include <utils.h>
#include <unordered_map>

namespace nsp {
Solution SolutionFactory::createRandomSolution(const IConfiguration& config) {
  Schedule schedule;
  // TODO: use vector<Employee*>
  std::vector<Employee> employees(config.employees().begin(),
                                  config.employees().end());
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
    int roosterScore = 0;
    int tail = employees.size() - 1;
    day = nextDay(day);
    while (tail >= 0) {
      if (roosterScore < roosterRequirements[day]) {
        // pick random employee and add a shift to it's schedule
        // swap it with employees[cIdx], dec cIdx
        auto idx = rand() % tail;
        schedule[employees[idx]].push_back(ShiftType::NORMAL);
        std::swap(employees[tail], employees[idx]);
        tail--;
      } else {
        // add empty shift
        schedule[employees[tail]].push_back(ShiftType::OFF);
      }
    }
  }

  return Solution(schedule);
}

}  // namespace nsp

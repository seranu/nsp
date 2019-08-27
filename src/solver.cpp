#include "solver.h"
#include <iostream>
#include "employee.h"
#include "iconfiguration.h"
#include "schedule_action.h"
#include "solution_factory.h"

using namespace std;

namespace nsp
{
int dayRoosterScore(const day_agenda_t& agenda) {
  int score = 0;
  for (auto const& [emp, shift] : agenda) {
    if (shift != ShiftType::OFF) {
      score += roosterScore(emp.grade());
    }
  }
  return score;
}

void applySuggestions(Solution& sol,
                      const std::vector<ScheduleAction>& suggestions,
                      const RuleEngine& ruleEngine) {
  Schedule schedule = sol.schedule();
  auto roosterScores = ruleEngine.roosterScores();
  const auto year = currentYear();
  // delete all deletes
  for (const auto& action : suggestions) {
    if (action.type() == ScheduleActionType::DELETE) {
      schedule.deleteShift(action.target(), action.day());
    }
  }
  // add all adds
  for (const auto& action : suggestions) {
    if (action.type() == ScheduleActionType::ADD) {
      const auto& dayAgenda = schedule.agenda(action.day());
      const auto day = dayOfWeek(action.day() + 1, schedule.month(), year);
      if (dayRoosterScore(dayAgenda) < roosterScores[day]) {
        schedule.addShift(action.target(), action.day(), action.shiftType());
      }
    }
  }
  // fill with random
  //  for (int i = 0; i < daysInMonth(schedule.month()); i++) {
  //    int score = dayRoosterScore(schedule.agenda(i));
  //    const auto day = dayOfWeek(i + 1, schedule.month(), year);
  //    while (score < roosterScores[day]) {
  //    }
  //  }
  sol = Solution(schedule);
}

void Solver::solve(int numIterations) {
  cout << "Solver::solve(" << numIterations << ") generating random solution\n";
  auto solution = SolutionFactory::createRandomSolution(*m_config);
  m_ruleEngine->computePenalty(solution);
  std::cout << "Generated solution with penalty: " << solution.penalty() << "\n"
            << solution;
  for (int i = 0; i < numIterations; i++) {
    solution = iterate(solution);
    m_ruleEngine->computePenalty(solution);
    std::cout << "Iterated to solution with penalty : " << solution.penalty()
              << "\n";
    if (m_bestSolutionSoFar &&
        solution.penalty() < m_bestSolutionSoFar->penalty()) {
      m_bestSolutionSoFar = solution;
    } else {
      m_bestSolutionSoFar = solution;
    }
  }
}

Solution Solver::iterate(const Solution& solution) {
  auto suggestions = m_ruleEngine->suggest(solution);
  Solution result(solution);
  for (auto& suggestion : suggestions) {
    cout << suggestion << "\n";
  }
  applySuggestions(result, suggestions, *m_ruleEngine);
  return result;
}

}  // namespace nsp

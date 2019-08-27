#include "solver.h"
#include <iostream>
#include "iconfiguration.h"
#include "solution_factory.h"

using namespace std;

namespace nsp
{
void Solver::solve(int numIterations) {
  cout << "Solver::solve(" << numIterations << ") generating random solution\n";
  auto solution = SolutionFactory::createRandomSolution(*m_config);
  m_ruleEngine->computePenalty(solution);
  std::cout << "Generated solution with penalty: " << solution.penalty()
            << "\n";
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
    auto increment = solution.morph(suggestion);
    m_ruleEngine->computePenalty(increment);
    if (increment.penalty() < result.penalty()) {
      result = increment;
    }
  }
  return result;
}

}  // namespace nsp

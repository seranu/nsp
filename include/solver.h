#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <optional>
#include "solution.h"

namespace nsp
{
class Solver
{
private:
    std::optional<Solution> m_bestSolutionSoFar;

public:
    Solver();
    void solve();

};
}
#endif // __SOLVER_H__

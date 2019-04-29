#ifndef __SOLUTION_FACTORY_H__
#define __SOLUTION_FACTORY_H__
#include "solution.h"
namespace nsp
{
class SolutionFactory
{
public:
    static Solution createRandomSolution(const Configuration& config);
    static Solution createFrom(const Solution& sol);
};
}
#endif __SOLUTION_FACTORY_H__
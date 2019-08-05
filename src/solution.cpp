#include "solution.h"
#include "ruleengine.h"
#include <cassert>
#include <vector>
#include <boost/functional/hash.hpp>

namespace nsp 
{

std::size_t SolutionHash::operator()(const Solution& s)
{
    std::size_t seed = 0;
    // TODO: make sure employees are combined in order every time
    for (const auto& emp : s.schedule()) {
        boost::hash_combine(seed, emp.second);
    }
    return seed;
}
}

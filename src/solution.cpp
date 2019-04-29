#include "solution.h"
#include <boost/functional/hash.hpp>

namespace nsp 
{

bool Solution::valid() const
{
    ShiftPattern res;
    for (const auto& p : m_schedule) {
        assert()
    }
}

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

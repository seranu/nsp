#include "employee.h"

#include <boost/functional/hash.hpp>

namespace nsp
{
std::size_t  EmployeeHash::operator() (const Employee& e) 
{
    std::size_t seed = 0;
    boost::hash_combine(seed, e.name());
    boost::hash_combine(seed, e.grade());
    return seed;
}
}

#include "employee.h"

#include <functional>

namespace nsp
{
std::size_t  EmployeeHash::operator() (const Employee& e) 
{
    auto h1 = std::hash<std::string>{}(e.name());
    auto h2 = std::hash<Grade>{}(e.grade());
    return h1 ^ h2;
}
}
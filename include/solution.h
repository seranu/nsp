#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include <map>
#include "employee.h"
#include "shiftpattern.h"

namespace nsp
{

struct SolutionHash
{
    std::size_t operator()(const Solution& s);
};

class Solution
{
private:
    int m_score;
    std::map<Employee, ShiftPattern> m_employees;
public:

    int score() const { return m_score; }
    const std::map<Employee, ShiftPattern>& employees() { return m_employees; }
};
} // nsp

#endif // __SOLUTION_H__
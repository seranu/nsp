#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include <map>
#include "employee.h"
#include "shiftpattern.h"

namespace nsp
{
class Solution
{
private:
    int m_score;
    std::map<Employee, ShiftPattern> m_schedule;
public:
    bool valid() const;
    int score() const { return m_score; }
    const std::map<Employee, ShiftPattern>& schedule() const { return m_schedule; }
};

struct SolutionHash
{
    std::size_t operator()(const Solution& s);
};

} // nsp

#endif // __SOLUTION_H__
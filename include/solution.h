#pragma once

#include <map>
#include "nsptypes.h"
#include "employee.h"

namespace nsp
{

class Solution
{
private:
    Schedule m_schedule;
    Penalty m_penalty;
public:
    Solution(Schedule schedule) 
        : m_schedule(move(schedule)) 
        {
        }
    void setPenalty(const Penalty);
    Penalty penalty() const { return m_penalty; }
    const Schedule& schedule() const { return m_schedule; }
};

struct SolutionHash
{
    std::size_t operator()(const Solution& s);
};

} // nsp

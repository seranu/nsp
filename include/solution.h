#pragma once

#include <schedule.h>
#include <map>
#include "employee.h"
#include "nsp_types.h"
namespace nsp
{

class Solution
{
private:
 Schedule m_schedule;
 Penalty m_penalty;
public:
 Solution(Schedule schedule) : m_schedule(std::move(schedule)) {}
 void setPenalty(const Penalty);
 Penalty penalty() const { return m_penalty; }
 const Schedule &schedule() const { return m_schedule; }
};

std::ostream &operator<<(std::ostream &, const Solution &);

struct SolutionHash
{
    std::size_t operator()(const Solution& s);
};

} // nsp

#pragma once

#include <climits>
#include <map>
#include "employee.h"
#include "nsp_types.h"
#include "schedule.h"
#include "schedule_action.h"

namespace nsp
{
class Solution
{
private:
 Schedule m_schedule;
 Penalty m_penalty{std::numeric_limits<Penalty>::max()};

public:
 Solution(Schedule schedule) : m_schedule(std::move(schedule)) {}
 Solution(const Solution &other)
     : m_schedule(other.m_schedule), m_penalty(other.m_penalty) {}
 Solution(Solution &&other) : m_schedule(std::move(other.m_schedule)) {
   m_penalty =
       std::exchange(other.m_penalty, std::numeric_limits<Penalty>::max());
 }
 Solution &operator=(const Solution &other) {
   m_schedule = other.m_schedule;
   m_penalty = other.m_penalty;
   return *this;
 }
 Solution &operator=(Solution &&other) {
   m_schedule = std::move(other.m_schedule);
   m_penalty =
       std::exchange(other.m_penalty, std::numeric_limits<Penalty>::max());
   return *this;
 }
 void setPenalty(const Penalty penalty) { m_penalty = penalty; }
 Penalty penalty() const { return m_penalty; }
 const Schedule &schedule() const { return m_schedule; }
 Solution morph(const ScheduleAction &) const;
};

struct SolutionHash {
  std::size_t operator()(const Solution &) const;
};

std::ostream &operator<<(std::ostream &, const Solution &);

} // nsp

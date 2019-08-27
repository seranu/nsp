#include "schedule.h"
#include <algorithm>
#include <boost/functional/hash.hpp>
#include <iomanip>
#include "log.h"

namespace nsp {

std::size_t ScheduleHash::operator()(const Schedule& schedule) const {
  size_t seed = 0;
  boost::hash_combine(seed, schedule.month());
  boost::hash_combine(seed, schedule.agenda());
  //  boost::hash_combine(seed, schedule.shifts());
  return seed;
}

const std::vector<ShiftType>& Schedule::emptyShift() const {
  static std::vector<ShiftType> s_empyShift;
  return s_empyShift;
}

void Schedule::addShift(const Employee& employee, int day,
                        ShiftType shiftType) {
  LOG_DEBUG("ADD %s : %d - %s", employee.name().c_str(), day + 1,
            shiftTypeToString(shiftType).c_str());
  assert(day < m_numDays);
  m_agenda[day][employee] = shiftType;
  if (m_shifts.find(employee) == m_shifts.end()) {
    m_shifts[employee].resize(m_numDays);
  }
  m_shifts[employee][day] = shiftType;
}

void Schedule::deleteShift(const Employee& employee, int day) {
  LOG_DEBUG("DELETE %s : %d", employee.name().c_str(), day + 1);
  assert(day < m_numDays);
  const auto& dayAgenda = m_agenda[day];
  const auto it = dayAgenda.find(employee);
  if (it != dayAgenda.end()) {
    m_agenda[day].erase(it);
    m_shifts[employee][day] = ShiftType::OFF;
  } else {
    LOG_DEBUG("%s has no shift on %d", employee.name().c_str(), day);
  }
}

void Schedule::moveShift(const Employee& employee, int from, int to) {
  assert(to < m_numDays && from < m_numDays);
  auto shiftType = m_shifts[employee][from];
  deleteShift(employee, from);
  addShift(employee, to, shiftType);
}

void Schedule::switchShift(const Employee& lhs, int lhsDay, const Employee& rhs,
                           int rhsDay) {
  assert(lhsDay < m_numDays && rhsDay < m_numDays);
  moveShift(lhs, lhsDay, rhsDay);
  moveShift(rhs, rhsDay, lhsDay);
}

const std::vector<ShiftType>& Schedule::shifts(const Employee& emp) const {
  auto it = m_shifts.find(emp);
  if (it != m_shifts.end()) {
    return it->second;
  }
  return emptyShift();
}

const std::vector<ShiftType>& Schedule::shifts(const size_t employeeId) const {
  for (auto const& [emp, shift] : m_shifts) {
    if (emp.id() == employeeId) {
      return shift;
    }
  }
  return emptyShift();
}

std::ostream& operator<<(std::ostream& os, const Schedule& schedule) {
  auto agenda = schedule.agenda();
  const auto month = schedule.month();
  auto day = dayOfWeek(1, month, currentYear());
  os << "******************** schedule ********************\n";
  for (size_t i = 0; i < agenda.size(); i++) {
    os << std::left << std::setw(20) << dayToString(day) << " : " << i + 1
       << " " << monthToString(month) << ": " << std::right << std::setw(10);
    std::vector<Employee> sortedEmployees;
    for (auto const& [emp, shift] : agenda[i]) {
      if (shift != ShiftType::OFF) {
        sortedEmployees.push_back(emp);
      }
    }
    std::sort(sortedEmployees.begin(), sortedEmployees.end());
    for (const auto& e : sortedEmployees) {
      os << e.name() << "(" << gradeToString(e.grade()) << ") "
         << std::setw(10);
    }
    os << "\n";
    day = nextDay(day);
 }
 os << "**************************************************\n";
 return os;
}
}  // namespace nsp

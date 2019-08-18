#include <schedule.h>

namespace nsp {

void Schedule::addShift(const Employee& employee, int day,
                        ShiftType shiftType) {
  m_agenda[day][employee] = shiftType;
  if (m_shifts.find(employee) == m_shifts.end()) {
    m_shifts[employee].resize(m_numDays);
  }
  m_shifts[employee][day] = shiftType;
}

void Schedule::deleteShift(const Employee& employee, int day) {
  const auto& dayAgenda = m_agenda[day];
  const auto it = dayAgenda.find(employee);
  assert(it != dayAgenda.end());
  m_agenda[day].erase(it);
  m_shifts[employee][day] = ShiftType::OFF;
}

void Schedule::moveShift(const Employee& employee, int from, int to) {
  auto shiftType = m_shifts[employee][from];
  deleteShift(employee, from);
  addShift(employee, to, shiftType);
}
// void Schedule::addEmployee(const Employee&);
std::ostream& operator<<(std::ostream& os, const Schedule& schedule) {
  // TODO: Implement
  return os;
}
}  // namespace nsp

#include <schedule.h>
#include <algorithm>

namespace nsp {

const std::vector<ShiftType>& Schedule::emptyShift() const {
  static std::vector<ShiftType> s_empyShift;
  return s_empyShift;
}

void Schedule::addShift(const Employee& employee, int day,
                        ShiftType shiftType) {
  assert(day < m_numDays);
  m_agenda[day][employee] = shiftType;
  if (m_shifts.find(employee) == m_shifts.end()) {
    m_shifts[employee].resize(m_numDays);
  }
  m_shifts[employee][day] = shiftType;
}

void Schedule::deleteShift(const Employee& employee, int day) {
  assert(day < m_numDays);
  const auto& dayAgenda = m_agenda[day];
  const auto it = dayAgenda.find(employee);
  assert(it != dayAgenda.end());
  m_agenda[day].erase(it);
  m_shifts[employee][day] = ShiftType::OFF;
}

void Schedule::moveShift(const Employee& employee, int from, int to) {
  assert(to < m_numDays && from < m_numDays);
  auto shiftType = m_shifts[employee][from];
  deleteShift(employee, from);
  addShift(employee, to, shiftType);
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
    os << dayToString(day) << " : " << i + 1 << " " << monthToString(month)
       << ": ";
    std::vector<Employee> sortedEmployees;
    for (auto const& [emp, shift] : agenda[i]) {
      if (shift != ShiftType::OFF) {
        sortedEmployees.push_back(emp);
      }
    }
    std::sort(sortedEmployees.begin(), sortedEmployees.end());
    for (const auto& e : sortedEmployees) {
      os << e.name() << "(" << e.id() << ", " << gradeToString(e.grade())
         << ") ";
    }
    os << "\n";
    day = nextDay(day);
 }
 os << "**************************************************\n";
 return os;
}
}  // namespace nsp

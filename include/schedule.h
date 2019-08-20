#pragma once
#include <date.h>
#include <employee.h>
#include <nsp_types.h>
#include <utils.h>
#include <unordered_map>
#include <vector>

namespace nsp {

using day_agenda_t = std::unordered_map<Employee, ShiftType, EmployeeHash>;
using shift_t =
    std::unordered_map<Employee, std::vector<ShiftType>, EmployeeHash>;
using agenda_t = std::vector<day_agenda_t>;

class Schedule {
 private:
  const Month m_month;
  const int m_numDays;
  shift_t m_shifts;
  agenda_t m_agenda;

 public:
  Schedule(Month m)
      : m_month(m), m_numDays(daysInMonth(m)), m_agenda(m_numDays) {}
  void addShift(const Employee&, int, ShiftType);
  void deleteShift(const Employee&, int);
  void moveShift(const Employee&, int, int);
  agenda_t agenda() const { return m_agenda; }
  shift_t shifts() const { return m_shifts; }
  Month month() const { return m_month; }
  // returns empty vector if employee has no shifts
  const std::vector<ShiftType> &shifts(const Employee &emp) const;
  const day_agenda_t& agenda(int day) const { return m_agenda[day]; }
  // TODO: get employee for employeeId
};
std::ostream &operator<<(std::ostream &, const Schedule &);
}  // namespace nsp

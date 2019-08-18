#pragma once
#include <date.h>
#include <employee.h>
#include <nsp_types.h>
#include <utils.h>
#include <unordered_map>
#include <vector>

namespace nsp {

using shift_t =
    std::unordered_map<Employee, std::vector<ShiftType>, EmployeeHash>;
using agenda_t =
    std::vector<std::unordered_map<Employee, ShiftType, EmployeeHash>>;

class Schedule {
 private:
  int m_numDays;
  shift_t m_shifts;
  agenda_t m_agenda;

 public:
  Schedule(Month m) : m_numDays(daysInMonth(m)), m_agenda(m_numDays) {}
  void addShift(const Employee&, int, ShiftType);
  void deleteShift(const Employee&, int);
  void moveShift(const Employee&, int, int);
  agenda_t agenda() const { return m_agenda; }
  shift_t shifts() const { return m_shifts; }
  //  void addEmployee(const Employee&);
};
std::ostream &operator<<(std::ostream &, const Schedule &);
}  // namespace nsp

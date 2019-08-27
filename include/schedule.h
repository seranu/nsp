#pragma once
#include <map>
#include <vector>
#include "date.h"
#include "employee.h"
#include "nsp_types.h"
#include "utils.h"

namespace nsp {

using day_agenda_t = std::map<Employee, ShiftType>;
using shift_t = std::map<Employee, std::vector<ShiftType>>;
using agenda_t = std::vector<day_agenda_t>;

class Schedule {
 private:
  Month m_month;
  int m_numDays;
  shift_t m_shifts;
  agenda_t m_agenda;

  const std::vector<ShiftType> &emptyShift() const;

 public:
  Schedule(Month m)
      : m_month(m), m_numDays(daysInMonth(m)), m_agenda(m_numDays) {}
  Schedule(const Schedule &) = default;
  Schedule(Schedule &&) = default;
  Schedule &operator=(const Schedule &) = default;
  Schedule &operator=(Schedule &&) = default;
  void addShift(const Employee&, int, ShiftType);
  void deleteShift(const Employee&, int);
  void moveShift(const Employee&, int, int);
  void switchShift(const Employee &, int, const Employee &, int);
  agenda_t agenda() const { return m_agenda; }
  shift_t shifts() const { return m_shifts; }
  Month month() const { return m_month; }
  // returns empty vector if employee has no shifts
  const std::vector<ShiftType> &shifts(const Employee &emp) const;
  const std::vector<ShiftType> &shifts(const size_t employeeId) const;
  const day_agenda_t& agenda(int day) const { return m_agenda[day]; }
};

struct ScheduleHash {
  std::size_t operator()(const Schedule &) const;
};

std::ostream &operator<<(std::ostream &, const Schedule &);
}  // namespace nsp

#pragma once
#include <functional>
#include "employee.h"
#include "schedule.h"

namespace nsp {
enum class ScheduleActionType { ADD, DELETE };

class ScheduleAction {
 private:
  Employee m_target;
  ScheduleActionType m_actionType;
  int m_day;
  ShiftType m_shiftType;
  ScheduleAction(const Employee& emp) : m_target(emp) {}

 public:
  static ScheduleAction createAddAction(const Employee&, int, ShiftType);
  static ScheduleAction createDeleteAction(const Employee&, int);
  void execute(Schedule& sch) const;
};
}  // namespace nsp

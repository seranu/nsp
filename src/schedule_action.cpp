#include "schedule_action.h"
#include <cassert>

namespace nsp {
ScheduleAction ScheduleAction::createAddAction(const Employee& emp, int day,
                                               ShiftType shiftType) {
  ScheduleAction act(emp);
  act.m_day = day;
  act.m_shiftType = shiftType;
  act.m_actionType = ScheduleActionType::ADD;
  return act;
}
ScheduleAction ScheduleAction::createDeleteAction(const Employee& emp,
                                                   int day) {
  ScheduleAction act(emp);
  act.m_day = day;
  act.m_actionType = ScheduleActionType::DELETE;
  return act;
}

void ScheduleAction::execute(Schedule& sch) const {
  switch (m_actionType) {
    case ScheduleActionType::ADD:
      sch.addShift(m_target, m_day, m_shiftType);
      break;
    case ScheduleActionType::DELETE:
      sch.deleteShift(m_target, m_day);
      break;
    default:
      assert(false);
  }
}

}  // namespace nsp

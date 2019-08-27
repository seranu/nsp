#include "schedule_action.h"
#include <cassert>
#include "log.h"

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
  LOG_DEBUG(" %s : %d", emp.name().c_str(), day);
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

std::string scheduleActionTypeToString(ScheduleActionType type) {
  static std::unordered_map<ScheduleActionType, std::string>
      s_scheduleActionTypes = {{ScheduleActionType::ADD, "Add"},
                               {ScheduleActionType::DELETE, "Delete"}};
  assert(s_scheduleActionTypes.find(type) != s_scheduleActionTypes.end());
  return s_scheduleActionTypes[type];
}

std::ostream& operator<<(std::ostream& out, const nsp::ScheduleAction& act) {
  return act.print(out);
}

std::ostream& ScheduleAction::print(std::ostream& out) const {
  out << "ScheduleAction: [ type: " << scheduleActionTypeToString(m_actionType);
  switch (m_actionType) {
    case ScheduleActionType::ADD:
      out << " " << m_target << " day : " << m_day + 1
          << " shiftType : " << shiftTypeToString(m_shiftType);
      break;
    case ScheduleActionType::DELETE:
      out << " " << m_target << " day : " << m_day + 1;
      break;
    default:
      assert(false);
  }
  return out;
}

}  // namespace nsp

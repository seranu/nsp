#include <gtest/gtest.h>
#include <schedule.h>

using namespace nsp;

class ScheduleTest : public ::testing::Test {
 public:
  ScheduleTest() : emp("Tester", Grade::Regular), sch(Month::August) {}

 protected:
  Employee emp;
  Schedule sch;
};

TEST_F(ScheduleTest, AddShift) {
  sch.addShift(emp, 22, ShiftType::NORMAL);
  sch.addShift(emp, 23, ShiftType::NORMAL);
  std::vector<ShiftType> expectedShifts(daysInMonth(Month::August),
                                        ShiftType::OFF);
  expectedShifts[22] = ShiftType::NORMAL;
  expectedShifts[23] = ShiftType::NORMAL;
  auto shifts = sch.shifts(emp);

  ASSERT_EQ(shifts.size(), 31);
  ASSERT_EQ(shifts, expectedShifts);

  auto agenda = sch.agenda();
  for (int i = 0; i < daysInMonth(Month::August); i++) {
    if (i == 22 || i == 23) {
      ASSERT_EQ(agenda[i].size(), 1);
      ASSERT_EQ(agenda[i][emp], ShiftType::NORMAL);
    } else {
      ASSERT_EQ(agenda[i].size(), 0);
    }
  }
}

TEST_F(ScheduleTest, RemoveShift) {
  sch.addShift(emp, 22, ShiftType::NORMAL);
  sch.addShift(emp, 23, ShiftType::NORMAL);
  sch.deleteShift(emp, 23);
  std::vector<ShiftType> expectedShifts(daysInMonth(Month::August),
                                        ShiftType::OFF);
  expectedShifts[22] = ShiftType::NORMAL;

  auto shifts = sch.shifts(emp);
  ASSERT_EQ(shifts, expectedShifts);
  auto agenda = sch.agenda();
  for (int i = 0; i < daysInMonth(Month::August); i++) {
    if (i == 22) {
      ASSERT_EQ(agenda[i].size(), 1);
      ASSERT_EQ(agenda[i][emp], ShiftType::NORMAL);
    } else {
      ASSERT_EQ(agenda[i].size(), 0);
    }
  }
}

TEST_F(ScheduleTest, MoveShift) {
  sch.addShift(emp, 22, ShiftType::NORMAL);
  sch.addShift(emp, 23, ShiftType::NORMAL);
  sch.moveShift(emp, 23, 1);
  std::vector<ShiftType> expectedShifts(daysInMonth(Month::August),
                                        ShiftType::OFF);
  expectedShifts[1] = ShiftType::NORMAL;
  expectedShifts[22] = ShiftType::NORMAL;

  auto shifts = sch.shifts(emp);
  ASSERT_EQ(shifts, expectedShifts);
  auto agenda = sch.agenda();
  for (int i = 0; i < daysInMonth(Month::August); i++) {
    if (i == 1 || i == 22) {
      ASSERT_EQ(agenda[i].size(), 1);
      ASSERT_EQ(agenda[i][emp], ShiftType::NORMAL);
    } else {
      ASSERT_EQ(agenda[i].size(), 0);
    }
  }
}

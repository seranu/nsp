#include <gtest/gtest.h>
#include "solution.h"

using namespace nsp;

class SolutionTest : public ::testing::Test {
 public:
  Schedule schedule;
  std::vector<Employee> employees;
  SolutionTest() : schedule(Month::September) {
    employees.emplace_back("Joana", Grade::Regular);
    employees.emplace_back("Iuliana", Grade::Regular);
    employees.emplace_back("Joan", Grade::Regular);

    schedule.addShift(employees[0], 1, ShiftType::NORMAL);
    schedule.addShift(employees[0], 2, ShiftType::NORMAL);
    schedule.addShift(employees[0], 3, ShiftType::NORMAL);
    schedule.addShift(employees[0], 4, ShiftType::NORMAL);
    schedule.addShift(employees[0], 5, ShiftType::NORMAL);
    schedule.addShift(employees[0], 29, ShiftType::NORMAL);
    schedule.addShift(employees[1], 1, ShiftType::NORMAL);
    schedule.addShift(employees[1], 12, ShiftType::NORMAL);
    schedule.addShift(employees[1], 11, ShiftType::NORMAL);
    schedule.addShift(employees[1], 29, ShiftType::NORMAL);
    schedule.addShift(employees[1], 9, ShiftType::NORMAL);
    schedule.addShift(employees[2], 22, ShiftType::NORMAL);
    schedule.addShift(employees[2], 29, ShiftType::NORMAL);
    schedule.addShift(employees[2], 1, ShiftType::NORMAL);
  }
};

TEST_F(SolutionTest, TestSolutionHashesDifferent_1) {
  SolutionHash ha;
  Solution sol(schedule);
  auto old = ha(sol);
  schedule.deleteShift(employees[0], 1);
  schedule.addShift(employees[0], 1, ShiftType::SHORT);
  Solution newSol(schedule);
  ASSERT_NE(old, ha(newSol));
}

TEST_F(SolutionTest, TestSolutionHashesDifferent_2) {
  SolutionHash ha;
  Schedule sch(schedule);
  Employee copy("Joana", Grade::Manager);
  sch.addShift(copy, 8, ShiftType::NORMAL);
  schedule.addShift(employees[0], 8, ShiftType::NORMAL);
  ASSERT_NE(ha(Solution(sch)), ha(Solution(schedule)));
}

TEST_F(SolutionTest, TestSolutionHashesDifferent_3) {
  SolutionHash ha;
  Schedule sch(schedule);
  sch.addShift(employees[1], 8, ShiftType::NORMAL);
  schedule.addShift(employees[0], 8, ShiftType::NORMAL);
  ASSERT_NE(ha(Solution(sch)), ha(Solution(schedule)));
}

TEST_F(SolutionTest, TestSolutionHashesEqual_1) {
  SolutionHash ha;
  Solution sol(schedule);
  auto oldHash = ha(sol);
  schedule.deleteShift(employees[0], 1);
  schedule.addShift(employees[0], 1, ShiftType::NORMAL);
  ASSERT_EQ(oldHash, ha(Solution(schedule)));
}

TEST_F(SolutionTest, TestSolutionHashesEqual_2) {
  SolutionHash ha;
  Schedule sch(schedule);
  sch.addShift(employees[2], 27, ShiftType::SHORT);
  schedule.addShift(employees[2], 27, ShiftType::SHORT);
  ASSERT_EQ(ha(Solution(sch)), ha(Solution(schedule)));
}

TEST_F(SolutionTest, TestSolutionHashesEqual_3) {
  SolutionHash ha;
  Schedule sch(schedule);
  sch.deleteShift(employees[0], 1);
  schedule.deleteShift(employees[0], 1);
  ASSERT_EQ(ha(Solution(sch)), ha(Solution(schedule)));
}

TEST_F(SolutionTest, TestSolutionHashesEqual_4) {
  SolutionHash ha;
  Schedule sch(schedule);
  Employee copy("Joana", Grade::Regular);
  sch.addShift(copy, 8, ShiftType::NORMAL);
  schedule.addShift(employees[0], 8, ShiftType::NORMAL);
  ASSERT_EQ(ha(Solution(sch)), ha(Solution(schedule)));
}

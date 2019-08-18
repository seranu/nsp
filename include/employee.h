#pragma once

#include <string>
#include "nsp_types.h"

namespace nsp
{
class Employee;
struct EmployeeHash {
  std::size_t operator()(const Employee &) const;
};

class Employee
{
private:
    std::string m_name;
    int m_minWeeklyHours;
    int m_maxWeeklyHours;
    Grade m_grade;
    size_t m_id;

   public:
    Employee(std::string name, int minHours, int maxHours,
             Grade grade = Grade::Regular)
        : m_name(move(name)),
          m_minWeeklyHours(minHours),
          m_maxWeeklyHours(maxHours),
          m_grade(grade) {
      EmployeeHash h;
      m_id = h(*this);
    }
    bool operator==(const Employee &other) const {
      EmployeeHash h;
      return m_id == h(other);
    }
    std::string name() const { return m_name; }
    int minWeeklyHours() const { return m_minWeeklyHours; }
    int maxWeeklyHours() const { return m_maxWeeklyHours; }
    Grade grade() const { return m_grade; }
    size_t id() const { return m_id; }
};
std::ostream &operator<<(std::ostream &, const Employee &);
}

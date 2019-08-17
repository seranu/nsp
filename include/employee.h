#pragma once

#include <string>
#include "nsp_types.h"

namespace nsp
{
class Employee
{
private:
    std::string m_name;
    int m_minWeeklyHours;
    int m_maxWeeklyHours;
    Grade m_grade;
public:
 Employee(std::string name, int minHours, int maxHours,
          Grade grade = Grade::Regular)
     : m_name(move(name)),
       m_minWeeklyHours(minHours),
       m_maxWeeklyHours(maxHours),
       m_grade(grade) {}

 std::string name() const { return m_name; }
 int minWeeklyHours() const { return m_minWeeklyHours; }
 int maxWeeklyHours() const { return m_maxWeeklyHours; }
 Grade grade() const { return m_grade; }
};

struct EmployeeHash
{
std::size_t operator() (const Employee&);
};

}

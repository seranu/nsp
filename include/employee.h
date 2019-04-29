#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__

#include <string>
#include "grade.h"

namespace nsp
{
struct EmployeeHash
{
std::size_t operator() (const Employee&);
};

class Employee
{
private:
    std::string m_name;
    int m_minMonthlyHours;
    int m_maxMonthlyHours;
    Grade m_grade;
public:
    Employee(std::string name, int minHours, int maxHours, Grade grade = Grade::Regular) 
        : m_name(move(name))
        , m_minMonthlyHours(minHours)
        , m_maxMonthlyHours(maxHours)
        , m_grade(grade)
    {
    }

    std::string name() const { return m_name; }
    int minMonthlyHours() const { return m_minMonthlyHours; }
    int maxMonthlyHours() const { return m_maxMonthlyHours; }
    Grade grade() const { return m_grade; }
};
}
#endif // __EMPLOYEE_H__
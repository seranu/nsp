#pragma once

#include <string>
#include "nsptypes.h"

namespace nsp
{
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


struct EmployeeHash
{
std::size_t operator() (const Employee&);
};

}
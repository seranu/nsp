#pragma once

#include <string>
#include "nsp_types.h"

namespace nsp
{
class Employee;
struct EmployeeHash {
  std::size_t operator()(const Employee &) const;
};

int roosterScore(Grade g);

class Employee
{
private:
    std::string m_name;
    Grade m_grade;
    size_t m_id;

   public:
    Employee(std::string name, Grade grade = Grade::Regular)
        : m_name(move(name)), m_grade(grade) {
      EmployeeHash h;
      m_id = h(*this);
    }
    std::string name() const { return m_name; }
    Grade grade() const { return m_grade; }
    size_t id() const { return m_id; }
    bool operator==(const Employee &other) const {
      EmployeeHash h;
      return m_id == h(other);
    }
    bool operator<(const Employee &other) const {
      return (m_name < other.name());
    }
};
std::ostream &operator<<(std::ostream &, const Employee &);
}

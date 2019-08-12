#pragma once
#include <date.h>
#include <employee.h>
#include <memory>
#include <vector>

namespace nsp
{
/*
 * IConfiguration for solution
 * 
 *
 */
class IRule;
class IConfiguration

{
public:
  Month month() const { return m_month; }
  std::vector<Employee> employees() const { return m_employees; }
  std::vector<std::shared_ptr<IRule>> rules() const { return m_rules; }
  virtual ~IConfiguration() {}

protected:
  Month m_month;
  std::vector<Employee> m_employees;
  std::vector<std::shared_ptr<IRule>> m_rules;

  virtual void init() = 0;
};
}

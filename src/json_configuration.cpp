#include <date.h>
#include <fstream>
#include <iostream>
#include <json_configuration.h>
#include <rules/rule_factory.h>
#include <utils.h>

namespace nsp {
void JsonConfiguration::init() {
    // read a JSON file
    std::ifstream in(m_configurationFileName.c_str());
    assert(in && "Invalid configuration file");
    json configJson;
    in >> configJson;
    parseConfigJson(configJson);
}

void JsonConfiguration::parseConfigJson(const json& in) {
    m_month = stringToMonth(in.at("month"));
    std::cout << in.at("month").dump(4) << std::endl;
    parseEmployees(in);
    parseGeneralRules(in);
}

void JsonConfiguration::parseEmployees(const json& in) {
  auto employeesJson = in["employees"];
  for (auto item : employeesJson) {
    m_employees.emplace_back(
        item["name"], item["schedule"]["min_monthly_hours"],
        item["schedule"]["max_monthly_hours"], stringToGrade(item["grade"]));

    std::cout << m_employees.back() << "\n";
    m_rules.emplace_back(std::make_shared<VacationDaysRule>(
        static_cast<std::vector<unsigned short>>(
            item["schedule"]["vacation"])));
    std::cout << "Added rule : " << m_rules.back() << "\n";
    EmployeeHash h;
    size_t empHash = h(m_employees.back());
    m_rules.emplace_back(std::make_shared<MinHoursPerWeekRule>(
        empHash, m_employees.back().minMonthlyHours()));
    // https://stackoverflow.com/questions/11905648/overloading-with-inhertiance-and-polymorphism
    std::cout << "Added rule : " << *(m_rules.back()) << "\n";

    m_rules.emplace_back(std::make_shared<MaxHoursPerWeekRule>(
        empHash, m_employees.back().maxMonthlyHours()));
    std::cout << "Added rule : " << m_rules.back() << "\n";
  }
}
void JsonConfiguration::parseEmployee(const json& in) {}
void JsonConfiguration::parseGeneralRules(const json& in) {}

} // namespace nsp

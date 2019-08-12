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
  for (auto employee : employeesJson) {
    m_employees.emplace_back(employee["name"],
                             employee["schedule"]["min_monthly_hours"],
                             employee["schedule"]["max_monthly_hours"],
                             stringToGrade(employee["grade"]));
    auto rule = std::make_shared<VacationDaysRule>(
        static_cast<std::vector<unsigned short>>(
            employee["schedule"]["vacation"]));
    m_rules.emplace_back(rule);
  }
}
void JsonConfiguration::parseEmployee(const json& in) {}
void JsonConfiguration::parseGeneralRules(const json& in) {}

} // namespace nsp

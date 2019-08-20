#include "json_configuration.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include "date.h"
#include "utils.h"

namespace nsp {
void JsonConfiguration::init() {
    // read a JSON file
    auto configJson = json::parse(m_jsonString);
    parseConfigJson(configJson);
}

void JsonConfiguration::parseConfigJson(const json& in) {
  m_month = stringToMonth(in["month"]);
  parseEmployees(in["employees"]);
  parseGeneralRules(in["general_rules"]);
}

void JsonConfiguration::parseEmployees(const json& in) {
  for (auto &item : in) {
    m_employees.emplace_back(item["name"], stringToGrade(item["grade"]));
    if (item.find("rules") != item.end()) {
      parseEmployeeRules(item["rules"], m_employees.back());
    }
  }
}

std::shared_ptr<ConsecutiveDaysRule>
JsonConfiguration::consecutiveDaysRuleFromJson(const json &in) {
  assert(in["type"].get<std::string>() == "consecutive_working_days");
  return std::make_shared<ConsecutiveDaysRule>(in["value"], in["penalty"]);
}

std::shared_ptr<MinHoursPerWeekRule>
JsonConfiguration::minHoursPerWeekRuleFromJson(const json &in,
                                               const Employee &emp) {
  assert(in["type"].get<std::string>() == "min_weekly_hours");
  return std::make_shared<MinHoursPerWeekRule>(emp.id(), in["value"],
                                               in["penalty"]);
}

std::shared_ptr<MaxHoursPerWeekRule>
JsonConfiguration::maxHoursPerWeekRuleFromJson(const json &in,
                                               const Employee &emp) {
  assert(in["type"].get<std::string>() == "max_weekly_hours");
  return std::make_shared<MaxHoursPerWeekRule>(emp.id(), in["value"],
                                               in["penalty"]);
}

std::shared_ptr<VacationDaysRule> JsonConfiguration::vacationDaysRuleFromJson(
    const json &in, const Employee &emp) {
  assert(in["type"].get<std::string>() == "vacation");
  return std::make_shared<VacationDaysRule>(emp.id(), in["value"],
                                            in["penalty"]);
}

std::shared_ptr<RoosterRequirementRule>
JsonConfiguration::roosteRequirementRuleFromJson(const json &in) {
  assert(in["type"].get<std::string>() == "rooster_requirement");
  return std::make_shared<RoosterRequirementRule>(stringToDay(in["day"]),
                                                  in["value"], in["penalty"]);
}

std::shared_ptr<ShopClosedRule>
JsonConfiguration::shopClosedRuleFromJson(const json &in) {
  assert(in["type"].get<std::string>() == "shop_closed");
  return std::make_shared<ShopClosedRule>(
      static_cast<std::vector<unsigned short>>(in["value"]), in["penalty"]);
}

void JsonConfiguration::parseEmployeeRules(const json &in,
                                           const Employee &emp) {
  for (auto &rule : in) {
    if (rule["type"].get<std::string>() == "min_weekly_hours") {
      m_rules.push_back(minHoursPerWeekRuleFromJson(rule, emp));
    } else if (rule["type"].get<std::string>() == "max_weekly_hours") {
      m_rules.push_back(maxHoursPerWeekRuleFromJson(rule, emp));
    } else if (rule["type"].get<std::string>() == "vacation") {
      m_rules.push_back(vacationDaysRuleFromJson(rule, emp));
    } else {
      assert(false && "Unknown rule type");
    }
  }
}

void JsonConfiguration::parseGeneralRules(const json &in) {
  for (auto rule : in) {
    if (rule["type"].get<std::string>() == "consecutive_working_days") {
      m_rules.emplace_back(consecutiveDaysRuleFromJson(rule));
    } else if (rule["type"].get<std::string>() == "rooster_requirement") {
      m_rules.emplace_back(roosteRequirementRuleFromJson(rule));
    } else if (rule["type"].get<std::string>() == "shop_closed") {
      m_rules.emplace_back(shopClosedRuleFromJson(rule));
    } else {
      assert(false && "Unknown general rule");
    }
  }
}

} // namespace nsp

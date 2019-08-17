#include <cassert>
#include <date.h>
#include <fstream>
#include <iostream>
#include <json_configuration.h>
#include <rules/rule_factory.h>
#include <utils.h>

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
    m_employees.emplace_back(item["name"], item["schedule"]["min_weekly_hours"],
                             item["schedule"]["max_weekly_hours"],
                             stringToGrade(item["grade"]));
    if (item["schedule"].find("vacation") != item["schedule"].end()) {
      m_rules.emplace_back(std::make_shared<VacationDaysRule>(
          static_cast<std::vector<unsigned short>>(
              item["schedule"]["vacation"])));
    }
    EmployeeHash h;
    size_t empHash = h(m_employees.back());
    m_rules.emplace_back(std::make_shared<MinHoursPerWeekRule>(
        empHash, m_employees.back().minWeeklyHours()));

    m_rules.emplace_back(std::make_shared<MaxHoursPerWeekRule>(
        empHash, m_employees.back().maxWeeklyHours()));
  }
}
std::shared_ptr<ConsecutiveDaysRule>
JsonConfiguration::consecutiveDaysRuleFromJson(const json &in) {
  assert(in["type"].get<std::string>() == "consecutive_working_days");
  return std::make_shared<ConsecutiveDaysRule>(in["value"]);
}

std::shared_ptr<RoosterRequirementRule>
JsonConfiguration::roosteRequirementRuleFromJson(const json &in) {
  assert(in["type"].get<std::string>() == "rooster_requirement");
  return std::make_shared<RoosterRequirementRule>(stringToDay(in["day"]),
                                                  in["value"]);
}

std::shared_ptr<ShopClosedRule>
JsonConfiguration::shopClosedRuleFromJson(const json &in) {
  assert(in["type"].get<std::string>() == "shop_closed");
  return std::make_shared<ShopClosedRule>(
      static_cast<std::vector<unsigned short>>(in["value"]));
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

#pragma once
#include <date.h>
#include <iconfiguration.h>
#include <rules/include_all_rules.h>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

namespace nsp
{
class JsonConfiguration : public IConfiguration
{
public:
 JsonConfiguration(const std::string &jsonString) : m_jsonString(jsonString) {
   init();
  }

private:
 std::string m_jsonString;
 void init() override;
 void parseConfigJson(const json &in);
 void parseEmployees(const json &in);
 void parseEmployeeRules(const json &in, const Employee &emp);
 void parseGeneralRules(const json &in);
 std::shared_ptr<ConsecutiveDaysRule> consecutiveDaysRuleFromJson(
     const json &in);
 std::shared_ptr<MinHoursPerWeekRule> minHoursPerWeekRuleFromJson(
     const json &in, const Employee &emp);
 std::shared_ptr<MaxHoursPerWeekRule> maxHoursPerWeekRuleFromJson(
     const json &in, const Employee &emp);
 std::shared_ptr<VacationDaysRule> vacationDaysRuleFromJson(
     const json &in, const Employee &emp);

 std::shared_ptr<RoosterRequirementRule> roosteRequirementRuleFromJson(
     const json &in);
 std::shared_ptr<ShopClosedRule> shopClosedRuleFromJson(const json &in);
};
}

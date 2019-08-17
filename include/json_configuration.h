#pragma once
#include <date.h>
#include <iconfiguration.h>
#include <memory>
#include <nlohmann/json.hpp>
#include <rules/rule_factory.h>
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
 void parseGeneralRules(const json &in);
 std::shared_ptr<ConsecutiveDaysRule> consecutiveDaysRuleFromJson(
     const json &in);
 std::shared_ptr<RoosterRequirementRule> roosteRequirementRuleFromJson(
     const json &in);
 std::shared_ptr<ShopClosedRule> shopClosedRuleFromJson(const json &in);
};
}

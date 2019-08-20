#include <configuration_factory.h>
#include <gtest/gtest.h>
#include <rules/include_all_rules.h>

using namespace nsp;

// class ConfigurationTest : public ::testing::Test {
// public:
//  ConfigurationTest()
//      : m_configuration(ConfigurationFactory::create(
//            ConfigurationType::JSON, "../example/config.json")) {}
//  std::unique_ptr<IConfiguration> m_configuration;
//};

TEST(ConfigurationTest, Month) {
  auto m_configuration = ConfigurationFactory::createFromString(
      ConfigurationType::JSON,
      //      "{ \"month\": \"august\", \"employees\" : [], \"general_rules\":
      //      [] }");

      R"({ "month": "august", "employees" : [], "general_rules": [] })");
  ASSERT_EQ(m_configuration->month(), Month::August);
}

TEST(ConfigurationTest, Employee) {
  auto m_configuration =
      ConfigurationFactory::createFromString(ConfigurationType::JSON, R"({ 
        "month": "august",
        "employees" : 
        [
          {
            "name" : "Oana",
            "rules" : [
              { "type": "min_weekly_hours", "value": 35, "penalty": 150 },
              { "type": "max_weekly_hours", "value": 45, "penalty": 170 },
              { "type": "vacation", "value": [1, 2, 5], "penalty": 50 }
            ],
            "grade" : "manager"
          }
        ],
        "general_rules" : [] })");

  const auto& employees = m_configuration->employees();
  ASSERT_EQ(employees.size(), 1);
  const auto& employee = employees[0];

  ASSERT_EQ(employee.name(), "Oana");
  ASSERT_EQ(employee.grade(), Grade::Manager);
  const auto& rules = m_configuration->rules();
  ASSERT_EQ(rules.size(), 3);
  for (auto& rule : rules) {
    if (rule->type() == RuleType::MinHoursPerWeek) {
      auto mhpwRule = dynamic_cast<const MinHoursPerWeekRule*>(rule.get());
      ASSERT_EQ(mhpwRule->value(), 35);
      ASSERT_EQ(mhpwRule->penalty(), 150);
    } else if (rule->type() == RuleType::MaxHoursPerWeek) {
      auto mhpwRule = dynamic_cast<const MaxHoursPerWeekRule*>(rule.get());
      ASSERT_EQ(mhpwRule->value(), 45);
      ASSERT_EQ(mhpwRule->penalty(), 170);
    } else if (rule->type() == RuleType::VacationDays) {
      auto vdRule = dynamic_cast<const VacationDaysRule*>(rule.get());
      ASSERT_EQ(vdRule->value(), std::vector<unsigned short>({1, 2, 5}));
      ASSERT_EQ(vdRule->penalty(), 50);
    }
  }
}

TEST(ConfigurationTest, TestConsecutiveDaysRule) {
  auto m_configuration = ConfigurationFactory::createFromString(
      ConfigurationType::JSON,
      R"({ "month": "august", "employees":[], "general_rules": [ { "type": "consecutive_working_days", "value": 5, "penalty": 100 } ] })");
  const auto& rules = m_configuration->rules();
  ASSERT_EQ(rules.size(), 1);
  const auto& rule = rules[0];
  ASSERT_EQ(rule->type(), RuleType::ConsecutiveDays);
  auto cdRule = dynamic_cast<const ConsecutiveDaysRule*>(rule.get());
  ASSERT_NE(cdRule, nullptr);
  ASSERT_EQ(cdRule->value(), 5);
  ASSERT_EQ(cdRule->penalty(), 100);
}

TEST(ConfigurationTest, TestRoosterRequirementRule) {
  auto m_configuration = ConfigurationFactory::createFromString(
      ConfigurationType::JSON,
      R"({ "month": "august", "employees":[], "general_rules": [ { "type": "rooster_requirement",
"day": "monday", "value": 200, "penalty": 100 } ] })");
  const auto& rules = m_configuration->rules();
  ASSERT_EQ(rules.size(), 1);
  ASSERT_EQ(rules[0]->type(), RuleType::RoosterRequirement);
  auto* rrRule = dynamic_cast<const RoosterRequirementRule*>(rules[0].get());
  ASSERT_NE(rrRule, nullptr);
  const auto& [day, value] = rrRule->value();
  ASSERT_EQ(day, Day::Monday);
  ASSERT_EQ(value, 200);
  ASSERT_EQ(rrRule->penalty(), 100);
}

TEST(ConfigurationTest, TestShopClosedRule) {
  auto m_configuration = ConfigurationFactory::createFromString(
      ConfigurationType::JSON,
      R"({ "month": "august", "employees":[], "general_rules": [ { "type": "shop_closed",
"value": [ 3, 21 ], "penalty": 100 } ] })");
  const auto& rules = m_configuration->rules();
  ASSERT_EQ(rules.size(), 1);
  ASSERT_EQ(rules[0]->type(), RuleType::ShopClosed);
  const auto* scRule = dynamic_cast<const ShopClosedRule*>(rules[0].get());
  ASSERT_NE(scRule, nullptr);
  ASSERT_EQ(scRule->value(), std::vector<unsigned short>({3, 21}));
  ASSERT_EQ(scRule->penalty(), 100);
}

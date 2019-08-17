#include <configuration_factory.h>
#include <gtest/gtest.h>
#include <rules/rule_factory.h>

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
            "schedule" : { "min_weekly_hours" : 35, "max_weekly_hours": 45 },
            "grade" : "manager"
          }
        ],
        "general_rules" : [] })");

  const auto& employees = m_configuration->employees();
  ASSERT_EQ(employees.size(), 1);
  const auto& employee = employees[0];

  ASSERT_EQ(employee.name(), "Oana");
  ASSERT_EQ(employee.grade(), Grade::Manager);
  ASSERT_EQ(employee.minWeeklyHours(), 35);
  ASSERT_EQ(employee.maxWeeklyHours(), 45);
}

TEST(ConfigurationTest, TestConsecutiveDaysRule) {
  auto m_configuration = ConfigurationFactory::createFromString(
      ConfigurationType::JSON,
      R"({ "month": "august", "employees":[], "general_rules": [ { "type": "consecutive_working_days", "value": 5, "penalty": "" } ] })");
  const auto& rules = m_configuration->rules();
  ASSERT_EQ(rules.size(), 1);
  const auto& rule = rules[0];
  ASSERT_EQ(rule->type(), RuleType::ConsecutiveDays);
  auto cdRule = dynamic_cast<const ConsecutiveDaysRule*>(rule.get());
  ASSERT_NE(cdRule, nullptr);
  ASSERT_EQ(cdRule->value(), 5);
}

TEST(ConfigurationTest, TestRoosterRequirementRule) {
  auto m_configuration = ConfigurationFactory::createFromString(
      ConfigurationType::JSON,
      R"({ "month": "august", "employees":[], "general_rules": [ { "type": "rooster_requirement",
"day": "monday", "value": 200, "penalty": "" } ] })");
  const auto& rules = m_configuration->rules();
  ASSERT_EQ(rules.size(), 1);
  ASSERT_EQ(rules[0]->type(), RuleType::RoosterRequirement);
  auto* rrRule = dynamic_cast<const RoosterRequirementRule*>(rules[0].get());
  ASSERT_NE(rrRule, nullptr);
  const auto& [day, value] = rrRule->value();
  ASSERT_EQ(day, Day::Monday);
  ASSERT_EQ(value, 200);
}

TEST(ConfigurationTest, TestShopClosedRule) {
  auto m_configuration = ConfigurationFactory::createFromString(
      ConfigurationType::JSON,
      R"({ "month": "august", "employees":[], "general_rules": [ { "type": "shop_closed",
"value": [ 3, 21 ], "penalty": "" } ] })");
  const auto& rules = m_configuration->rules();
  ASSERT_EQ(rules.size(), 1);
  ASSERT_EQ(rules[0]->type(), RuleType::ShopClosed);
  const auto* scRule = dynamic_cast<const ShopClosedRule*>(rules[0].get());
  ASSERT_NE(scRule, nullptr);
}

TEST(ConfigurationTest, TestMinHoursPerWeekRules) {
  auto m_configuration =
      ConfigurationFactory::createFromString(ConfigurationType::JSON, R"({ 
        "month": "august",
        "employees" : 
        [
          {
            "name" : "Oana",
            "schedule" : { "min_weekly_hours" : 35, "max_weekly_hours": 45 },
            "grade" : "manager"
          }
        ],
        "general_rules" : [] })");
  const auto& rules = m_configuration->rules();
  ASSERT_EQ(rules.size(), 2);
  bool found = false;
  for (auto& rule : rules) {
    if (rule->type() == RuleType::MinHoursPerWeek) {
      auto mhpwRule = dynamic_cast<const MinHoursPerWeekRule*>(rule.get());
      ASSERT_NE(mhpwRule, nullptr);
      ASSERT_EQ(mhpwRule->value(), 35);
      found = true;
    }
  }
  ASSERT_TRUE(found);
}

TEST(ConfigurationTest, TestMaxHoursPerWeekRules) {
  auto m_configuration =
      ConfigurationFactory::createFromString(ConfigurationType::JSON, R"({ 
        "month": "august",
        "employees" : 
        [
          {
            "name" : "Oana",
            "schedule" : { "min_weekly_hours" : 35, "max_weekly_hours": 45 },
            "grade" : "manager"
          }
        ],
        "general_rules" : [] })");
  const auto& rules = m_configuration->rules();
  ASSERT_EQ(rules.size(), 2);
  bool found = false;
  for (auto& rule : rules) {
    if (rule->type() == RuleType::MaxHoursPerWeek) {
      auto mhpwRule = dynamic_cast<const MaxHoursPerWeekRule*>(rule.get());
      ASSERT_NE(mhpwRule, nullptr);
      ASSERT_EQ(mhpwRule->value(), 45);
      found = true;
    }
  }
  ASSERT_TRUE(found);
}

TEST(ConfigurationTest, TestVacationDays) {
  auto m_configuration =
      ConfigurationFactory::createFromString(ConfigurationType::JSON, R"({ 
        "month": "august",
        "employees" : 
        [
          {
            "name" : "Oana",
            "schedule" : { "min_weekly_hours" : 35, "max_weekly_hours": 45, "vacation": [1, 21] },
            "grade" : "manager"
          }
        ],
        "general_rules" : [] })");
  const auto& rules = m_configuration->rules();
  ASSERT_EQ(rules.size(), 3);
  bool found = false;
  for (auto& rule : rules) {
    if (rule->type() == RuleType::VacationDays) {
      auto vdRule = dynamic_cast<const VacationDaysRule*>(rule.get());
      ASSERT_NE(vdRule, nullptr);
      ASSERT_EQ(vdRule->value(), std::vector<unsigned short>({1, 21}));
      found = true;
    }
  }
  ASSERT_TRUE(found);
}

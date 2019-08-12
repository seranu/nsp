#pragma once
#include <date.h>
#include <iconfiguration.h>
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
  JsonConfiguration(const std::string &fileName)
      : m_configurationFileName(fileName) {
    init();
  }

private:
  std::string m_configurationFileName;
  void init() override;
  void parseConfigJson(const json& in);
  void parseEmployees(const json& in);
  void parseEmployee(const json& in);
  void parseGeneralRules(const json& in);
};
}

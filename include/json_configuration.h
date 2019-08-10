#pragma once
#include <date.h>
#include <iconfiguration.h>
#include <memory>
#include <string>
#include <vector>

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
};
}

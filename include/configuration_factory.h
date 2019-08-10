#pragma once
#include <memory>
#include <iconfiguration.h>

namespace nsp
{
enum class ConfigurationType
{
    JSON
};

class ConfigurationFactory
{
public:
   static std::unique_ptr<IConfiguration> create(ConfigurationType type, const std::string& fileName);
};
}

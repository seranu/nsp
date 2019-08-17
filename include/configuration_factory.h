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
 static std::unique_ptr<IConfiguration> createFromFile(
     ConfigurationType type, const std::string& fileName);
 static std::unique_ptr<IConfiguration> createFromString(
     ConfigurationType type, const std::string& configString);
};
}

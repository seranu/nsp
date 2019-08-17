#include <configuration_factory.h>
#include <json_configuration.h>
#include <boost/filesystem/string_file.hpp>

namespace nsp
{
std::unique_ptr<IConfiguration> ConfigurationFactory::createFromFile(
    ConfigurationType type, const std::string& fileName) {
  std::string configString;
  boost::filesystem::load_string_file(fileName, configString);
  return createFromString(type, configString);
}
std::unique_ptr<IConfiguration> ConfigurationFactory::createFromString(
    ConfigurationType type, const std::string& configString) {
  switch (type) {
    case ConfigurationType::JSON:
      return std::make_unique<JsonConfiguration>(configString);
    default:
        assert(false && "Unknown configuration type");
    }
    return nullptr;
}
}  // namespace nsp

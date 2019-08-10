#include <configuration_factory.h>
#include <json_configuration.h>

namespace nsp
{
std::unique_ptr<IConfiguration>
ConfigurationFactory::create(ConfigurationType type,
                             const std::string& fileName) {
    switch (type) {
    case ConfigurationType::JSON:
        return std::make_unique<JsonConfiguration>(fileName);
    default:
        assert(false && "Unknown configuration type");
    }
    return nullptr;
}
}

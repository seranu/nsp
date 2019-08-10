#include <fstream>
#include <iostream>
#include <json_configuration.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace nsp {
void JsonConfiguration::init() {
    // read a JSON file
    std::ifstream in(m_configurationFileName.c_str());
    assert(in && "Invalid configuration file");
    json configJson;
    in >> configJson;
    std::cout << configJson.dump(4) << std::endl;
}
} // namespace nsp

#pragma once
#include <string>

namespace nsp
{
class Configuration
{
private:
    std::string m_fileName;


    Configuration(const std::string& fileName)
        : m_fileName(fileName)
        {
            init();
        }

    void init();
public:
    static Configuration fromFile(const std::string& fileName);
};
}
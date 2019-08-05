#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <string>

namespace nsp
{
/*
 * Configuration for solution
 * 
 *
 */
class Configuration

{
private:
public:
    static Configuration fromFile(const std::string& fileName);
};
}
#endif // __CONFIGURATION_H__

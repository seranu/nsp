#pragma once
#include <iconfiguration.h>
#include <rules/irule.h>

namespace nsp {
std::ostream &operator<<(std::ostream &, const IConfiguration &);
std::ostream &operator<<(std::ostream &, const IRule &);
}  // namespace nsp

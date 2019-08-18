#pragma once

#include <schedule.h>
#include "nsp_types.h"

namespace nsp
{
class IRule
{
public:
    virtual RuleType type() const = 0;
    virtual bool satisfied(const Schedule& schedule) = 0;
    virtual std::string print() const = 0;
    virtual ~IRule() {}
};
}

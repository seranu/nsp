#pragma once

#include "nsptypes.h"

namespace nsp
{
class IRule
{
public:
    virtual RuleType type() const = 0;
    virtual bool satisfied(const Schedule& schedule) = 0;
    virtual Penalty penalty() const = 0;
    virtual ~IRule() {}
};
}

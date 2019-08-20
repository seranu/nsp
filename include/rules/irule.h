#pragma once

#include <schedule.h>
#include "nsp_types.h"

namespace nsp
{
class IRule
{
public:
    virtual RuleType type() const = 0;
    // returns the penalty
    virtual int apply(const Schedule& schedule) = 0;
    virtual std::string print() const = 0;
    int penalty() const { return m_penalty; }
    virtual ~IRule() {}

   protected:
    int m_penalty;
    void setPenalty(int penalty) { m_penalty = penalty; }
};
}

#pragma once

#include "nsptypes.h"
#include <memory>
#include <vector>

namespace nsp
{
class Solution;
class IRule;
class Configuration;
class RuleEngine
{
private:
    RuleEngine() {}
    std::vector<std::unique_ptr<IRule>> m_rules;
public:
    static RuleEngine createFromConfiguration(const Configuration&);
    Penalty computePenalty(const Solution&) const;
    bool valid(const Solution&) const;
};
}
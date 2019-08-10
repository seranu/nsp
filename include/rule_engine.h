#pragma once

#include "irule.h"
#include "nsp_types.h"
#include <memory>
#include <vector>

namespace nsp
{
class Solution;
class Configuration;
class RuleEngine
{
private:
    RuleEngine() {}
    std::vector<std::shared_ptr<IRule>> m_rules;
public:
    static RuleEngine createFromConfiguration(const Configuration&);
    Penalty computePenalty(const Solution&) const;
    bool valid(const Solution&) const;
};
}

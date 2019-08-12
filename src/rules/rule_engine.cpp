#include <iconfiguration.h>
#include <rules/rule_engine.h>

namespace nsp {
std::unique_ptr<RuleEngine>
RuleEngine::createFromConfiguration(const IConfiguration &configuration) {
  return std::make_unique<RuleEngine>(configuration.rules());
}

Penalty RuleEngine::computePenalty(const Solution &) const {}

bool RuleEngine::valid(const Solution &) const {}

} // namespace nsp

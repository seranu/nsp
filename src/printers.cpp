#include <printers.h>
namespace nsp {
std::ostream &operator<<(std::ostream &os, const IRule &rule) {
  os << rule.print();
  return os;
}

std::ostream &operator<<(std::ostream &os, const IConfiguration &config) {
  os << "\n********** Configuration **************\n";
  os << "Month: " << monthToString(config.month()) << "\n";
  os << "Employees: \n";
  for (const auto &employee : config.employees()) {
    os << "\t" << employee << "\n";
  }
  os << "Rules: \n";
  for (const auto &rule : config.rules()) {
    os << "\t" << *rule << "\n";
  }
  os << "***************************************\n";
  return os;
}
}  // namespace nsp

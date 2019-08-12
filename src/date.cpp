#include <algorithm>
#include <date.h>
#include <iostream>
#include <unordered_map>

namespace nsp
{

Month stringToMonth(std::string month) {
  static std::unordered_map<std::string, Month> s_months = {
      {"january", Month::January},
      {"february", Month::February},
      {"march", Month::March},
      {"april", Month::April},
      {"may", Month::May},
      {"june", Month::June},
      {"july", Month::July},
      {"august", Month::August},
      {"september", Month::September},
      {"october", Month::October},
      {"november", Month::November},
      {"december", Month::December}};
  std::transform(month.begin(), month.end(), month.begin(), ::tolower);
  assert(s_months.find(month) != s_months.end() && "Unknown month!");
  return s_months[month];
}

Day stringToDay(std::string day) {
  static std::unordered_map<std::string, Day> s_days = {
      {"sunday", Day::Sunday},     {"monday", Day::Monday},
      {"tuesday", Day::Tuesday},   {"wednesday", Day::Wednesday},
      {"thursday", Day::Thursday}, {"friday", Day::Friday},
      {"saturday", Day::Saturday}};
  std::transform(day.begin(), day.end(), day.begin(), ::tolower);
  assert(s_days.find(day) != s_days.end() && "Unknown day!");
  return s_days[day];
}

}

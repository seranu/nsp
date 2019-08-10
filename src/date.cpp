#include <date.h>
#include <unordered_map>

namespace nsp
{

Month stringToMonth(const std::string &month) {
    static std::unordered_map<std::string, Month> s_months = {
        {"January", Month::January},
        {"February", Month::February},
        {"March", Month::March},
        {"April", Month::April},
        {"May", Month::May},
        {"June", Month::June},
        {"July", Month::July},
        {"August", Month::August},
        {"September", Month::September},
        {"October", Month::October},
        {"November", Month::November},
        {"December", Month::December}};
    assert(s_months.find(month) != s_months.end() && "Unknown month!");
    return s_months[month];
}

Day stringToDay(const std::string& day) {
    static std::unordered_map<std::string, Day> s_days = {
        {"Sunday", Day::Sunday},     {"Monday", Day::Monday},
        {"Tuesday", Day::Tuesday},   {"Wednesday", Day::Wednesday},
        {"Thursday", Day::Thursday}, {"Friday", Day::Friday},
        {"Saturday", Day::Saturday}};
    assert(s_days.find(day) != s_days.end() && "Unknown day!");
    return s_days[day];
}

}

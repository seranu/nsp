#pragma once
#include <cassert>
#include <string>

namespace nsp
{
enum class Day: unsigned
{
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

enum class Month: unsigned
{
    January = 0,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

Month stringToMonth(const std::string&);
Day stringToDay(const std::string&);

class Date
{
private:
    unsigned m_day;
    unsigned m_month;
    unsigned m_year;
public:
    Date(unsigned day, unsigned month, unsigned year)
        : m_day(day)
        , m_month(month)
        , m_year(year)
    {
        assert(m_day >= 0 && m_day <= 31);
        assert(m_month >= 0 && m_month <= 12);
        assert(m_year >= 0);
    }

    Day dayOfWeek() const {
        // awsome formula ripped of wikipedia
        auto d = m_day, m = m_month, y = m_year;
        return static_cast<Day>((d+=m<3?y--:y-2,23*m/9+d+4+y/4-y/100+y/400)%7);
    }
};
}

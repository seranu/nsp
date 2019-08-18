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

int currentYear();
Day dayOfWeek(int day, int month, int year);
Day dayOfWeek(int day, Month month, int year);
Day nextDay(Day);
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

    Day dayOfWeek() const { return nsp::dayOfWeek(m_day, m_month, m_year); }
};
}

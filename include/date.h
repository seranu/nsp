#ifndef __DATE_H__
#define __DATE_H__

#include <cassert>

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
        auto d = m_day, m = m_month, y = m_year;
        return static_cast<Day>((d+=m<3?y--:y-2,23*m/9+d+4+y/4-y/100+y/400)%7);
    }
};
}
#endif //__DATE_H__

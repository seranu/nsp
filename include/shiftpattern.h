#ifndef __SHIFTPATTERN_H__
#define __SHIFTPATTERN_H__

#include <vector>

namespace nsp
{
enum class ShiftType : int
{
    NORMAL = 10,
    SHORT = 8
};

typedef std::vector<ShiftType> ShiftPattern;

}
#endif // __SHIFTPATTERN_H__
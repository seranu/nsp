#include <date.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <unordered_map>

namespace nsp
{
int currentYear() {
  time_t theTime = time(NULL);
  struct tm *aTime = localtime(&theTime);
  return aTime->tm_year + 1900;
}

Day dayOfWeek(int d, int m, int y) {
  // awsome formula ripped of wikipedia
  return static_cast<Day>((d += m < 3 ? y-- : y - 2,
                           23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) %
                          7);
}

Day dayOfWeek(int d, Month month, int y) {
  return dayOfWeek(d, static_cast<int>(month) + 1, y);
}

Day nextDay(Day d) {
  return static_cast<Day>((static_cast<unsigned>(d) + 1) % 7);
}

}  // namespace nsp

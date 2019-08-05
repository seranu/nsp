#include <gtest/gtest.h>
#include <date.h>

using namespace nsp;

TEST(TestDate, Today)
{
    Date today(5, 8, 2019);
    EXPECT_EQ(today.dayOfWeek(), Day::Monday);
}

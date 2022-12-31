#include <gtest/gtest.h>

#include "calc.h"

TEST(addTest, simple)
{
    EXPECT_TRUE(add(1, 2) == 3);
}



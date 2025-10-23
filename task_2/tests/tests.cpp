#include <gtest/gtest.h>
#include "eleven.h"

TEST(Eleven, ParseAndToString) {
    Eleven a("0");
    EXPECT_EQ(a.toString(), "0");
    Eleven b("A9");
    EXPECT_EQ(b.toString(), "A9");
}

TEST(Eleven, Add) {
    Eleven a("A9");           // 119(10)
    Eleven b("25");             // 25(10)
    Eleven c = a.add(b);        // 144(10)
    EXPECT_TRUE(c.isGreater(a));
    EXPECT_EQ(c.subtract(a).toString(), b.toString());
}

TEST(Eleven, SubNonNegative) {
    Eleven a("100");           // 1*11^2 = 121
    Eleven b("A");             // 10
    Eleven d = a.subtract(b);         // 111
    EXPECT_EQ(d.toString(), "A1"); // 121 - 10 = 111(10) -> base11: 9*11 + 1 = "A1"
}

TEST(Eleven, Compare) {
    Eleven a("1A"); // 1*11 + 10 = 21
    Eleven b("20"); // 2*11 + 0  = 22
    EXPECT_TRUE(a.isLess(b));
    EXPECT_FALSE(a.isEqual(b));
}

TEST(Eleven, SubThrowsOnNegative) {
    Eleven small("5");
    Eleven big("10");
    EXPECT_THROW(small.subtract(big), std::underflow_error);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

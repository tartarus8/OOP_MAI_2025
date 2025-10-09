#include <gtest/gtest.h>
#include "eleven.h"

TEST(Eleven, ParseAndToString) {
    Eleven z("0");
    EXPECT_TRUE(z.isZero());
    Eleven a("A9");           // 119 (10*11+9)
    EXPECT_EQ(a.toString(), "A9");
}

TEST(Eleven, Add) {
    Eleven a("A9");           // 119
    Eleven b(25);             // 25
    auto c = a.add(b);        // 144(10) -> в base11: 11*13 + 1? Проверим просто через интерфейс:
    EXPECT_TRUE(c.greaterThan(a));
    EXPECT_EQ(c.sub(a).toString(), b.toString());
}

TEST(Eleven, SubNonNegative) {
    Eleven a("100");           // 1*11^2 = 121
    Eleven b("A");             // 10
    auto d = a.sub(b);         // 111
    EXPECT_EQ(d.toString(), "A1"); // 121 - 10 = 111(10) -> base11: 9*11 + 1 = "91"
}

TEST(Eleven, Compare) {
    Eleven x("1A"); // 1*11 + 10 = 21
    Eleven y("20"); // 2*11 + 0  = 22
    EXPECT_TRUE(x.lessThan(y));
    EXPECT_FALSE(x.equals(y));
}

TEST(Eleven, SubThrowsOnNegative) {
    Eleven small("5");
    Eleven big("10");
    EXPECT_THROW(small.sub(big), std::invalid_argument);
}

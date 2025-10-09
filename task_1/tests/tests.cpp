#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#define main turkish_main
#include "../src/task_1.cpp"
#undef main
using namespace std;

static int RunMainWithInput(const string& in, string& out) {
    // Backup original buffers
    streambuf* cin_backup = cin.rdbuf();
    streambuf* cout_backup = cout.rdbuf();

    istringstream iss(in);
    ostringstream oss;
    cin.rdbuf(iss.rdbuf());
    cout.rdbuf(oss.rdbuf());

    int rc = turkish_main();   // call the renamed main

    // Restore buffers
    cin.rdbuf(cin_backup);
    cout.rdbuf(cout_backup);

    out = oss.str();
    return rc;
}

// -------------------------- Unit tests for helpers ---------------------------

TEST(TurkishNumbers, ZeroToNine_Valid) {
    // capture cout by swapping rdbuf
    ostringstream oss;
    auto* old = cout.rdbuf(oss.rdbuf());

    EXPECT_EQ(OK, zero_to_nine(0));
    EXPECT_EQ("sıfır", oss.str());

    // restore and reuse for another digit
    cout.rdbuf(old);
    oss.str(""); oss.clear();
    cout.rdbuf(oss.rdbuf());

    EXPECT_EQ(OK, zero_to_nine(9));
    EXPECT_EQ("dokuz", oss.str());

    cout.rdbuf(old);
}

TEST(TurkishNumbers, ZeroToNine_Invalid) {
    ostringstream oss;
    auto* old = cout.rdbuf(oss.rdbuf());

    EXPECT_EQ(WRONG_INPUT, zero_to_nine(11));
    EXPECT_EQ("error: input isn't a supported digit", oss.str());

    cout.rdbuf(old);
}

TEST(TurkishNumbers, Decades_Valid) {
    ostringstream oss;
    auto* old = cout.rdbuf(oss.rdbuf());

    EXPECT_EQ(OK, decades(1));
    EXPECT_EQ("on", oss.str());

    cout.rdbuf(old);
    oss.str(""); oss.clear();
    cout.rdbuf(oss.rdbuf());

    EXPECT_EQ(OK, decades(7));
    EXPECT_EQ("yetmiş", oss.str());

    cout.rdbuf(old);
}

TEST(TurkishNumbers, Decades_Invalid) {
    ostringstream oss;
    auto* old = cout.rdbuf(oss.rdbuf());

    EXPECT_EQ(WRONG_INPUT, decades(0));
    EXPECT_EQ("error: input isn't a supported digit", oss.str());

    cout.rdbuf(old);
}

TEST(TurkishNumbersE2E, SingleDigit) {
    string out;
    int rc = RunMainWithInput("0\n", out);
    EXPECT_EQ(0, rc);
    EXPECT_EQ("sıfır", out);
}

TEST(TurkishNumbersE2E, ExactDecade) {
    string out;
    int rc = RunMainWithInput("70\n", out);
    EXPECT_EQ(0, rc);
    EXPECT_EQ("yetmiş", out);
}

TEST(TurkishNumbersE2E, CompositeNumber) {
    string out;
    int rc = RunMainWithInput("42\n", out);
    EXPECT_EQ(0, rc);
    // Program prints "kırk iki" without newline
    EXPECT_EQ("kırk iki", out);
}

TEST(TurkishNumbersE2E, InvalidOutOfRange) {
    string out;
    int rc = RunMainWithInput("100\n", out);
    EXPECT_EQ(WRONG_INPUT, rc);
    EXPECT_EQ("error: input isn't a supported number", out);
}

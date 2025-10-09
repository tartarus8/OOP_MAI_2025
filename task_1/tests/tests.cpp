#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

using namespace std;

#define main turkish_main
#include "../src/task_1.cpp"
#undef main

static int RunMainWithInput(const string& in, string& out, string& err) {
    streambuf* cin_backup  = cin.rdbuf();
    streambuf* cout_backup = cout.rdbuf();
    streambuf* cerr_backup = cerr.rdbuf();

    istringstream iss(in);
    ostringstream oss_out;
    ostringstream oss_err;

    cin.rdbuf(iss.rdbuf());
    cout.rdbuf(oss_out.rdbuf());
    cerr.rdbuf(oss_err.rdbuf());

    int rc = turkish_main();

    cin.rdbuf(cin_backup);
    cout.rdbuf(cout_backup);
    cerr.rdbuf(cerr_backup);

    out = oss_out.str();
    err = oss_err.str();
    return rc;
}

TEST(TurkishNumbers, ZeroToNine_Valid) {
    ostringstream oss;
    auto* old = cout.rdbuf(oss.rdbuf());

    EXPECT_EQ(OK, zero_to_nine(0));
    EXPECT_EQ("sıfır", oss.str());

    cout.rdbuf(old);
    oss.str(""); oss.clear();
    cout.rdbuf(oss.rdbuf());

    EXPECT_EQ(OK, zero_to_nine(9));
    EXPECT_EQ("dokuz", oss.str());

    cout.rdbuf(old);
}

TEST(TurkishNumbers, ZeroToNine_Invalid) {
    ostringstream oss;
    auto* old = cerr.rdbuf(oss.rdbuf());

    EXPECT_EQ(WRONG_INPUT, zero_to_nine(11));
    EXPECT_EQ("error: input isn't a supported digit", oss.str());

    cerr.rdbuf(old);
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
    auto* old = cerr.rdbuf(oss.rdbuf());

    EXPECT_EQ(WRONG_INPUT, decades(0));
    EXPECT_EQ("error: input isn't a supported digit", oss.str());

    cerr.rdbuf(old);
}

TEST(TurkishNumbersE2E, SingleDigit) {
    string out, err;
    int rc = RunMainWithInput("0\n", out, err);
    EXPECT_EQ(0, rc);
    EXPECT_EQ("sıfır", out);
    EXPECT_EQ("", err);
}

TEST(TurkishNumbersE2E, ExactDecade) {
    string out, err;
    int rc = RunMainWithInput("70\n", out, err);
    EXPECT_EQ(0, rc);
    EXPECT_EQ("yetmiş", out);
    EXPECT_EQ("", err);
}

TEST(TurkishNumbersE2E, CompositeNumber) {
    string out, err;
    int rc = RunMainWithInput("42\n", out, err);
    EXPECT_EQ(0, rc);
    EXPECT_EQ("kırk iki", out);
    EXPECT_EQ("", err);
}

TEST(TurkishNumbersE2E, InvalidOutOfRange) {
    string out, err;
    int rc = RunMainWithInput("100\n", out, err);
    EXPECT_EQ(WRONG_INPUT, rc);
    EXPECT_EQ("", out);
    EXPECT_EQ("error: input isn't a supported number", err);
}

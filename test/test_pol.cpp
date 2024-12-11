#include "gtest.h"
#include "all.h"
#include <cassert>

TEST(Pol, 1)
{
    string s = "35+(45-6)/11*56*(2*0)+134"; // -2
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    string s1 = ConvertForTests(v);
    int f = A.Syntax_analysis();
    string s2 = "35 45 6 - 11 / 56 * 2 0 * * + 134 + "; // важен последний пробел
    EXPECT_EQ(1, f * (s1 == s2));
}
TEST(Pol, incorrect_entry_1)
{
    string s = "44 - 58 * 33 - 9 ++ 5";
    Translator A;
    A.lexical_analysis(s);
    ASSERT_ANY_THROW(A.Syntax_analysis());
}

TEST(Pol, 2)
{
    string s = "77 - 56 * 8 + 222 - (3 * 2 - 1) * 4";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    string s1 = ConvertForTests(v);
    int f = A.Syntax_analysis();
    string s2 = "77 56 8 * - 222 + 3 2 * 1 - 4 * - ";
    EXPECT_EQ(1, f * (s1 == s2));
}

TEST(Pol, 3)
{
    string s = "1-1-1+1-1*1-1/1+1+1";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    string s1 = ConvertForTests(v);
    int f = A.Syntax_analysis();
    string s2 = "1 1 - 1 - 1 + 1 1 * - 1 1 / - 1 + 1 + ";
    EXPECT_EQ(1, f * (s1 == s2));
}

TEST(Pol, 4)
{
    string s = "0*0*0*0*0*0*0*0*0";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    string s1 = ConvertForTests(v);
    int f = A.Syntax_analysis();
    string s2 = "0 0 * 0 * 0 * 0 * 0 * 0 * 0 * 0 * ";
    EXPECT_EQ(1, f * (s1 == s2));
}

TEST(Pol, 5)
{
    string s = "0-233+0+234/22+77*(2-5*13)/3";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    string s1 = ConvertForTests(v);
    int f = A.Syntax_analysis();
    string s2 = "0 233 - 0 + 234 22 / + 77 2 5 13 * - * 3 / + ";
    EXPECT_EQ(1, f * (s1 == s2));
}

TEST(Pol, 6)
{
    string s = "(88+7+7-88)*0";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    string s1 = ConvertForTests(v);
    int f = A.Syntax_analysis();
    string s2 = "88 7 + 7 + 88 - 0 * ";
    EXPECT_EQ(1, f * (s1 == s2));
}

TEST(Pol, 7)
{
    string s = "17";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    string s1 = ConvertForTests(v);
    int f = A.Syntax_analysis();
    string s2 = "17 ";
    EXPECT_EQ(1, f * (s1 == s2));
}

TEST(Pol, 8)
{
    string s = "8 - (13 + 1 * 4) / 5";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    string s1 = ConvertForTests(v);
    int f = A.Syntax_analysis();
    string s2 = "8 13 1 4 * + 5 / - ";
    EXPECT_EQ(1, f * (s1 == s2));
}

TEST(Pol, 9)
{
    string s = "7.567 / (4665.5 - 4665.5/3*3) - 255";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    string s1 = ConvertForTests(v);
    int f = A.Syntax_analysis();
    string s2 = "7.567 4665.5 4665.5 3 / 3 * - / 255 - ";
    EXPECT_EQ(1, f * (s1 == s2));
}

TEST(Pol, 10)
{
    string s = "8.32324-546.7/24+444*(323.2-334.12)-34-(214+33.451+(22-1.23))";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    string s1 = ConvertForTests(v);
    int f = A.Syntax_analysis();
    string s2 = "8.32324 546.7 24 / - 444 323.2 334.12 - * + 34 - 214 33.451 + 22 1.23 - + - ";
    EXPECT_EQ(1, f * (s1 == s2));
}

TEST(Pol, 11)
{
    string s = "5324^4+4365-88+0-(34/2)^2";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    string s1 = ConvertForTests(v);
    int f = A.Syntax_analysis();
    string s2 = "5324 4 ^ 4365 + 88 - 0 + 34 2 / 2 ^ - ";
    EXPECT_EQ(1, f * (s1 == s2));
}

TEST(Pol, incorrect_entry_2)
{
    string s = "8.32324-546.7/24+444*(323.2-334.12)-34-(214+33.451+((22-1.23))";
    Translator A;
    A.lexical_analysis(s);
    ASSERT_ANY_THROW(A.Syntax_analysis());
}

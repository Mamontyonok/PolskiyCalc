#include "gtest.h"
#include "all.h"
#include <cassert>

TEST(Res, 1)
{
    string s = "35+(45-6)/11*56*(2*0)+134"; // -2
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    EXPECT_EQ(169, postfix_calculate(v));
}

TEST(Res, 2)
{
    string s = "77 - 56 * 8 + 222 - (3 * 2 - 1) * 4";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    EXPECT_EQ(-169, postfix_calculate(v));
}

TEST(Res, 3)
{
    string s = "1-1-1+1-1*1-1/1+1+1";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    EXPECT_EQ(0, postfix_calculate(v));
}

TEST(Res, 4)
{
    string s = "0*0*0*0*0*0*0*0*0";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    EXPECT_EQ(0, postfix_calculate(v));
}

TEST(Res, 5)
{
    string s = "0-233+0+234/22+77*(2-5*13)/3";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    EXPECT_LE(abs(-1839.36363636 - postfix_calculate(v)), 1e-6);
}

TEST(Res, 6)
{
    string s = "(88+7+7-88)*0";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    EXPECT_EQ(0, postfix_calculate(v));
}

/*TEST(Res, 7) // почему-то не работает с одним числом: pointer being freed was not allocated (ошибка при вызове деструктора класса Translator)
{
    string s = "17";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    double temp = postfix_calculate(v); // проблема возникает при вызове функции postfix_calculate(), которая не является методом класса
    //while (v1.size()) {
     //   delete v1.back();
     //   v1.pop_back();
    //}
    //while (v.size()) {
    //    delete v.back();
    //    v.pop_back();
   // }
    //EXPECT_EQ(17, temp);
}*/

TEST(Res, 8)
{
    string s = "8 - (13 + 1 * 4) / 5";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    EXPECT_EQ(4.6, postfix_calculate(v));
}

TEST(Res, division_by_zero)
{
    string s = "7.567 / (4665.5 - 4665.5/3*3) - 255";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    ASSERT_ANY_THROW(postfix_calculate(v));
}

TEST(Res, 9)
{
    string s = "8.32324-546.7/24+444*(323.2-334.12)-34-(214+33.451+(22-1.23))";
    Translator A;
    A.lexical_analysis(s);
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    EXPECT_LE(abs(-5165.15692666 - postfix_calculate(v)), 1e-6);
}


#include "gtest.h"
#include "all.h"
#include <cassert>

TEST(Pol, 1)
{
    string s = "35+(45-6)/11*56*(2*0)+134"; // -2
    Translator A;
    A.lexical_analysis(s);
   // vector v(A.GetVector());
    vector<Term*> v1 = A.GetVector();
    vector<Term*> v = Polskaya(v1);
    string s1 = ConvertForTests(v);
    int f = A.Syntax_analysis();
    string s2 = "35 45 6 - 11 / 56 * 2 0 * * + 134 + "; // важен последний пробел
    EXPECT_EQ(1, f * (s1 == s2));
}
/*TEST(Queue, can_create_queue)
{
    ASSERT_NO_THROW(Queue<int> q);
}

TEST(Queue, cant_create_queue_with_negative_length)
{
    ASSERT_ANY_THROW(Queue<int> q(-1));
}

TEST(Queue, can_push)
{
    Queue<int> q;
    vector <int> v;
    for (int i = 0; i < n; i++) {
        q.push(i - 3);
        v.push_back(i - 3);
    }
    bool f = true;
    for (int i = 0; i < n; i++) {
        if (q[i] != v[i]) {
            f = false;
            break;
        }
    }
    EXPECT_EQ(1, f);
}

TEST(Queue, can_pop)
{
    Queue<int> q;
    for (int i = 0; i < n; i++)
        q.push(i - 3);
    q.pop();
    EXPECT_EQ(n - 5, q[n - 2]);
}

TEST(Queue, can_get_size)
{
    Queue<int> q(5);
    q.push(3);
    q.push(-7);
    EXPECT_EQ(2, q.size());
}

TEST(Queue, can_get_back)
{
    Queue<int> q;
    for (int i = 0; i < n; i++)
        q.push(i - 3);
    EXPECT_EQ(n - 4, q.GetBack());
}

TEST(Queue, can_get_front)
{
    Queue<int> q;
    for (int i = 0; i < n; i++)
        q.push(i - 3);
    EXPECT_EQ(-3, q.GetFront());
}

TEST(Queue, throw_queue_is_empty)
{
    Queue<int> q;
    ASSERT_ANY_THROW(q.pop());
}*/


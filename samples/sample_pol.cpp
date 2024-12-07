#include "all.h"

int main()
{
    /*string s;
    getline(cin, s);
    //string s = "35+(45-6)/11*56*(-2*0)+134";
    Translator A;
    A.lexical_analysis(s);
    A.Syntax_analysis();*/
    /*vector<Term*> v(A.GetVector());
    for (int i = 0; i < v.size(); i++) {
        if (v[i] -> GetType() == number)
            cout << v[i] -> GetValue() << " ";
        if (v[i] -> GetType() == operation)
            cout << dynamic_cast<Operation*>(v[i]) -> GetOperation() << " ";
        if (v[i] -> GetType() == open_bracket)
            cout << "(" << " ";
        if (v[i] -> GetType() == close_bracket)
            cout << ")" << " ";
    }*/
 /*   vector<Term*> v(Polskaya(A.GetVector()));
    cout << v.size() << endl;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] -> GetType() == number)
            cout << static_cast<Number*>(v[i]) -> GetValue() << " ";
        if (v[i] -> GetType() == operation) {
            //cout << v[i] -> GetType() << " ";
            cout << static_cast<Operation*>(v[i]) -> GetOperation() << " ";
        }
    }
    cout << endl;
    cout << postfix_calculate(Polskaya(A.GetVector())) << endl;*/
    string s = "35+(45-6)/11*56*(2*0)+134"; // -2
    Translator A;
    A.lexical_analysis(s);
   // vector v(A.GetVector());
    vector v(Polskaya(A.GetVector()));
    string s1 = ConvertForTests(v);
    cout << s1;
    string s2 = "35 45 6 - 11 / 56 * 2 0 * * + 134 + ";
    cout << endl;
    cout << s2;
    if (s1 == s2)
        cout << "good";
    //for (int i = 0; i < A.GetVector().size(); i++)
     //   cout << (A.GetVector())[i]-> GetValue() << " ";
    
    return 0;
}

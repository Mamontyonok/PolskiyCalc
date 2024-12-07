#include "all.h"

int main()
{
    string s;
    getline(cin, s);
    Translator A;
    A.lexical_analysis(s);
    A.Syntax_analysis();
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
    vector<Term*> v(Polskaya(A.GetVector()));
    cout << v.size() << endl;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] -> GetType() == number)
            cout << v[i] -> GetValue() << " ";
        if (v[i] -> GetType() == operation) {
            //cout << v[i] -> GetType() << " ";
            cout << dynamic_cast<Operation*>(v[i]) -> GetOperation() << " ";
        }
    }
    cout << endl;
    cout << postfix_calculate(Polskaya(A.GetVector())) << endl;
    //for (int i = 0; i < A.GetVector().size(); i++)
     //   cout << (A.GetVector())[i]-> GetValue() << " ";
    
    return 0;
}

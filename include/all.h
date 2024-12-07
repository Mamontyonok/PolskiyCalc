#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>

using namespace std;

static map<char, int> dict {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2},{'^', 3}, {'(', 0}
};

enum types{number, operation, open_bracket, close_bracket};

class Term {
protected:
    types type;
public:
    types GetType() {
        return type;
    }
};

class Number:public Term {
protected:
    double value;
public:
    double GetValue() {
        return value;
    }
    Number (double _value = 0.0):value(_value) {
        type = number;
    }
};

class Operation:public Term {
protected:
    char op;
    int priority;
public:
    char GetOperation() {
        return op;
    }
    int GetPriority() {
        return priority;
    }
    Operation(char _op):op(_op) {
        type = operation;
        priority = dict[op];
        type = operation;
    }
};

class Open_bracket:public Term {
protected:
    char bracket;
    int priority = 0;
public:
    Open_bracket() {
        type =  open_bracket;
        bracket = '(';
    }
};

class Close_bracket:public Term {
protected:
    char bracket;
public:
    Close_bracket() {
        type = close_bracket;
        bracket = ')';
    }
};

/*double strtod(string s, int j) {
    string temp;
    int i = j - 1;
    while (((s[i] <= '9' && s[i] >= '0') || s[i] == '.' || s[i] == ',') && i >= 0) {
        temp.push_back(s[i]);
        i--;
    }
    reverse(temp.begin(), temp.end());
    return stod(temp);
}*/

class Translator : public Term {
    std::vector<Term*> terms;
    std::string N;
public:
    ~Translator() {
        while (terms.size()) {
            delete terms.back();
            terms.pop_back();
        }
    }
    std::vector<Term*> GetVector() {
        return terms;
    }
    // перевод из строки в вектор(составление вектора термов)
    std::vector<Term*>lexical_analysis(std::string str) {
        int number_status = 0; // не накапливаем число
        for (int i = 0; i < str.size(); i++) {
            if (number_status == 0) {
                if (str[i] == '(')
                    terms.push_back(new Open_bracket());
                if (str[i] == ')')
                    terms.push_back(new Close_bracket());
                if (str[i] == '*' || str[i] == '/' || str[i] == '+' || str[i] == '-')
                    terms.push_back(new Operation(str[i]));
                if (str[i] >= '0' && str[i] <= '9') {
                    number_status = 1;
                    N += str[i];
                }
            }
            else {
                if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == ',')
                    N += str[i];
                if (str[i] == ')') {
                    number_status = 0;
                    terms.push_back(new Number(std::stod(N)));
                    //terms.push_back(new Number(strtod(str, i)));
                    terms.push_back(new Close_bracket());
                    N = string();
                }
                if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
                    number_status = 0;
                    terms.push_back(new Number(std::stod(N)));
                    //terms.push_back(new Number(strtod(str, i)));
                    terms.push_back(new Operation(str[i]));
                    N = string();
                }
            }
        }
        if (N.size() > 0)
            terms.push_back(new Number(std::stod(N)));
        return terms;
    }
    
    char GetOpenBracket(types t) { // вспомогательная функция для проверки корректности расстановки скобок
        if (t == close_bracket)
            return open_bracket;
        return 0;
    }
    int Syntax_analysis() {
        stack<char> st;
        bool flag = false;
        
        for (int i = 0 ; i < terms.size(); i++){
            if (terms[i] -> GetType() == open_bracket)
                st.push('(');
            if(terms[i] -> GetType() == close_bracket){
                if (!st.size())
                    flag = true;
                else{
                    if (st.top() != GetOpenBracket(terms[i] -> GetType()))
                        flag = true;
                    else
                        st.pop();
                }
            }
        }
        if(st.size() != 0)
            flag = true;
        if (flag == true)
            throw logic_error("IEROGLIFS");

        int state;
        if (terms[0]->GetType() == number)
            state = 0;
        if (terms[0]->GetType() == operation) {
            state = 1;
            throw logic_error("oops");
        }
        if (terms[0]->GetType() == open_bracket)
            state = 2;
        if (terms[0]->GetType() == close_bracket) {
            state = 3;
            throw logic_error("oops");
        }
        for (int i = 1; i < terms.size(); i++) {
            switch(state) {
                case 0:
                    if (terms[i]->GetType() == open_bracket || terms[i]->GetType() == number)
                        throw logic_error("oops");
                    //обновляем state
                    if (terms[i]->GetType() == operation)
                        state = 1;
                    else state = 3;
                    break;
                case 1:
                    if (terms[i]->GetType() == operation || terms[i]->GetType() == close_bracket)
                        throw logic_error("oops");
                    //обновляем state
                    if (terms[i]->GetType() == number)
                        state = 0;
                    else state = 2;
                    break;
            }
        }
        return 1;
    }
};

static vector<Term*> Polskaya (vector<Term*> terms) {
    vector<Term*> P;
    stack<Term*> st;
    for (int i = 0; i < terms.size(); ++i) {
        if (terms[i] -> GetType() == number)
            P.push_back(terms[i]);
        if (terms[i] -> GetType() == operation) {
            if (st.size() > 0) {
                while (static_cast<Operation*>(terms[i]) -> GetPriority() <= static_cast<Operation*>(st.top()) -> GetPriority()) {
                    if (st.size() > 0) { 
                        P.push_back(st.top());
                        st.pop();
                    }
                    if (st.size() == 0)
                        break;
                }
            }
            st.push(terms[i]);
        }
        if (terms[i] -> GetType() == open_bracket)
            st.push(terms[i]);
        if (terms[i] -> GetType() == close_bracket) {
            if (st.size() > 0) { //
                while (st.top() -> GetType() != open_bracket) {
                    P.push_back(st.top());
                    st.pop();
                }
                st.pop(); // удаление ( из стэка
            }
        }
    }
    while (st.size() != 0) {
        P.push_back(st.top());
        st.pop();
    }
    return P;
}

static double postfix_calculate(vector<Term*> terms) {
    stack<Term*> st;
    types current_type;
    double t1, t2;
    for (int i = 0; i < terms.size(); i++) {
        current_type = terms[i]->GetType();
        if (current_type == number)
            st.push(terms[i]);
        if (current_type == operation) {
            t2 = static_cast<Number*>(st.top()) -> GetValue();
            st.pop();
            t1 = static_cast<Number*>(st.top()) -> GetValue();
            st.pop();
            switch(static_cast<Operation*>(terms[i])->GetOperation()) {
                case '+':
                    st.push(new Number(t1 + t2));
                    break;
                case '-':
                    st.push(new Number(t1 - t2));
                    break;
                case '*':
                    st.push(new Number(t1 * t2));
                    break;
                case '/':
                    if (t2 == 0)
                        throw logic_error("division on zero");
                    st.push(new Number(t1 / t2));
                    break;
            }
        }
    }
    return (static_cast<Number*>(st.top())->GetValue());
}

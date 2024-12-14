#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "stack.h"
#include <string>
#include <math.h>

using namespace std;

static double binpow (double a, int n) {
    double res = 1;
    while (n) {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

static map<char, int> dict {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}, {'(', 0}
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

class Translator {
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
                if (str[i] == '*' || str[i] == '/' || str[i] == '+' || str[i] == '-' || str[i] == '^')
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
                if (str[i] == '(') {
                    terms.push_back(new Number(std::stod(N)));
                    terms.push_back(new Open_bracket());
                    N = string();
                }
                if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^') {
                    number_status = 0;
                    terms.push_back(new Number(std::stod(N)));
                    //terms.push_back(new Number(strtod(str, i)));
                    terms.push_back(new Operation(str[i]));
                    N = string();
                }
            }
        }
        if (N.size()) {
            terms.push_back(new Number(std::stod(N)));
            N = string();
        }
        return terms;
    }
    
    char GetOpenBracket(types t) { // вспомогательная функция для проверки корректности расстановки скобок
        if (t == close_bracket)
            return '(';
        return 0;
    }
    int Syntax_analysis() {
        Stack<char> st;
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
        for (int i = 1; i < terms.size() - 1; i++) {
            if (terms.size() != i - 1)
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
            else switch(state) {
                case 0:
                    if (terms[i] -> GetType() != close_bracket)
                        throw logic_error("oops");
                    break;
                case 1:
                    if (terms[i] -> GetType() != number)
                        throw logic_error("oops");
                    break;
                case 2:
                    throw logic_error("oops");
                    break;
                case 3:
                    throw logic_error("oops");
                    break;
            }
        }
        
        return 1;
    }
};

static vector<Term*> Polskaya (vector<Term*> terms) {
    vector<Term*> P;
    Stack<Term*> st;
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
    while (st.size()) {
        P.push_back(st.top());
        st.pop();
    }
    return P;
}
// добавить обработку унарных операторов
static double postfix_calculate(vector<Term*> terms) {
    Stack<Term*> st;
    types current_type;
    double t1, t2;
    for (int i = 0; i < terms.size(); i++) {
        current_type = terms[i]->GetType();
        if (current_type == number)
            st.push(new Number(static_cast<Number*>(terms[i]) -> GetValue()));
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
                case '^':
                    if(abs(round(t2) - t2) < 1e-9 && t2 >= 0) // проверка, натуральное(или 0) ли t2?
                        st.push(new Number(binpow(t1, t2)));
                    else st.push(new Number(pow(t1, t2)));
                    break;
                case '/':
                    if (t2 == 0)
                        throw logic_error("division by zero");
                    st.push(new Number(t1 / t2));
                    break;
            }
        }
    }
    double result = static_cast<Number*>(st.top()) -> GetValue();
    while (st.size()) {
        delete st.top();
        st.pop();
    }
    return result;
}

static string ConvertForTests (vector <Term*> terms) {
    string s;
    for (int i = 0; i < terms.size(); i++) {
        types t = terms[i] -> GetType();
        switch(t) {
            case number:
                //cout << static_cast<Number*>(terms[i]) -> GetValue() << " ";
                //костыль, но так как необходим исключительно для тестов, то ничего страшного
                s += to_string(static_cast<Number*>(terms[i]) -> GetValue());
                if (s[s.size() - 1] == '0')
                    for (size_t j = s.size() - 1; s[j] == '0'; j--)
                        s.erase(j, 1);
                if (s[s.size() - 1] == '.')
                    s.erase(s.size() - 1, 1);
                s += " ";
                break;
            case operation:
                //cout << static_cast<Operation*>(terms[i]) -> GetOperation() << " ";
                s += static_cast<Operation*>(terms[i]) -> GetOperation();
                s += " ";
                break;
            case open_bracket:
                //cout << '(' << " ";
                s += '(';
                s += " ";
                break;
            case close_bracket:
                //cout << ')' << " ";
                s += ')';
                s += " ";
                break;
        }
    }
    return s;
}

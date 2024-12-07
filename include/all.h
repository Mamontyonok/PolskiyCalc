#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>

using namespace std;

//pair <char, int> dict[10];
static map<char, int> dict {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2},{'^', 3}, {'(', 0}
};

//создать словарь dict pair либо мапу

enum types{number, operation, open_bracket, close_bracket};

class Term {
protected:
    types type;
public:
    types GetType() {
        return type;
    }
    virtual double GetValue() = 0;
    virtual int GetPriority() = 0; //
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
    int GetPriority() {
        throw logic_error("NeNado");
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
    double GetValue() {
        throw logic_error("Zachem?");
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
    double GetValue() {
        throw logic_error("Zachem?");
    }
    int GetPriority() { //
        return priority;
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
    double GetValue() {
        throw logic_error("Zachem?");
    }
    int GetPriority() {
        throw logic_error("NeNado");
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
    double GetValue() {
        throw logic_error("Zachem?");
    }
    int GetPriority() {
        throw logic_error("NeNado");
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
    int Syntax_analysis() {
        // доделать равное кол-во открытых и закрытых скобок
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
             //   case 2:
                //    if (terms[i]->GetType() == close_bracket || terms[i]->GetType() == operation)
                 //       throw logic_error("");
                    // update state
                 //   if (terms[i]->GetType() == number)
                //        state = 0;
                //    else state = 2;
            //    case 3:
            //        if ({Open_bracket, number})
             //           throw logic_error("");
                    // update state
            }
        }
        return 1;
    }
};

static vector<Term*> Polskaya (vector<Term*> terms) {
    //vector<Term*> P(terms.size());
    vector<Term*> P;
    stack<Term*> st;
   // Term* temp = nullptr; оказалось лишней идеей (вроде бы)
    for (int i = 0; i < terms.size(); ++i) {
        if (terms[i] -> GetType() == number)
            P.push_back(terms[i]);
        if (terms[i] -> GetType() == operation) {
            if (st.size() > 0) { //
                //cout << st.top()->GetType() << " " << "HI" << endl;
                //while (dict[dynamic_cast<Operation*>(terms[i]) -> GetOperation()] <= dict[dynamic_cast<Operation*>(st.top()) -> GetOperation()]) {
                //while (dict[terms[i] -> GetType()] <= dict[st.top() -> GetType()]) {
                while (terms[i] -> GetPriority() <= st.top() -> GetPriority()) {
                    if (st.size() > 0) { //
                        P.push_back(st.top());
                       // temp = st.top();
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
            //while (st.size() != 0) {
            //    cout << dynamic_cast<Operation*>(st.top()) -> GetOperation() << endl;
            //    st.pop();
            //}
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
            //t2 = st.top()->GetValue();
            t2 = dynamic_cast<Number*>(st.top()) -> GetValue();
            st.pop();
            //t1 = st.top()->GetValue();
            // пустой стэк, из него удалился последний элемент строчкой выше
            if (!st.empty())
                t1 = dynamic_cast<Number*>(st.top()) -> GetValue();
            else {
                cout << "HI";
                return 0;
            }
            st.pop();
            switch(dynamic_cast<Operation*>(terms[i])->GetOperation()) {
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
    return (st.top()->GetValue());
}

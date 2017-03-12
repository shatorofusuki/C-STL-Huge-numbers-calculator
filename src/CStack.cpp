#include "CStack.h"
#include "CElement/CParenthesis.h"
#include "CElement/COperator.h"

CStack::CStack():m_Correct(true) {}

CStack::~CStack () {
    for (auto it = m_Stack.begin(); it != m_Stack.end(); it++) {
        delete *it;
    }
    for (auto it = m_Queue.begin(); it != m_Queue.end(); it++) {
        delete *it;
    }
}

void CStack::push( CElement * pointer) {
    m_Stack.push_back(pointer);
}

void CStack::parse(istream & is) {
    string expression;
    getline(is, expression);
    
    for (auto it = m_Stack.begin(); it != m_Stack.end(); it++) {
        delete *it;
    }
    
    m_Stack.clear();
    
    for (auto it = m_Queue.begin(); it != m_Queue.end(); it++) {
        delete *it;
    }
    
    m_Queue.clear();
    
    for (auto it = expression.begin(); it!=expression.end(); it++) {
        switch (*it) {
            case '(': {
                CParenthesis * par = new CParenthesis(EParenthesis::left);
                m_Stack.push_back(par);
                break;
            }
            case ')': {
                while (m_Stack.size()!=0) {
                    if (m_Stack.back()->getType()==EType::leftpar) break;
                    m_Queue.push_back(m_Stack.back());
                    m_Stack.pop_back();
                }
                if (m_Stack.size() == 0) {
                    cout<<"Error : got right bracket, but left is nowhere to be found."<<endl;
                    cout<<"I will try to evaluate the first "<<it-expression.begin()<<" characters"<<endl;
                    return;
                }
                auto toDel = m_Stack.back();
                m_Stack.pop_back();
                delete toDel;
                break;
            }
            case '*':
            case '+':
            case '-': {
                COperator * op = new COperator(&*it);
                while (m_Stack.size()>0) {
                    if (op->getType() <= m_Stack.back()->getType()) {
                        m_Queue.push_back(m_Stack.back());
                        m_Stack.pop_back();
                    } else {
                        break;
                    }
                }
                m_Stack.push_back(op);
                break;
            }
            case ' ':{
                continue;
            }
            case '0':case '1':case '2':case '3':case '4':case '5':
            case '6':case '7':case '8':case '9':case '.': {
                string mm = "";
                
                while ((*it > 47 && *it < 58 ) || *it == 46) {
                    mm+=*it;
                    it++;
                }
                it--;
                CNumber * n = new CNumber(mm);
                if (!n->isCorrect()) {
                    cout<<"Error : something happened while parsing the expression"<<endl;
                    cout<<"Possible reasons : multiple decimal marks"<<endl;
                    this->m_Correct = false;
                    delete n;
                    return;
                }
                m_Queue.push_back(n);
                break;
            }
            default: {
                
                break;
            }
        }
    }
    
    while (m_Stack.size()!=0) {
        if (m_Stack.back()->getType() == EType::leftpar) {
            cout<<"Error : parsing failed"<<endl;
            cout<<"Possible reasons : brackets left on stack"<<endl;
            this->m_Correct = false;
            return;
        }
        m_Queue.push_back(m_Stack.back());
        m_Stack.pop_back();
    }
}

ostream & operator <<  (ostream & os, const CStack & a) {
    for (auto it = a.m_Queue.begin(); it!=a.m_Queue.end(); it++) {
        (*it)->print(os);
        os<<endl;
    }
    return os;
}

CNumber CStack::calculate () {
    string result = "";
    if (!this->m_Correct) {
        CNumber err;
        err.setErrorState();
        return err;
    }
    while (m_Queue.size() != 0) {
        CElement * token = m_Queue.front();
        m_Queue.pop_front();
        if (token->getType() == EType::number) {
            m_Stack.push_back(token);
        } else {
            //it is an operator
            if (m_Stack.size()<2) {
                cout <<"Error : not enough numbers on stack for the operator"<<endl;
                cout <<"Possible causes : too many operators in the input"<<endl;
                CNumber m;
                m.setErrorState();
                return m;
            }
            CElement * a = m_Stack.back();
            m_Stack.pop_back();
            CElement * b = m_Stack.back();
            m_Stack.pop_back();
            
            switch (token->getType()) {
                case EType::mult : {
                    CNumber temp = *(dynamic_cast<CNumber *>(a)) * *(dynamic_cast<CNumber *>(b));
                    delete a;
                    delete b;
                    CNumber * pt = new CNumber(temp);
                    m_Stack.push_back(pt);
                    break;
                }
                case EType::add : {
                    CNumber temp = *(dynamic_cast<CNumber *>(a)) + *(dynamic_cast<CNumber *>(b));
                    delete a;
                    delete b;
                    CNumber * pt = new CNumber(temp);
                    m_Stack.push_back(pt);
                    break;
                }
                default: /*minus*/{
                    CNumber temp = *(dynamic_cast<CNumber *>(b)) - *(dynamic_cast<CNumber *>(a));
                    delete a;
                    delete b;
                    CNumber * pt = new CNumber(temp);
                    m_Stack.push_back(pt);
                    break;
                }
            }
            delete token;
        }
    }
    
    CNumber final;
    if (m_Stack.size() == 1) {
        final = (*(dynamic_cast<CNumber*>(m_Stack.back())));
    } else {
        if (m_Stack.size() > 1) {
            cout<<"Error : more than 1 element left on stack."<<endl;
        } else {
            cout<<"Error : stack is empty."<<endl;
        }
        final.setErrorState();
    }
    return final;
}
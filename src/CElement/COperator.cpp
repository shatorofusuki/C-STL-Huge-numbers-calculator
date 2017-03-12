#include "COperator.h"

COperator::COperator (const EOperation a) : m_Op(a) {}

COperator::COperator (const char * op) {
    if (*op == '+') {
        m_Op = EOperation::addition;
    } else if ( *op == '*') {
        m_Op = EOperation::multiplication;
    } else if (*op == '-') {
        m_Op = EOperation::subtraction;
    } else {
        cout<<"Error : unknown operation"<<endl;
    }
}

EType COperator::getType () const {
    switch (m_Op) {
        case addition:
            return EType::add;
            break;
        case multiplication:
            return EType::mult;
            break;
        default:
            return EType::subtr;
            break;
    };
}

void COperator::print(ostream & os) const {
    switch (m_Op) {
        case addition:
            os<<" + ";
            break;
        case multiplication:
            os<<" * ";
            break;
        case subtraction:
            os<<" - ";
            break;
        default:
            break;
    };
}
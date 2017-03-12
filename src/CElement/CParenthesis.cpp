#include "CParenthesis.h"

CParenthesis::CParenthesis (const EParenthesis a) : m_Par(a) {}

EType CParenthesis::getType () const {
    switch (m_Par) {
        case EParenthesis::left:
            return EType::leftpar;
            break;
        default:
            return EType::rightpar;
            break;
    };
}

void CParenthesis::print(ostream & os) const {
    switch (m_Par) {
        case EParenthesis::left:
            os<<" ( ";
            break;
        case EParenthesis::right:
            os << " ) ";
            break;
        default:
            break;
    };
}

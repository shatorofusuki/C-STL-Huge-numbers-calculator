#ifndef __Semm__COperator__
#define __Semm__COperator__

/** enum to easier programmer's work by supplying substitutions for different types of operations*/
enum EOperation {
    addition = 1,
    subtraction = 2,
    multiplication = 3
};

#include <stdio.h>
#include "CElement.h"

/**
 * @class COperator
 * @brief used to store different operators
 */

class COperator : public CElement {
public:
    /**
     *Constructor
     *@param a operation enum
     */
    COperator (const EOperation a);
    
    /**
     *Constructor
     *@param op operator as text/char
     */
    COperator (const char * op);
    
    /**
     * Returns the type of element
     * @return the type of element
     */
    virtual EType getType () const ;
    
    /**
     * Ouputs the operator
     * @param os output stream
     */
    virtual void print(ostream & os) const;
private:
    EOperation m_Op;
};

#endif /* defined(__Semm__COperator__) */

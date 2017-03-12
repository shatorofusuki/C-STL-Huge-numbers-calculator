#ifndef __Semm__CParenthesis__
#define __Semm__CParenthesis__

#include <stdio.h>
#include "CElement.h"

/** enum to easier programmer's work by supplying substitutions for left and right parenthesis*/
enum EParenthesis {
    left,
    right
};

/**
 *@class CParenthesis
 *@brief stores parenthesis
 */
class CParenthesis : public CElement {
public:
    /**
     *Constructor
     *@param a parenthesis enum, left or right
     */
    CParenthesis (const EParenthesis a);
    
    /**
     *returns type of an element
     *@return type of an element
     */
    virtual EType getType () const;
    
    /**
     * prints the element
     * @param os output stream
     */
    virtual void print(ostream & os) const;
private:
    EParenthesis m_Par;
};

#endif /* defined(__Semm__CParenthesis__) */

#ifndef __Semm__CStack__
#define __Semm__CStack__

#include <stdio.h>
#include <vector>
#include <deque>
#include "CElement/CNumber.h"

/**
 * @class CStack
 * @brief used to store different elements, transform and calculate expressions
 */
class CStack {
public:
    /**
     * Constructor
     */
    CStack();
    
    /**
     * Destructor
     */
    ~CStack ();
    
    /**
     * Pushes element onto the stack
     * @param pointer pointer to an object to push
     */
    void push( CElement * pointer);
    
    /**
     * parses an arithmetic expression from stream
     * @param is stream
     */
    void parse(istream & is);
    
    /**
     * outputs the stack
     * @param os output stream
     * @param a object
     * @return output stream
     */
    friend ostream & operator <<  (ostream & os, const CStack & a);
    
    /**
     *  Calculates the arithmetic expression and returns the result
     *  @return result of the calculation
     */
    CNumber calculate ();
private:
    vector < CElement * > m_Stack;
    deque  < CElement * > m_Queue;
    bool m_Correct;
};

#endif /* defined(__Semm__CStack__) */

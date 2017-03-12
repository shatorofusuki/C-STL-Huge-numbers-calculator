#ifndef __Semm__CNumber__
#define __Semm__CNumber__

#include <stdio.h>
#include <vector>
#include <math.h>

#include "CElement.h"

/**
 * @class CNumber
 * @brief Class able to hold numbers with up to 2147483647 digits
 */

class CNumber : public CElement {
public:
    /**
     * Constructor
     */
    CNumber();
    
    /**
     * Constructor
     * @param exp exponent
     */
    CNumber(const long exp);
    
    /**
     * Constructor
     * @param input String with arithmetic expression
     */
    CNumber(const string & input);
    
    /**
     * Copy constructor
     * @param other Another instance od CNumber to make a copy of
     */
    CNumber(const CNumber & other);
    
    /**
     * Destructor
     */
    ~CNumber ();
    
    /**
     * Optimizes string with the number (erases zeros at the beginning etc.)
     * @param input number as a string
     * @param check boolean whose value will be checked later by the calling function
     * @return optimized string
     */
    string processString (const string & input, bool & check);
    
    /**
     * Outputs the number in scientific notation
     * @param os ousput stream
     * @param num an instance of CNumber to output
     * @return stream
     */
    friend ostream & operator << (ostream & os, const CNumber & num);
    
    /**
     * Outputs the number in human-readable form
     * @return readable number
     */
    string beautify () const;
    
    /**
     * Returns the number of digits in a number
     * @return the number of digits
     */
    unsigned long totalDigits () const;
    
    /**
     * Overloaded binary operator +
     * @param a first number for addition
     * @param b second number for addition
     * @return sum of a and b
     */
    friend CNumber operator + (const CNumber & a, const CNumber & b);
    
    /**
     * Overloaded binary operator *
     * @param a first number for multiplication
     * @param b second number for multiplication
     * @return multiplication of a and b
     */
    friend CNumber operator * (const CNumber & a, const CNumber & b);
    
    /**
     * Overloaded binary operator -
     * @param a first number for subtraction
     * @param b second number for subtraction
     * @return difference between a and b
     */
    friend CNumber operator - (const CNumber & a, const CNumber & b);
    
    /**
     * Overloaded unary operator -
     * @param a number to invert
     * @return negative (or positive) number for positive (or negative) input respectively
     */
    friend CNumber operator - (const CNumber & a);
    
    /**
     * Erases unnecessary zeros, should be called after performing operations on numbers
     */
    void zeroOptimize();
    
    /**
     * Overloaded operator []
     * @param index index of a digit to return
     * @return digit at the index
     */
    unsigned int operator [] (const long & index) const;
    
    /**
     * Returns the number of digits after the decimal point
     * @return number of digits after the decimal point
     */
    unsigned long afterDecimal () const;
    
    /**
     * Returns the number of digits before the decimal point
     * @return number of digits before the decimal point
     */
    unsigned long beforeDecimal() const;
    
    /**
     * Overloaded comparison operator, less
     * @param a first number
     * @param b second number
     * @return boolean as a result of comparison with <
     */
    friend bool operator < (const CNumber &a, const CNumber &b);
    
    /**
     * Returns the type of element
     * @return the type of element
     */
    virtual EType getType () const ;
    
    /**
     * Ouputs the number in scientific notation
     * @param os output stream
     */
    virtual void print(ostream & os) const;
    
    /**
     * sets error state, use when the number can become corrupted
     */
    void setErrorState ();
    
    /**
     * Used to check if the number is correct
     * @return true if correct
     */
    bool isCorrect() const;
private:
    /**
     * Helper method for copy constructor and possible oveloaded operators like "="
     * @param input number as a string
     * @return boolean indicating success
     */
    bool assign (const string & input);
    
    /** stores digits*/
    vector<unsigned int> m_Billions;
    /** exponent*/
    long m_Exp;
    /** sign of the number*/
    bool m_Positive;
    /**fail indicator*/
    bool m_Correct;
};

#endif /* defined(__Semm__CNumber__) */

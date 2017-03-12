#ifndef __Semm__CTester__
#define __Semm__CTester__

/**
 * @class CTester
 * @brief used by the developer to check if changes in code didn't affect the functionality
 */

class CTester {
public:
    /**
     * Constructor
     */
    CTester ();
    
    /**
     * Destructor
     */
    ~CTester ();
    
    /**
     *  tests operator -
     */
    void minusTest () const;
    
    /**
     * tests operator +
     */
    void plusTest () const;
    
    /**
     * tests multiplication
     */
    void multiplyTest () const;
    
    /**
     * tests some precomputated expressions
     */
    void expressionsTest() const ;
    
    /**
     * Tests entry point
     * @return true if success
     */
    bool test() const;
    
    /**
     * Multiplies small number multiple times
     */
    void loadTest () const ;
private:
};


#endif /* defined(__Semm__CTester__) */

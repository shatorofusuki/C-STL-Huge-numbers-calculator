#ifndef __Semm__CElement__
#define __Semm__CElement__

#include <stdio.h>
#include <iostream>
#include "Etype.h"

using namespace std;

/*! @class CElement
 *  @brief Abstract class to allow for polymorphism
 *
 */

class CElement {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~CElement();
    
    /**
     * Pure virtual getter for the type of element
     * @return type enum
     */
    
    virtual EType getType () const = 0;
    /**
     * Pure virtual output function
     * @param os Name of output stream
     */
    
    virtual void print(ostream & os) const = 0;
private:
};

#endif /* defined(__Semm__CElement__) */

#include "CNumber.h"
#include <cstring>

#define DECIMAL_POINT '.'
#define NUMBER_LENGTH 9

CNumber::CNumber() : m_Exp(0), m_Positive(true), m_Correct(true) {}

CNumber::CNumber(const long exp) : m_Positive(true) {
    m_Exp = exp;
    m_Correct = true;
}

CNumber::CNumber(const string & input) {
    this->assign(input);
}

CNumber::CNumber(const CNumber & other) {
    m_Billions = other.m_Billions;
    m_Exp = other.m_Exp;
    m_Positive = other.m_Positive;
    m_Correct = other.m_Correct;
}

CNumber::~CNumber () {
    
}

bool CNumber::assign (const string & input) {
    //don't forget any attributes!
    m_Billions.clear();
    m_Positive = true;
    m_Correct = true;
    bool check = true;
    string processed = processString(input, check);
    
    if (!check) {
        cout<<"Number check error!"<<endl;
        m_Correct = false;
    }
    
    while (processed.length()!=0) {
        size_t l = (NUMBER_LENGTH > processed.length()) ? processed.length() : NUMBER_LENGTH;
        string toPush = processed.substr(processed.length()-l,l);
        processed.erase(processed.length()-l,l);
        unsigned int toPushLong = stoi(toPush.c_str());
        m_Billions.push_back(toPushLong);
    }
    
    return true;
}

string CNumber::processString (const string & input, bool & check) {
    
    string result = "";
    
    bool foundDec = false;
    unsigned long decPos = 0;
    unsigned long firstDigit = 0;
    unsigned long zeroesStartAt = 0;
    bool lastWasZero = false;
    bool firstDigitFound = false;
    
    for (size_t i = 0; i < input.length(); i++) {
        
        if (input[i] != '0' && input[i]!=DECIMAL_POINT) {
            lastWasZero = false;
        } else if (lastWasZero == false){
            zeroesStartAt = i;
            lastWasZero = true;
        }
        
        //if it is not a digit
        if (!(input[i]>=48 && input[i]<=57)) {
            
            //if it is a sign
            if (input[i] == '-' || input[i] == '+') {
                if (i!=0) {
                    check = false;
                    return result;
                } else {
                    if (input[i] == '-'){
                        m_Positive = false;
                    }
                    continue;
                }
            }
            
            //is it a dot?
            if (input[i] == DECIMAL_POINT) {
                if (foundDec || i == input.length()-1) {
                    check = false;
                    return result;
                } else {
                    decPos = i;
                    foundDec = true;
                    continue;
                }
            }
            check = false;
            return result;
        }
        
        //it is a digit
        if (!firstDigitFound) {
            if (input[i]!='0') {
                firstDigit = i;
                firstDigitFound = true;
            }
        }
    }
    
    //handle zeros
    if (!firstDigitFound) {
        m_Exp = 0;
        return "0";
    }
    
    if (lastWasZero == false) zeroesStartAt = input.length();
    //cout<<"*lastDigit = "<<zeroesStartAt<<" (foundZeros = "<<lastWasZero<<")"<<endl;
    
    if (decPos == 0) decPos = input.length();
    m_Exp = (firstDigit > decPos) ? decPos - firstDigit : decPos - firstDigit - 1;
    //cout<<"*Exp should be = "<<m_Exp<<endl;
    
    //cut at the end
    result = input.substr(0,zeroesStartAt);
    
    //cut at the start
    result = result.substr(firstDigit, input.length()-firstDigit);
    //cout<<"~~ Result is "<<result<<"*10^"<<m_Exp<<endl;
    
    //erase the dot
    size_t dot = result.find(DECIMAL_POINT);
    if (dot != string::npos) {
        result.erase(dot,1);
    }
    return result;
}

ostream & operator << (ostream & os, const CNumber & num) {
    if (!num.m_Positive && num.m_Billions.size()!=0) {
        os<<"-";
    }
    if (num.m_Billions.size()!=0) {
        for (auto it = num.m_Billions.rbegin() ; it!= num.m_Billions.rend(); it++) {
            os<<*it;
        }
    } else {
        os<<"0";
    }
    os <<" * 10^"<<num.m_Exp;
    return os;
}

string CNumber::beautify () const {
    
    string result = "";
    
    if (!m_Positive && m_Billions.size()!=0 && m_Billions.size()!=0) {
        result+="-";
    }
    if (m_Billions.size()!=0) {
        //cout<<this->beforeDecimal()-1<<" "<<-(long)(this->afterDecimal())<<endl;
        long bd = (this->beforeDecimal() > 1) ? this->beforeDecimal()-1 : 0;
        for (long it = bd ; it>=-(long)(this->afterDecimal()); it--) {
            result+= to_string((*this)[it]);
            if (it == 0 && it-1>=-(long)(this->afterDecimal())) result+=".";
        }
    } else {
        result += "0";
    }
    return result;
}

unsigned long CNumber::totalDigits () const {
    if (m_Billions.size() == 0) return 0;
    unsigned long totalDigits = (m_Billions.size()-1) * NUMBER_LENGTH;
    unsigned int lastNumber = m_Billions[m_Billions.size()-1];
    unsigned int ten = 10;
    int k = 1;
    while (ten < lastNumber) {
        ten*=10;
        k++;
    }
    totalDigits += k;
    return totalDigits;
}

CNumber operator + (const CNumber & a, const CNumber & b) {
    
    //whos exponent is bigger?
    long maxExp = (a.m_Exp > b.m_Exp) ? a.m_Exp : b.m_Exp;
    
    CNumber some(maxExp);
    
    //both positive - OK
    if (a.m_Positive == false && b.m_Positive == false) {
        //both negative - result will be negative
        some.m_Positive = false;
    } else if (a.m_Positive == false && b.m_Positive == true) {
        //one negative, another positive - subtract (b-a)
        return b-(-a);
    } else if (a.m_Positive == true && b.m_Positive == false) {
        return a-(-b);
    }
    
    long a_ad = a.afterDecimal();
    long a_bd = a.beforeDecimal();
    long b_ad = b.afterDecimal();
    long b_bd = b.beforeDecimal();
    long beforeMax = ( a_bd >= b_bd) ? a_bd : b_bd;
    long afterMax  = ( a_ad >= b_ad) ? a_ad : b_ad;
    
    int k = 0;
    unsigned int temp = 0;
    unsigned int ten = 1;
    bool overflow = false;
    bool overflowedLast = false;
    bool wasNonZero = false;
    
    for (long i = -afterMax; i < beforeMax; i ++) {
        int res = (a[i] + b[i]);
        overflowedLast = false;
        if (overflow) {
            res++;
            overflow = false;
            overflowedLast = true;
        }
        if (res > 9) {
            overflow = true;
            res%=10;
        }
        if (res!=0) {
            wasNonZero = true;
        }
        if (wasNonZero) {
            temp += res * ten;
            ten*=10;
            k++;
        }
        
        if (k == NUMBER_LENGTH) {
            some.m_Billions.push_back(temp);
            temp = 0;
            k = 0;
            ten = 1;
        }
        
    }
    
    //leftovers
    if (k != 0 || overflow) {
        overflowedLast = false;
        if (overflow) {
            temp += 1 * ten;
            overflowedLast = true;
        }
        some.m_Billions.push_back(temp);
    }
    
    if (overflowedLast) {
        some.m_Exp++;
    }
    some.zeroOptimize();
    return some;
}

CNumber operator * (const CNumber & a, const CNumber & b) {
    CNumber some;
    //find suitable size
    long size = (abs(a.m_Exp) + abs(b.m_Exp))*2 + 10;
    short * digArray = new short [size];
    for (long i = 0; i < size; i++) {
        digArray[i] = 0;
    }
    
    // cout<<"a = "<<a.m_Exp<<" b = "<<b.m_Exp<<" -> size = "<<size<<endl;
    
    unsigned int inArray = 0;
    long bAfter = b.afterDecimal();
    long bBefore = b.beforeDecimal();
    long aAfter = a.afterDecimal();
    long aBefore = a.beforeDecimal();
    
    long maxAfter = (aAfter > bAfter) ? aAfter : bAfter;
    long maxBefore = (aBefore > bBefore) ? aBefore : bBefore;
    
    int overflowVal = 0;
    bool overflowInSum = false;
    unsigned int curr = 0;
    //bool increase = false;
    
    for (long bi = -maxAfter; bi < maxBefore; bi++) {
        curr = inArray;
        
        for (long ai = -maxAfter; ai < maxBefore; ai++) {
            
            int res = a[ai] * b[bi];
            if (overflowVal > 0) {
                res+=overflowVal;
                overflowVal = 0;
            }
            if (res > 9) {
                overflowVal = (res%100)/10;
                res %= 10;
            }
            
            //cout<<"c"<<curr;
            int onPosInArray = digArray[curr];
            onPosInArray+=res;
            if (overflowInSum) {
                onPosInArray++;
                overflowInSum = false;
            }
            if (onPosInArray > 9) {
                overflowInSum = true;
                onPosInArray%=10;
            }
            digArray[curr++]=onPosInArray;
            //cout<<res;
        }
        
        if (overflowVal || overflowInSum) {
            //save remaining overflow
            int onPosInArray = digArray[curr];
            onPosInArray+=overflowVal;
            if (overflowInSum) {
                onPosInArray++;
                overflowInSum = false;
            }
            if (onPosInArray > 9) {
                overflowInSum = true;
                onPosInArray%=10;
            }
            digArray[curr++]=onPosInArray;
            //cout<<overflowVal;
            overflowVal = 0;
        }
        inArray++;
        //cout<<endl;
    }
    
    bool moved = false;
    while (digArray[curr]==0 && curr>0) {
        curr--;
        moved = true;
    }
    
    if (moved) {
        curr++;
    }
    
    //find resulting exp
    long someAfter = aAfter + bAfter;
    some.m_Exp = curr - 1 - someAfter;
    
    //push into CNumber vector
    int k = 0;
    unsigned int temp = 0;
    unsigned int ten = 1;
    bool started = false;
    
    for (unsigned int i = 0; i < curr; i++) {
        if (digArray[i] != 0 || started) {
            started = true;
            temp+=digArray[i]*ten;
            ten*=10;
        } else {
            if ((long)i < someAfter)
                some.m_Exp--;
        }
        if (started) k++;
        if (k==NUMBER_LENGTH) {
            some.m_Billions.push_back(temp);
            k = 0;
            temp = 0;
            ten = 1;
        }
    }
    
    if (k>0) {
        some.m_Billions.push_back(temp);
    }
    
    //fix sign
    if (a.m_Positive ^ b.m_Positive) {
        some.m_Positive = false;
    } else {
        some.m_Positive = true;
    }
    
    some.zeroOptimize();
    delete [] digArray;
    return some;
}

CNumber operator - (const CNumber & a, const CNumber & b) {
    
    CNumber result;
    
    if (a.m_Positive == false && b.m_Positive == false) {
        if (!(a < b)) result.m_Positive = false;
    } else if (a.m_Positive == false && b.m_Positive == true) {
        CNumber some = (-a)+b;
        return -some;
    } else if (a.m_Positive == true && b.m_Positive == false) {
        CNumber some = a+(-b);
        return some;
    } else {
        result.m_Positive = !(a<b);
    }
    
    //zeros optimizations
    if (b.m_Billions.size() == 1 && b.m_Billions[0] == 0) {
        result = a;
        return result;
    } else if (a.m_Billions.size() == 1 && a.m_Billions[0] == 0) {
        result = b;
        result.m_Positive = !b.m_Positive;
        return result;
    }
    
    unsigned long a_ad = a.afterDecimal();
    unsigned long a_bd = a.beforeDecimal();
    unsigned long b_ad = b.afterDecimal();
    unsigned long b_bd = b.beforeDecimal();
    long aexp = a.m_Exp;
    long bexp = b.m_Exp;
    
    long maxAfter = (a_ad >= b_ad) ? a_ad : b_ad;
    long maxBefore = (a_bd>=b_bd) ? a_bd :  b_bd;
    long maxExp = (aexp >= bexp) ? aexp : bexp;
    bool reversed = (a<b) ? true : false;
    long borrowed = 0;
    
    result.m_Exp = maxExp;
    
    int k = 0;
    unsigned int temp = 0;
    unsigned int ten = 1;
    bool started = false;
    long comma = 0;
    long totalWritten = 0;
    long zeros = 0;
    
    for (long i = -maxAfter; i<maxBefore; i++) {
        if (i<=0) comma++;
        int fop = (!reversed) ? a[i] : b[i];
        int sop = (!reversed) ? b[i] : a[i];
        if (borrowed>0) {
            if (fop>0) {
                fop--;
                borrowed--;
            } else {
                fop+=9;
            }
        }
        if (fop<sop && sop != 0) {
            //need to borrow!
            borrowed++;
            fop+=10;
        }
        int res = fop - sop;
        
        if (started || res!=0) {
            //record "res"
            temp+=ten*res;
            ten*=10;
            k++;
            started = true;
            totalWritten++;
            if (res==0) {
                zeros++;
            } else {
                zeros=0;
            }
        } else {
            result.m_Exp--;
        }
        
        if (k==NUMBER_LENGTH) {
            result.m_Billions.push_back(temp);
            temp = 0;
            ten = 1;
            k = 0;
        }
    }
    
    if (k!=0) {
        result.m_Billions.push_back(temp);
    }
    
    
    result.m_Exp = totalWritten - zeros - comma;
    result.zeroOptimize();
    return result;
}

CNumber operator - (const CNumber & a) {
    CNumber toRet (a);
    toRet.m_Positive = !toRet.m_Positive;
    return toRet;
}

void CNumber::zeroOptimize() {
    for (long n = m_Billions.size()-1; n>0; n--) {
        if (m_Billions[n] == 0) {
            m_Billions.pop_back();
        } else {
            break;
        }
    }
    if (m_Billions.size() == 0) {
        m_Positive = true;
        m_Exp = 0;
    }
}

unsigned int CNumber::operator [] (const long & index) const {
    unsigned int digit;
    long actualNumber = this->totalDigits() - m_Exp + index - 1;
    if (actualNumber >= (long)this->totalDigits() || actualNumber < 0) {
        //cout<<"Wow! Out of range!"<<endl;
        return 0;
    }
    long rowWithDigit = actualNumber / NUMBER_LENGTH;
    int whichOne = actualNumber % NUMBER_LENGTH;
    unsigned int num = m_Billions [rowWithDigit];
    int ten = pow(10,whichOne+1);
    num%=ten;
    digit = num/pow(10, whichOne);
    return digit;
}

unsigned long CNumber::afterDecimal () const {
    return ((long)(this->totalDigits()) - m_Exp - 1 >= 0) ? this->totalDigits() - m_Exp - 1 : 0;
}

unsigned long CNumber::beforeDecimal() const {
    return ((long)(this->totalDigits() - this->afterDecimal())>= 0) ?  m_Exp + 1:0 ;
}

bool operator < (const CNumber &a, const CNumber &b) {
    if (a.m_Exp < b.m_Exp) {
        return true;
    } else if (a.m_Exp > b.m_Exp) {
        return false;
    } else {
        long ad = (a.afterDecimal() > b.afterDecimal()) ? a.afterDecimal() : b.afterDecimal();
        for (long it = a.beforeDecimal()-1 ; it>=-ad; it--) {
            if (a[it] < b[it]) {
                return true;
            }
        }
        return false;
    }
}

EType CNumber::getType () const {
    return EType::number;
}

void CNumber::print(ostream & os) const {
    os<<*this;
}

void CNumber::setErrorState () {
    this->m_Correct = false;
}

bool CNumber::isCorrect() const{
    return m_Correct;
}
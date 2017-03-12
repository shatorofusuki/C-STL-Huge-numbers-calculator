#include "CTester.h"

#include "CElement/CNumber.h"
#include "CStack.h"
#include <stdio.h>
#include <sstream>
#include <cassert>

CTester::CTester () {
    
}

CTester::~CTester() {
    
}

void CTester::minusTest () const {
    istringstream iss;
    ostringstream oss;
    
    CNumber one("1");
    CNumber two("2");
    CNumber mone("-1");
    CNumber mtwo("-2");
    
    cout<<"Operator minus test ...";
    iss.clear(); oss.str(""); oss.clear();
    oss<<(one-two).beautify()<<" "
    <<(two-one).beautify()<<" "
    <<(one-mtwo).beautify()<<" "
    <<(two-mone).beautify()<<" "
    <<(mone-two).beautify()<<" "
    <<(mtwo-one).beautify()<<" "
    <<(mone-mtwo).beautify()<<" "
    <<(mtwo-mone).beautify();
    assert(oss.str() == "-1 1 3 3 -3 -3 1 -1");
    cout<<" OK"<<endl;
}

void CTester::plusTest () const {
    istringstream iss;
    ostringstream oss;
    
    CNumber one("1");
    CNumber two("2");
    CNumber mone("-1");
    CNumber mtwo("-2");
    
    cout<<"Operator plus test ....";
    iss.clear(); oss.str(""); oss.clear();
    oss<<(one+two).beautify()<<" "
    <<(two+one).beautify()<<" "
    <<(one+mtwo).beautify()<<" "
    <<(two+mone).beautify()<<" "
    <<(mone+two).beautify()<<" "
    <<(mtwo+one).beautify()<<" "
    <<(mone+mtwo).beautify()<<" "
    <<(mtwo+mone).beautify();
    assert(oss.str() == "3 3 -1 1 1 -1 -3 -3");
    cout<<" OK"<<endl;
}

void CTester::multiplyTest () const {
    istringstream iss;
    ostringstream oss;
    
    CNumber zero("0");
    CNumber one("1");
    CNumber two("2");
    CNumber mone("-1");
    CNumber mtwo("-2");
    
    cout<<"Operator multiply test.";
    iss.clear(); oss.str(""); oss.clear();
    oss<<(one*two).beautify()<<" "
    <<(two*one).beautify()<<" "
    <<(one*mtwo).beautify()<<" "
    <<(two*mone).beautify()<<" "
    <<(mone*two).beautify()<<" "
    <<(mtwo*one).beautify()<<" "
    <<(mone*mtwo).beautify()<<" "
    <<(mtwo*mone).beautify()<<" "
    <<(zero*zero).beautify()<<" "
    <<(zero*one).beautify()<<" "
    <<(one*zero).beautify()<<" "
    <<(zero*mtwo).beautify()<<" "
    <<(mtwo*zero).beautify();
    assert(oss.str() == "2 2 -2 -2 -2 -2 2 2 0 0 0 0 0");
    cout<<" OK"<<endl;
}

void CTester::expressionsTest() const {
    
    CStack stack;
    istringstream iss;
    ostringstream oss;
    
    cout<<"Expression #1 test ....";
    iss.clear(); oss.str(""); oss.clear();
    iss.str("((18265318765281.12461426+23867.00000001)*89726869)-0.000000001");
    stack.parse(iss);
    oss<<stack.calculate().beautify();
    assert(oss.str()=="1638889866237132398860.279820629");
    cout<<" OK"<<endl;
    
    cout<<"Expression #2 test ....";
    iss.clear(); oss.str(""); oss.clear();
    iss.str("19287562897654298756+821741256823756187365*(21581263518653-61758327651873256)");
    stack.parse(iss);
    oss<<stack.calculate().beautify();
    assert(oss.str()=="-50731631569376002048504726505273892339");
    cout<<" OK"<<endl;
    
    cout<<"Expression #3 test ....";
    iss.clear(); oss.str(""); oss.clear();
    iss.str("0.00000000000236246*0.000000000000203460337 + 0.1246357454652365277");
    stack.parse(iss);
    oss<<stack.calculate().beautify();
    assert(oss.str()=="0.12463574546523652770000048066690774902");
    cout<<" OK"<<endl;
}

void CTester::loadTest() const {
    istringstream iss;
    ostringstream oss;
    CStack stack;
    iss.clear(); oss.str(""); oss.clear();
    
    cout<<"50 big multiplications.";
    CNumber a ("100000000000");
    CNumber f ("0.0000000001");
    int k = 50;
    while (k-- > 0) {
        f = f * a;
    }
    oss<<f;
    assert(oss.str() == "1 * 10^540");
    cout<<" OK"<<endl;
}

bool CTester::test() const {
    
    this->minusTest();
    this->plusTest();
    this->multiplyTest();
    this->expressionsTest();
    this->loadTest();
    
    cout<<"All tests passed!"<<endl;
    return true;
}

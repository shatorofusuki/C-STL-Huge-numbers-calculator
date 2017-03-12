#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

// MY INCLUDES
#include "CElement/CNumber.h"
#include "CStack.h"
#include "CTester.h"

int main(int argc, const char * argv[]) {
    
    bool isFile = false;
    
    cout<<"Calculator started"<<endl;
    
    while (true) {
        cout<<"Would you like to work with a file? [Y/N/T for tests/Q to quit] ... ";
        string answer;
        cin>>answer;
        if (answer == "Y" || answer == "y") {
            isFile = true;
        } else if (answer == "N" || answer == "n") {
            isFile = false;
        } else if (answer == "T" || answer == "t"){
            CTester test;
            test.test();
            continue;
        } else if (answer == "Q" || answer == "q"){
            cout<<"Finishing ... "<<endl;
            break;
        } else {
            cout<<"Sorry, try again please."<<endl;
            continue;
        }
        
        
        if (!isFile) {
            //this is not a file!
            CStack stack;
            cout<<"Please enter an expression (+,-,* operations supported) : ";
            string expr;
            cin>>expr;
            istringstream ss(expr);
            stack.parse(ss);
            CNumber r = stack.calculate();
            if (r.isCorrect()) {
                cout<<"The answer is : ";
            } else {
                cout<<"Due to the error the answer may not be correct : ";
            }
            cout<<r.beautify()<<endl;
        } else {
            cout<<"Please supply the path to file : ";
            string path;
            cin>>path;
            
            if (path[0] == '\'') {
                path = path.substr(1,path.length()-2);
            }
            
            ifstream ifs;
            ifs.open (path, ios::in);
            if (ifs.fail()) {
                cout<<"File is corrupted or doesn't exist"<<endl;
                ifs.close();
                continue;
            } else {
                cout<<"File is ok"<<endl;
            }
            string expr;
            long k = 0;
            while (getline(ifs, expr)) {
                cout<<"Evaluating expression #"<<k++<<" from file "<<path<<endl;
                istringstream iss (expr);
                CStack stack;
                stack.parse(iss);
                CNumber r = stack.calculate();
                if (r.isCorrect()) {
                    cout<<"The answer is : ";
                } else {
                    cout<<"Due to the error the answer may not be correct : ";
                }
                cout<<r.beautify()<<endl;
            }
            ifs.close();
        }
        
        cout<<"Try again? [Y/N] ";
        cin>>answer;
        if (answer == "N" || answer == "n") {
            cout<<"Finishing..."<<endl;
            break;
        }
    }
    
    return 0;
}

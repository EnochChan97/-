//
//  main.cpp
//  Caculater
//
//  Created by sean Chan on 2017/5/16.
//  Copyright © 2017年 sean Chan. All rights reserved.
//

#include <iostream>
#include "test.cpp"
#include "Scanner.hpp"
#include "Parser.hpp"
#include "Calc.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    Calc calc;
    STATUS status = STATUS_OK;
    do {
        string buf;
        cout<<"< ";
        getline(cin,buf);
        Scanner scanner(buf);
        Parser parser(scanner,calc);
        parser.Parse();
        double result = parser.Calculate();
        cout<<result<<endl;
    
    } while (status != STATUS_QUIT);
    
    return 0;
}

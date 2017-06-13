//
//  Parser.hpp
//  Caculater
//
//  Created by sean Chan on 2017/5/23.
//  Copyright © 2017年 sean Chan. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <stdio.h>
#include <string>

class Scanner;
class Node;
class Calc;
enum STATUS
{
    STATUS_OK,
    STATUS_QUIT,
    STATUS_ERROR
};

class Parser
{
public:
    Parser(Scanner& scanner,Calc& calc);
    void Parse();
    Node* Expr();
    Node* Term();
    Node* Factor();
    double Calculate()const;
private:
    Scanner& scanner_;
    Calc& calc_;
    Node* tree_;
    STATUS status_;
};
#endif /* Parser_hpp */

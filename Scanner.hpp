//
//  Scanner.hpp
//  Caculater
//
//  Created by sean Chan on 2017/5/23.
//  Copyright © 2017年 sean Chan. All rights reserved.
//

#ifndef Scanner_hpp
#define Scanner_hpp

#include <stdio.h>
#include <string>

enum ETOKEN
{
    TOKEN_END,
    TOKEN_ERROR,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPARENTHESIS,
    TOKEN_RPARENTHESIS,
    TOKEN_IDENTIFIER,
    TOKEN_ASSIGN
};
class Scanner{
public:
    Scanner(const std::string& buf);
    double Number()const;
    void Accept();
    ETOKEN Token()const;
    std::string GetSymbol()const;

private:
    void SkipWhite();
    const std::string buf_;
    ETOKEN token_;
    unsigned int curPos_;
    double number_;
    std::string symbol_;
};
#endif /* Scanner_hpp */

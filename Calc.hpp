//
//  Calc.hpp
//  Caculater
//
//  Created by sean Chan on 2017/6/13.
//  Copyright © 2017年 sean Chan. All rights reserved.
//

#ifndef Calc_hpp
#define Calc_hpp
#include "SymbolTable.hpp"
#include "Storage.hpp"
#include <stdio.h>
class Parser;
class Calc{
    friend class Parser;
public:
    Calc():storage_(sybTbl_){}
    unsigned int FindSymbol(const std::string& str)const{
        return sybTbl_.Find(str);
    }
    unsigned int AddSymbol(const std::string& str){
        return sybTbl_.Add(str);
    }
     Storage& getStorage(){
        return storage_;
    }
private:
    SymbolTable sybTbl_;
    Storage storage_;
};
#endif /* Calc_hpp */

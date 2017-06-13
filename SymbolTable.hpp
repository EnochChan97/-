//
//  SymbolTable.hpp
//  Caculater
//
//  Created by sean Chan on 2017/5/26.
//  Copyright © 2017年 sean Chan. All rights reserved.
//

#ifndef SymbolTable_hpp
#define SymbolTable_hpp
#include <map>
#include <string>
#include <stdio.h>

class SymbolTable
{
   
public:
    enum
    {
        IDNOTFOUND = 0xffffffff,
        
    };
    SymbolTable() : curId(0){}
    unsigned int Add(const std::string& str);
    unsigned int Find(const std::string& str)const;
    void Clear();
    std::string GetSymbolName(unsigned int id)const;
    ~SymbolTable();
private:
    std::map<std::string, unsigned int> dictionary_;
    unsigned int curId;
};

#endif /* SymbolTable_hpp */

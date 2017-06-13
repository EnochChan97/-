//
//  Storage.hpp
//  Caculater
//
//  Created by sean Chan on 2017/5/27.
//  Copyright © 2017年 sean Chan. All rights reserved.
//

#ifndef Storage_hpp
#define Storage_hpp

#include <stdio.h>
#include "SymbolTable.hpp"
#include <vector>
class Storage
{
public:
    Storage(SymbolTable& tbl);
    void Clear();
    bool IsInit(unsigned int id)const;
    void AddConstants(SymbolTable& tbl);
    double GetValue(unsigned int id)const;
    void SetValue(unsigned int id,double val);
    void AddValue(unsigned int id,double val);
private:
    std::vector<double> cells_;
    std::vector<bool> inits_;
};
#endif /* Storage_hpp */

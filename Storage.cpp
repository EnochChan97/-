//
//  Storage.cpp
//  Caculater
//
//  Created by sean Chan on 2017/5/27.
//  Copyright © 2017年 sean Chan. All rights reserved.
//

#include "Storage.hpp"
#include <cmath>
#include <cassert>
Storage::Storage(SymbolTable& tbl)
{
    AddConstants(tbl);
}

void Storage::Clear()
{
    cells_.clear();
    inits_.clear();
}

void Storage::AddConstants(SymbolTable& tbl)   //添加常量
{
    unsigned int id = tbl.Add("e");
    AddValue(id, exp(1.0));
    
    id = tbl.Add("pi");
    AddValue(id, 2.0*acos(0.0));    //反余弦 pi = 2*acos(0)
}
void Storage::AddValue(unsigned int id, double val)   //为变量或常量添加值
{
    
    cells_.resize(id+1);
    inits_.resize(id+1);
    cells_[id] = val;
    inits_[id] = true;
}

bool Storage::IsInit(unsigned int id)const
{
    return id < cells_.size() && inits_[id];
}

double Storage::GetValue(unsigned int id)const
{
    assert(id < cells_.size());
    return cells_[id];
}

void Storage::SetValue(unsigned int id, double val)
{
//    assert(id <= cells_.size());
    if (id < cells_.size())
    {
        cells_[id] = val;
        inits_[id] = true;
    }else if(id == cells_.size())
    {
        AddValue(id, val);
    }
    
}

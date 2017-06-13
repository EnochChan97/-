//
//  SymbolTable.cpp
//  Caculater
//
//  Created by sean Chan on 2017/5/26.
//  Copyright © 2017年 sean Chan. All rights reserved.
//
#include <string>
#include <map>
#include "SymbolTable.hpp"
SymbolTable::~SymbolTable(){}
unsigned int SymbolTable::Add(const std::string& str)
{
    dictionary_[str] = curId;
    return curId++;
}
unsigned int SymbolTable::Find(const std::string& str)const
{
   auto it = dictionary_.find(str);
    if (it != dictionary_.end()) return it->second;
    
    return IDNOTFOUND;
    
    
}
void SymbolTable::Clear()
{
    dictionary_.clear();
    curId = 0;
}

class IsEqualId
{
public:
    explicit IsEqualId(unsigned int id) : id_(id){}
    bool operator()(const std::pair<const std::string, unsigned int>& it)const
    {
        return it.second == id_;
    }
private:
    unsigned int id_;
};
std::string SymbolTable::GetSymbolName(unsigned int id)const
{
    auto it = std::find_if(dictionary_.begin(), dictionary_.end(), IsEqualId(id));
        return  it->first;

};

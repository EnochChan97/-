//
//  Mode.cpp
//  Caculater
//
//  Created by sean Chan on 2017/5/16.
//  Copyright © 2017年 sean Chan. All rights reserved.
//

#include "Node.hpp"
#include <iostream>
#include <cmath>
#include <cassert>
double NumberNode::Calc() const
{
    return number_;
}

BinaryNode::~BinaryNode(){
    delete left_;
    delete right_;
}
UnaryNode::~UnaryNode()
{
    delete child_;
}
/*
double AddNode::Calc() const
{
    return left_->Calc() + right_->Calc();
}

double SubNode::Calc() const
{
    return left_->Calc() - right_->Calc();
}

double MultiplyNode::Calc() const
{
    return left_->Calc() * right_->Calc();
}

double DivideNode::Calc() const
{
    double divisor = right_->Calc();
    if (divisor != 0)
        return left_->Calc() / divisor;
    else{
        std::cout<<"Error:divisor by zero\n ";
        return HUGE_VAL;
}
}
*/
double UMinusNode::Calc()const{
    return -child_->Calc();
}

MultipleNode::~MultipleNode(){
    std::vector<Node*>::const_iterator it;
    for (it = childs_.begin(); it != childs_.end(); ++it) {
        delete *it;   
    }
}

double SumNode::Calc()const
{
    double result = 0.0;
    std::vector<Node*>::const_iterator childIt = childs_.begin();
    std::vector<bool>::const_iterator positiveIt = positives_.begin();
    for (; childIt != childs_.end(); ++childIt,++positiveIt)
    {
        assert(positiveIt != positives_.end());
        double val = (*childIt)->Calc();
        if (*positiveIt)
            result += val;
        else
            result -= val;
    }
    assert(positiveIt == positives_.end());
    return result;
}


double ProductNode::Calc()const
{
    double result = 1;
    std::vector<Node*>::const_iterator childIt = childs_.begin();
    std::vector<bool>::const_iterator positiveIt = positives_.begin();
    for (; childIt != childs_.end(); ++childIt,++positiveIt)
    {
        assert(positiveIt != positives_.end());
        double val = (*childIt)->Calc();
        if (*positiveIt)
            result *= val;
        else if(val != 0.0)
            result /= val;
        else
        {
            std::cout<<"Division by zero"<<std::endl;
            return HUGE_VAL;
            
        }
    }
    assert(positiveIt == positives_.end());
    return result;
}

double VariableNode::Calc()const
{
    double x = 0.0;
    if (storage_.IsInit(id_))
    {
        x = storage_.GetValue(id_);
    }else
    {
        std::cout<<"Use of uninitialized variable"<<std::endl;
    }
    return x;
}

 bool VariableNode::IsLvalue()const
{
    return true;
}

void VariableNode::Assign(double val)
{
    storage_.SetValue(id_, val);
}


double AssignNode::Calc()const
{
    double x = 0.0;
    x = right_->Calc();
    left_->Assign(x);
    return x;
}

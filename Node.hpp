//
//  Mode.hpp
//  Caculater
//
//  Created by sean Chan on 2017/5/16.
//  Copyright © 2017年 sean Chan. All rights reserved.
//

#ifndef Mode_hpp
#define Mode_hpp
#include <vector>
#include <stdio.h>
#include <cassert>
#include "Storage.hpp"
class NoCopyable{
protected:
    NoCopyable(){}
    ~NoCopyable(){}
private:
    NoCopyable(const NoCopyable&);
    NoCopyable& operator=(const NoCopyable&);
    
};
class Node : private NoCopyable
{
public:
    virtual double Calc() const = 0;
    virtual ~Node(){};
    virtual bool IsLvalue()const
    {
        return false;
    }
    virtual void Assign(double val)
    {
        assert(!"Assign called incorrectlly");
    }
    
};

class NumberNode : public Node{
public:
    NumberNode(double number):number_(number){}
    double Calc() const;
private:
    const double number_;
};

class BinaryNode:public Node{
protected:
    Node* const left_;
    Node* const right_;
public:
    BinaryNode(Node* left,Node* right):left_(left),right_(right){}
    ~BinaryNode();
    
};

class UnaryNode:public Node{
public:
    UnaryNode(Node* child)
    :child_(child){}
    ~UnaryNode();
protected:
    Node* const child_;
};
/*
class AddNode:public BinaryNode{
public:
    AddNode(Node* left,Node* right):BinaryNode(left,right){}
    double Calc()const;
};

class   SubNode:public BinaryNode{
public:SubNode(Node* left,Node* right):BinaryNode(left,right){}
    double  Calc()const;
};

class MultiplyNode:public BinaryNode{
public:MultiplyNode(Node* left,Node* right):BinaryNode(left,right){}
    double  Calc()const;
};

class DivideNode:public BinaryNode{
public:DivideNode(Node* left,Node* right):BinaryNode(left,right){}
    double  Calc()const;
};
*/


class UMinusNode : public UnaryNode{
public:
    UMinusNode(Node* child):UnaryNode(child){}
    double Calc() const;
};

class MultipleNode : public Node
{
public:
    MultipleNode(Node* node)
    {
        AppendNode(node, true);
    };
    void AppendNode(Node* node,bool positive)
    {
        childs_.push_back(node);
        positives_.push_back(positive);
    };
    ~MultipleNode();
protected:
    std::vector<Node*> childs_;
    std::vector<bool> positives_;
};

class SumNode :public MultipleNode
{
public:
    SumNode(Node* node) : MultipleNode(node){}
    double Calc()const;
};

class ProductNode :public MultipleNode
{
public:
    ProductNode(Node* node) : MultipleNode(node){}
    double Calc()const;
};

class VariableNode : public Node
{
public:
    VariableNode(unsigned int id,Storage& storage)
    :id_(id),storage_(storage){}
     double Calc()const;
     bool IsLvalue()const;
     void Assign(double val);
private:
    unsigned int id_;
    Storage& storage_;
    
};

class AssignNode:public BinaryNode{
public:
    AssignNode(Node* left,Node* right):BinaryNode(left,right){}
    double Calc()const;
};


#endif /* Mode_hpp */

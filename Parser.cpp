//
//  Parser.cpp
//  Caculater
//
//  Created by sean Chan on 2017/5/23.
//  Copyright © 2017年 sean Chan. All rights reserved.
//

#include "Parser.hpp"
#include "Scanner.hpp"
#include "Node.hpp"
#include <cassert>
#include <iostream>
#include "Calc.hpp"
Parser::Parser(Scanner& scanner,Calc& calc) : scanner_(scanner),calc_(calc),tree_(nullptr)
{
    
}

void Parser::Parse(){
    tree_ = Expr();
}

Node* Parser::Expr()
{
    Node* node = Term();
    ETOKEN token = scanner_.Token();
    /*
    if (token == TOKEN_PLUS) {
        scanner_.Accept();
        Node* nodeRight = Expr();
        node = new AddNode(node,nodeRight);
    }else if (token == TOKEN_MINUS)
    {
        scanner_.Accept();
        Node* nodeRight = Expr();
        node = new SubNode(node,nodeRight);
    }
    */
    if (token == TOKEN_PLUS || token == TOKEN_MINUS)
    {
        MultipleNode* multipleNode = new SumNode(node);
        do {
            scanner_.Accept();
            Node* nextNode = Term();
            multipleNode->AppendNode(nextNode, (token == TOKEN_PLUS));
            token = scanner_.Token();
        } while (scanner_.Token() == TOKEN_PLUS || scanner_.Token() == TOKEN_MINUS);
            node  = multipleNode;
    }else if (token == TOKEN_ASSIGN)
    {
        
        scanner_.Accept();
        Node* nodeRight = Expr();
        if (node->IsLvalue())
        {
            node = new AssignNode(node,nodeRight);
            
        }else
        {
            status_ = STATUS_ERROR;
            std::cout<<"the left-hand side must be an assignable varibale"<<std::endl;
        }
    
    }

    return node;
}
Node* Parser::Term()
{
    Node* node = Factor();
    ETOKEN token = scanner_.Token();
    /*
    if (token == TOKEN_MULTIPLY) {
        scanner_.Accept();
        Node* nodeRight = Term();
        node = new MultiplyNode(node,nodeRight);
    }else if (token == TOKEN_DIVIDE)
    {
        scanner_.Accept();
        Node* nodeRight = Term();
        node = new DivideNode(node,nodeRight);
    }
     */
    if (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE)
    {
        MultipleNode* multipleNode = new ProductNode(node);
        do {
            //Term = Factor{ ('*'|'/') Factor }
            scanner_.Accept();
            Node* nextNode = Factor();
            multipleNode->AppendNode(nextNode, (token == TOKEN_MULTIPLY));
            token = scanner_.Token();
        } while (scanner_.Token() == TOKEN_MULTIPLY || scanner_.Token() == TOKEN_DIVIDE);
        node  = multipleNode;
    }
    return node;
}
Node* Parser::Factor()
{
    Node* node;
    ETOKEN token = scanner_.Token();
    if (token == TOKEN_LPARENTHESIS)
    {
        scanner_.Accept();     //accept'('
        node  = Expr();
        
        if (scanner_.Token() == TOKEN_RPARENTHESIS)
        {
            scanner_.Accept();      //accept')'
        }
        else
        {
            status_ = STATUS_ERROR;   //抛出异常
            std::cout<<"missing right parentheses"<<std::endl;
            node = nullptr;
        }
    }
    else if (token == TOKEN_NUMBER)
    {
        node = new NumberNode(scanner_.Number());
        scanner_.Accept();
    }else if(token == TOKEN_IDENTIFIER)
    {
        
        std::string symbol = scanner_.GetSymbol();
        unsigned int id = calc_.FindSymbol(symbol);
        scanner_.Accept();
        if (id == SymbolTable::IDNOTFOUND) {
            id = calc_.AddSymbol(symbol);
        }
        node = new VariableNode(id,calc_.getStorage());
    }
    else if (token == TOKEN_MINUS)
    {
        scanner_.Accept();
        node = new UMinusNode(Factor());
    }
    else{

        status_ = STATUS_ERROR;
        std::cout<<"not valid expression"<<std::endl;
    }
    return node;
}

double Parser::Calculate()const{
    assert(tree_ != 0);
    return tree_->Calc();
}


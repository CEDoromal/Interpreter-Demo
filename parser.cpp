#include <bits/stdc++.h>
#include "token.h"
#include "exitwmsg.cpp"

using namespace std;

//PARSER
vector<pair<string, token_t>>::iterator tokenIterator;
vector<pair<string, token_t>>::iterator tokenEnd;

vector<pair<string, token_t>> *ASTPointer;

void makeASTNode() {
    if (swapTokenMap.find(tokenIterator->second) != swapTokenMap.end() && swapTokenMap[tokenIterator->second]) {
        pair<string, token_t> temp = ASTPointer->back();
        ASTPointer->pop_back();
        ASTPointer->push_back(*tokenIterator);
        ASTPointer->push_back(temp);
        //cout<<"Swapped "<<temp.first<<":"<<temp.second<<" and "<<tokenIterator->first<<":"<<tokenIterator->second<<"\n";
    } else ASTPointer->push_back(*tokenIterator);
}

void nextToken() {
    if (tokenIterator < tokenEnd) ++tokenIterator;
}

bool accept(token_t targetToken) {
    if (tokenIterator->second == targetToken) {
        makeASTNode();
        nextToken();
        return true;
    }

    if (tokenIterator->second == TOKEN_UNIDENTIFIED) {
        exitwmsg("ERROR", 2);
        nextToken();
    }

    return false;
}

bool expect(token_t expectedToken) {
    if (accept(expectedToken)) return true;

    exitwmsg("ERROR", 2);
    nextToken();

    return false;
}

void factor() {
    if (accept(TOKEN_NUMBER)) {
        ;
    } else if (accept(TOKEN_IDENTIFIER)) {
        ;
    } else {
        exitwmsg("ERROR", 2);
        nextToken();
    }
}

void expression() {
    factor();
    if (accept(TOKEN_ADD) || accept(TOKEN_SUBTRACT)) {
        factor();
    }
}

void condition() {
    factor();
    if (accept(TOKEN_GREATER_THAN) || accept(TOKEN_LESS_THAN) || accept (TOKEN_EQUAL) || accept (TOKEN_NOT_EQUAL)) {
        factor();
    } else {
        exitwmsg("ERROR", 2);
        nextToken();
    }
}

void statement() {
    /*/
    if (accept(TOKEN_IF)) {
            expect(TOKEN_OPEN_PARENTHESIS);
            condition();
            expect(TOKEN_CLOSE_PARENTHESIS);
            statement();

    } else /*o*/ if (accept(TOKEN_IDENTIFIER)) {
        if (accept(TOKEN_COLON)) {
            if (accept(TOKEN_INT)) {
                ;
            } else if (accept(TOKEN_DOUBLE)) {
                ;
            } else {
                exitwmsg("ERROR", 2);
                nextToken();
            }
        } else if (accept(TOKEN_ASSIGN)) {
            expression();
        }

    } else if (accept(TOKEN_OUTPUT)) {
        expect(TOKEN_LEFT_SHIFT);
        if (accept(TOKEN_QUOTE)) {
            expect(TOKEN_STRING);
            expect(TOKEN_QUOTE);/*
        } else if (accept(TOKEN_NUMBER)) {
            ;
        } else if (accept(TOKEN_IDENTIFIER)) {
            ;
        } else {
            exitwmsg("ERROR", 2);
            nextToken();*/
        } else expression();
    }
}

vector<pair<string, token_t>> parser(vector<pair<string, token_t>> tokens) {
    vector<pair<string, token_t>> AST;
    ASTPointer = &AST;

    tokenIterator = tokens.begin();
    tokenEnd = tokens.end();

    while (tokenIterator < tokenEnd) {
        //*/
        if (accept(TOKEN_IF)) {
            expect(TOKEN_OPEN_PARENTHESIS);
            condition();
            expect(TOKEN_CLOSE_PARENTHESIS);
        } /*v*/
        statement();
        expect(TOKEN_SEMICOLON);
    }
    /*
    for (pair<string, token_t> element : AST) {
        cout<<element.first;
    }*/

    cout << "NO ERROR(S) FOUND\n\n";
    return AST;
}


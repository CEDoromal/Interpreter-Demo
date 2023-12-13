#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <bits/stdc++.h>

//TOKEN
enum token_t {
    //UNIDENTIFIED
    TOKEN_UNIDENTIFIED,

    //IDENTIFIER
    TOKEN_IDENTIFIER,

    //PUNCTUATION
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    TOKEN_OPEN_PARENTHESIS,
    TOKEN_CLOSE_PARENTHESIS,
    TOKEN_QUOTE,

    //OPERATOR
    TOKEN_ASSIGN,
    TOKEN_LEFT_SHIFT,
    TOKEN_GREATER_THAN,
    TOKEN_LESS_THAN,
    TOKEN_EQUAL,
    TOKEN_NOT_EQUAL,
    TOKEN_ADD,
    TOKEN_SUBTRACT,

    //KEYWORD
    TOKEN_INT,
    TOKEN_DOUBLE,
    TOKEN_OUTPUT,
    TOKEN_IF,

    //LITERAL
    TOKEN_NUMBER,
    TOKEN_STRING
};

std::map<std::string, token_t> keywordMap = {
    {"integer",     TOKEN_INT},
    {"double",  TOKEN_DOUBLE},
    {"output",  TOKEN_OUTPUT},
    {"if",      TOKEN_IF}
};

std::map<token_t, bool> swapTokenMap = {
    {TOKEN_UNIDENTIFIED,            false},
    {TOKEN_IDENTIFIER,              false},
    {TOKEN_COLON,                   true},
    {TOKEN_SEMICOLON,               false},
    {TOKEN_OPEN_PARENTHESIS,        false},
    {TOKEN_CLOSE_PARENTHESIS,       false},
    {TOKEN_QUOTE,                   false},
    {TOKEN_ASSIGN,                  true},
    {TOKEN_LEFT_SHIFT,              true},
    {TOKEN_GREATER_THAN,            true},
    {TOKEN_LESS_THAN,               true},
    {TOKEN_EQUAL,                   true},
    {TOKEN_NOT_EQUAL,               true},
    {TOKEN_ADD,                     true},
    {TOKEN_SUBTRACT,                true},
    {TOKEN_INT,                     false},
    {TOKEN_DOUBLE,                  false},
    {TOKEN_OUTPUT,                  false},
    {TOKEN_IF,                      false},
    {TOKEN_NUMBER,                  false},
    {TOKEN_STRING,                  false}
};

std::map<token_t, bool> writeTokenMap = {
    {TOKEN_UNIDENTIFIED,            false},
    {TOKEN_IDENTIFIER,              false},
    {TOKEN_COLON,                   true},
    {TOKEN_SEMICOLON,               true},
    {TOKEN_OPEN_PARENTHESIS,        true},
    {TOKEN_CLOSE_PARENTHESIS,       true},
    {TOKEN_QUOTE,                   true},
    {TOKEN_ASSIGN,                  true},
    {TOKEN_LEFT_SHIFT,              true},
    {TOKEN_GREATER_THAN,            true},
    {TOKEN_LESS_THAN,               true},
    {TOKEN_EQUAL,                   true},
    {TOKEN_NOT_EQUAL,               true},
    {TOKEN_ADD,                     true},
    {TOKEN_SUBTRACT,                true},
    {TOKEN_INT,                     true},
    {TOKEN_DOUBLE,                  true},
    {TOKEN_OUTPUT,                  true},
    {TOKEN_IF,                      true},
    {TOKEN_NUMBER,                  false},
    {TOKEN_STRING,                  false}
};


#endif // TOKEN_H_INCLUDED

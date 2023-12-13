#include <bits/stdc++.h>
#include "token.h"
#include "exitwmsg.cpp"

enum varType {
    VAR_INT,
    VAR_DOUBLE
};

using namespace std;

map<string, varType> symbolMap;
map<string, string> valueMap;

template<typename T>
T evaluate(vector<pair<string, token_t>>::iterator ASTIterator) {
    string value;
    switch (ASTIterator->second) {
        case TOKEN_IDENTIFIER:
            if (symbolMap.find(ASTIterator->first) == symbolMap.end()) exitwmsg("Undeclared Variable", 3);
            value = valueMap[ASTIterator->first];
            break;
        case TOKEN_NUMBER:
            value = ASTIterator->first;
            break;
        case TOKEN_ADD:
            value = to_string(evaluate<double>(++ASTIterator) + evaluate<double>(++ASTIterator));
            break;
        case TOKEN_SUBTRACT:
            value = to_string(evaluate<double>(++ASTIterator) - evaluate<double>(++ASTIterator));
            break;
        case TOKEN_GREATER_THAN:
            value = to_string(evaluate<double>(++ASTIterator) > evaluate<double>(++ASTIterator));
            break;
        case TOKEN_LESS_THAN:
            value = to_string(evaluate<double>(++ASTIterator) < evaluate<double>(++ASTIterator));
            break;
        case TOKEN_EQUAL:
            value = to_string(evaluate<double>(++ASTIterator) == evaluate<double>(++ASTIterator));
            break;
        case TOKEN_NOT_EQUAL:
            value = to_string(evaluate<double>(++ASTIterator) != evaluate<double>(++ASTIterator));
            break;
        case TOKEN_QUOTE:
            value = (++ASTIterator)->first;
            ++ASTIterator; //skip second "
            break;
    }
    stringstream stream(value);
    T convertedValue;
    if (stream >> convertedValue) return convertedValue;
    else exitwmsg("Conversion Error", 3);
}

void assignVar(string name, vector<pair<string, token_t>>::iterator ASTIterator) {
    string value;
    //varType type = symbolMap.find(name);
    if (symbolMap.find(name) == symbolMap.end()) exitwmsg("Undeclared Variable", 3);
    switch (symbolMap[name]) {
        case VAR_INT:
            value = to_string(evaluate<int>(ASTIterator));
            break;
        case VAR_DOUBLE:
            value = to_string(evaluate<double>(ASTIterator));
            break;
    }
    valueMap[name] = value;
}

void declareVar(string name, token_t type) {
    if (symbolMap.find(name) != symbolMap.end()) exitwmsg("Multiple Variable Declaration", 3);

    switch (type) {
        case TOKEN_INT:
            symbolMap[name] = VAR_INT;
            valueMap[name] = "0";
            break;
        case TOKEN_DOUBLE:
            symbolMap[name] = VAR_DOUBLE;
            valueMap[name] = "0";
            break;
    }
}

void interpret(vector<pair<string, token_t>> AST) {
    //system("cls"); //Clear screen (OPTIONAL)


    vector<pair<string, token_t>>::iterator ASTIterator = AST.begin();
    vector<pair<string, token_t>>::iterator ASTIteratorEnd = AST.end();

    while (ASTIterator<ASTIteratorEnd) {
        switch (ASTIterator->second) { //braces needed otherwise won't work
            case TOKEN_COLON: {
                string arg1 = (++ASTIterator)->first;
                token_t arg2 = (++ASTIterator)->second;
                declareVar(arg1, arg2);
                break;
            }
            case TOKEN_ASSIGN: {
                string arg1 = (++ASTIterator)->first;
                assignVar(arg1, ++ASTIterator);
                break;
            }
            case TOKEN_IF: {
                if(!evaluate<int>(++++ASTIterator)) //++ to Skip (
                    while (ASTIterator<ASTIteratorEnd && ASTIterator->second != TOKEN_SEMICOLON)
                        ++ASTIterator;
                break;
            }
            case TOKEN_LEFT_SHIFT: {
                switch ((++ASTIterator)->second) {
                    case (TOKEN_OUTPUT):
                        cout<<evaluate<string>(++ASTIterator)<<"\n";
                        break;
                }
                break;
            }
        }
        /*cout<<"\nsymbolMap dump:\n";
        map<string, varType>::iterator symMapIter;
        for(symMapIter = symbolMap.begin(); symMapIter != symbolMap.end(); ++symMapIter) {
            cout<<symMapIter->first<<":"<<symMapIter->second<<"\n";
        }*/
        ++ASTIterator;
    }

}

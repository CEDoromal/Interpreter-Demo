#include <bits/stdc++.h>
#include "token.h"
#include "exitwmsg.cpp"

using namespace std;

//LEXER

vector<pair<string, token_t>> tokenize(ifstream &inputFile) {
    vector<pair<string, token_t>> output;

    while (!inputFile.eof()) {
        char currChar = inputFile.get();

        if (currChar == EOF) break;
        if (isspace(currChar)) continue;

        string word = "";
        word += currChar;
        token_t token = TOKEN_UNIDENTIFIED;

        switch(currChar) {

            case ':':
                switch (inputFile.peek()) {
                    case '=':
                        word += inputFile.get();
                        token = TOKEN_ASSIGN;
                        break;
                    default:
                        token = TOKEN_COLON;
                }
                break;

            case ';':
                token = TOKEN_SEMICOLON;
                break;

            case '(':
                token = TOKEN_OPEN_PARENTHESIS;
                break;

            case ')':
                token = TOKEN_CLOSE_PARENTHESIS;
                break;

            case '<':
                switch (inputFile.peek()) {
                    case '<':
                        word += inputFile.get();
                        token = TOKEN_LEFT_SHIFT;
                        break;
                    default:
                        token = TOKEN_LESS_THAN;
                }
                break;

            case '>':
                token = TOKEN_GREATER_THAN;
                break;

            case '=':
                switch (inputFile.peek()) {
                    case '=':
                        word += inputFile.get();
                        token = TOKEN_EQUAL;
                        break;
                }
                break;

            case '!':
                switch (inputFile.peek()) {
                    case '=':
                        word += inputFile.get();
                        token = TOKEN_NOT_EQUAL;
                        break;
                }
                break;

            case '+':
                token = TOKEN_ADD;
                break;

            case '-':
                token = TOKEN_SUBTRACT;
                break;

            case '"':
                /*/ Add/Remove a '/' at the start of this line to switch out commented code

                //-------------------------------------------------------------------------//

                //NO SUPPORT FOR QUOTE TOKEN
                word = "";
                while (!inputFile.eof()) {
                    if (inputFile.peek() == '"') {
                        inputFile.ignore();
                        break;
                    }
                    word += inputFile.get();
                }
                token = TOKEN_STRING;

                /*/ //---------------------------------------------------------------------//

                //HAS SUPPORT FOR QUOTE TOKEN
                output.push_back(make_pair(word, TOKEN_QUOTE));
                word = "";
                while (!inputFile.eof()) {
                    if (inputFile.peek() == '"') break;
                    word += inputFile.get();
                }
                token = TOKEN_STRING;
                if (inputFile.peek() == '"') {
                    output.push_back(make_pair(word, token));
                    word = "";
                    word += inputFile.get();
                    token = TOKEN_QUOTE;
                }
                //*/

                break;

            default:
                if (isdigit(currChar)) {
                    while (!inputFile.eof() && (isdigit(inputFile.peek()) || inputFile.peek() == '.'))  {
                        word += inputFile.get();
                    }
                    token = TOKEN_NUMBER;
                }

                else if (isalpha(currChar)) {
                    while (!inputFile.eof() && (isalnum(inputFile.peek()) || inputFile.peek() == '_'))  {
                        word += inputFile.get();
                    }
                    if (keywordMap.find(word) != keywordMap.end()) {
                        token = keywordMap[word];
                    } else {
                        token = TOKEN_IDENTIFIER;
                    }
                }
        }

        output.push_back(make_pair(word, token));
    }

    return output;
}

vector<pair<string, token_t>> lexer(string inputPath, bool generateFiles = false) {
    ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
		exitwmsg("Cannot open file on" + inputPath, 1);
	}

	vector<pair<string, token_t>> tokens = tokenize(inputFile);
	inputFile.close();

	if (generateFiles) {
        ofstream outlex("NOSPACES.TXT");
        ofstream keywords("RES_SYM.TXT");

        for (pair<string, token_t> element : tokens) {
            /*/ //NO SUPPORT FOR QUOTE TOKEN
            if (element.second == TOKEN_STRING) outlex << '"' << element.first << '"';
            else outlex << element.first;
            /*/ //HAS SUPPORT FOR QUOTE TOKEN
            outlex << element.first;
            //*/

            if (writeTokenMap.find(element.second) != writeTokenMap.end() && writeTokenMap[element.second]) {
                keywords << element.first << '\n';
            }
        }
        outlex.close();
        keywords.close();
	}

	return tokens;
}

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

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

enum token_c {
    CATEGORY_UNIDENTIFIED,
    CATEGORY_IDENTIFIER,
    CATEGORY_PUNCTUATION,
    CATEGORY_OPERATOR,
    CATEGORY_KEYWORD,
    CATEGORY_LITERAL
};

map<token_t, token_c> tokenCategoryMap = {
    {TOKEN_UNIDENTIFIED,            CATEGORY_UNIDENTIFIED},

    {TOKEN_IDENTIFIER,              CATEGORY_IDENTIFIER},

    {TOKEN_COLON,                   CATEGORY_PUNCTUATION},
    {TOKEN_SEMICOLON,               CATEGORY_PUNCTUATION},
    {TOKEN_OPEN_PARENTHESIS,        CATEGORY_PUNCTUATION},
    {TOKEN_CLOSE_PARENTHESIS,       CATEGORY_PUNCTUATION},
    {TOKEN_QUOTE,                   CATEGORY_PUNCTUATION},

    {TOKEN_ASSIGN,                  CATEGORY_OPERATOR},
    {TOKEN_LEFT_SHIFT,              CATEGORY_OPERATOR},
    {TOKEN_GREATER_THAN,            CATEGORY_OPERATOR},
    {TOKEN_LESS_THAN,               CATEGORY_OPERATOR},
    {TOKEN_EQUAL,                   CATEGORY_OPERATOR},
    {TOKEN_ADD,                     CATEGORY_OPERATOR},
    {TOKEN_SUBTRACT,                CATEGORY_OPERATOR},

    {TOKEN_INT,                     CATEGORY_KEYWORD},
    {TOKEN_DOUBLE,                  CATEGORY_KEYWORD},
    {TOKEN_OUTPUT,                  CATEGORY_KEYWORD},
    {TOKEN_IF,                      CATEGORY_KEYWORD},

    {TOKEN_NUMBER,                  CATEGORY_LITERAL},
    {TOKEN_STRING,                  CATEGORY_LITERAL}
};

map<string, token_t> keywordMap = {
    {"int",     TOKEN_INT},
    {"double",  TOKEN_DOUBLE},
    {"output",  TOKEN_OUTPUT},
    {"if",      TOKEN_IF}
};

map<token_t, bool> writeTokenMap = {
    {TOKEN_UNIDENTIFIED,            false},
    {TOKEN_IDENTIFIER,              false},
    {TOKEN_COLON,                   false},
    {TOKEN_SEMICOLON,               false},
    {TOKEN_OPEN_PARENTHESIS,        false},
    {TOKEN_CLOSE_PARENTHESIS,       false},
    {TOKEN_QUOTE,                   false},
    {TOKEN_ASSIGN,                  false},
    {TOKEN_LEFT_SHIFT,              true},
    {TOKEN_GREATER_THAN,            false},
    {TOKEN_LESS_THAN,               false},
    {TOKEN_EQUAL,                   false},
    {TOKEN_ADD,                     false},
    {TOKEN_SUBTRACT,                false},
    {TOKEN_INT,                     true},
    {TOKEN_DOUBLE,                  true},
    {TOKEN_OUTPUT,                  true},
    {TOKEN_IF,                      true},
    {TOKEN_NUMBER,                  false},
    {TOKEN_STRING,                  false}
};

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
		cout << "unable to open file\n";
		exit(1);
	}

	vector<pair<string, token_t>> tokens = tokenize(inputFile);
	inputFile.close();

	if (generateFiles) {
        ofstream outlex("outlex.txt");
        ofstream keywords("keywords.txt");

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


// PARSER
class node {
    private:
        pair<string, token_t> content;
        node *parent;
        vector<node> children;
    public:
        node(pair<string, token_t> c) {
            content = c;
            parent = nullptr;
        }
        pair<string, token_t> getContent() {return content;}
        node *getParent() {return parent;}
        void setParent(node *p) {parent = p;}
        vector<node> getChildren() {return children;}

        void addChild(node &n) {
            n.getChildren().push_back(n);
        }
};

pair<string, token_t> *parser(vector<pair<string, token_t>> tokens) {
    pair<string, token_t> output[tokens.size()];

    return output;
}
//





map<string, int> phaseMap = {
    {"1", 1},
    {"2", 2}
};

int main(int argc, char *argv[]) {

    string inputPath = "./input.hl";
    bool generateLexFiles = true;
    int phase = 2;

    if (argc == 2) {
        inputPath = argv[1];
        generateLexFiles = true;
    }
    if (argc > 2) {
        for (int i = 1; i < argc; ++i) {

            //Doesn't need follow-up arguments
            if (strcmp(argv[i], "-nl") == 0 || strcmp(argv[i], "--no-lex-files") == 0) {
                generateLexFiles = false;
                continue;
            }

            //Needs follow-up arguments
            if (i+1 <= argc) {
                if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
                    inputPath = argv[++i];
                    continue;
                }
                if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--phase") == 0) {
                    string p = argv[++i];
                    if (phaseMap.find(p) != phaseMap.end()) {
                        phase = phaseMap[p];
                    }
                    continue;
                }
            }
        }
    }

    switch (phase) {
        case 1:
            lexer(inputPath, generateLexFiles);
            break;
        case 2:
            parser(lexer(inputPath, generateLexFiles));
            //TODO: Parser
            break;
    }



    return 0;
}

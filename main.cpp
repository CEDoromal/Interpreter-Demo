#include <fstream>
#include <bits/stdc++.h>
#include "lex.cpp"
#include "parser.cpp"
#include "interpreter.cpp"

using namespace std;

//MAIN PROGRAM
map<string, int> phaseMap = {
    {"1", 1},
    {"2", 2},
    {"3", 3}
};

int main(int argc, char *argv[]) {
    string inputPath = "./input.hl";
    bool generateLexFiles = true;
    int phase = 3;

    if (argc == 2) {
        inputPath = argv[1];
        generateLexFiles = true;
    }
    if (argc > 2) {
        for (int i = 1; i < argc; ++i) {

            //Doesn't need follow-up arguments
            if (strcmp(argv[i], "--no-lex-files") == 0) {
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
            break;
        case 3:
            interpret(parser(lexer(inputPath, generateLexFiles)));
            break;
    }

    if(argc <= 2) exitwmsg("Exiting Interpreter");
    return 0;
}

//
//  main.cpp
//  Project 1 - Lexer
//
//  Created by Nicholas McMurdie on 9/15/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, const char * argv[]) {
    vector<Token*> tokens;
    
    // Open input file
    if (argc < 2) {
        cerr << "Please provide name of input file" << endl;
        return 1;
    }
    
    ifstream ifs(argv[1]);
    if (!ifs)  {
        cerr << "Unable to open " << argv[1] << " for input" << endl;
        return 2;
    }
    
    // Copy file to input string
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
    
    // Convert code into tokens using Lexer
    Lexer lex;
    lex.run(input);
    tokens = lex.getTokens();
    
    // Run tokens through parser
    Parser parser(tokens);
    DatalogProgram prgm = parser.getDatalog();
    
    // Interpret tokens
    Interpreter inter(prgm);
    
    return 0;
}


//
//  Lexer.h
//  Project 1 - Lexer
//
//  Created by Nicholas McMurdie on 9/15/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef Lexer_h
#define Lexer_h

#include <vector>
#include "MatcherAutomoton.h"
#include "IDAutomoton.h"
#include "StringAutomoton.h"
#include "CommentAutomoton.h"
#include "UndefinedAutomoton.h"

class Lexer {
private:
    std::vector<Token*> tokens;
    std::vector<Automoton*> machines;
    
public:
    Lexer() {
        machines.push_back(new MatcherAutomoton(",", TokenType(COMMA)));
        machines.push_back(new MatcherAutomoton(".", TokenType(PERIOD)));
        machines.push_back(new MatcherAutomoton("?", TokenType(Q_MARK)));
        machines.push_back(new MatcherAutomoton("(", TokenType(LEFT_PAREN)));
        machines.push_back(new MatcherAutomoton(")", TokenType(RIGHT_PAREN)));
        machines.push_back(new MatcherAutomoton(":", TokenType(COLON)));
        machines.push_back(new MatcherAutomoton(":-", TokenType(COLON_DASH)));
        machines.push_back(new MatcherAutomoton("*", TokenType(MULTIPLY)));
        machines.push_back(new MatcherAutomoton("+", TokenType(ADD)));
        machines.push_back(new MatcherAutomoton("Schemes", TokenType(SCHEMES)));
        machines.push_back(new MatcherAutomoton("Facts", TokenType(FACTS)));
        machines.push_back(new MatcherAutomoton("Rules", TokenType(RULES)));
        machines.push_back(new MatcherAutomoton("Queries", TokenType(QUERIES)));
        machines.push_back(new UndefinedAutomoton());
        machines.push_back(new IDAutomoton());
        machines.push_back(new StringAutomoton());
        machines.push_back(new CommentAutomoton());
    }
    
    void run(std::string input) {
        int lineNumber = 1;
        
        while (input.size() > 0) {
            if (input[0] == '\n') ++lineNumber;
            if (input[0] == ' ' || input[0] == '\n' || input[0] == '\t') {
                input = input.substr(1);
                continue;
            }
            
            int maxRead = 0, maxNewLines = 0;
            Automoton* maxMachine = machines.at(0);
            
            for (int i = 0; i < (int)machines.size(); ++i) {
                int numRead = machines.at(i) -> read(input);
                if (numRead > maxRead) {
                    maxRead = numRead;
                    maxNewLines = machines.at(i) -> newLinesRead();
                    maxMachine = machines.at(i);
                }
            }
            
            // Add token from best machine
            if (maxRead > 0 && !isdigit(input[0])) {
                Token* t = maxMachine -> createToken(input.substr(0, maxRead), lineNumber);
                if (t -> getType().toString() != TokenType(COMMENT).toString()) tokens.push_back(t);
                lineNumber += maxNewLines;
            }
            // If no machine recognized, add UNDEFINED token
            else {
                std::string error = "";
                error.push_back(input[0]);
                maxRead = 1;
                TokenType type(UNDEFINED);
                tokens.push_back(new Token(type, error, lineNumber));
            }
            
            input = input.substr(maxRead);
        }
        
        // Insert EOF token
        TokenType fileEnd(FILE_END);
        tokens.push_back(new Token(fileEnd, "", lineNumber));
    }
    
    std::vector<Token*> getTokens() {
        return tokens;
    }
};

#endif /* Lexer_h */

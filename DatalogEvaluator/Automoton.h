//
//  Automoton.h
//  Project 1 - Lexer
//
//  Created by Nicholas McMurdie on 9/15/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef Automoton_h
#define Automoton_h

#include "Token.h"

class Automoton {
protected:
    int newLines = 0;
    TokenType type;
    
public:
    Automoton(TokenType type) : type(type) {}
    
    virtual int read(const std::string& input) = 0;
    
    virtual Token* createToken(std::string input, int lineNumber) {
        return new Token(type, input, lineNumber);
    }
    
    virtual int newLinesRead() const { return newLines; }
};

#endif /* Automoton_h */

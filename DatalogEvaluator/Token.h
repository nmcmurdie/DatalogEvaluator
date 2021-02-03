//
//  Token.h
//  Project 1 - Lexer
//
//  Created by Nicholas McMurdie on 9/15/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef Token_h
#define Token_h

#include <sstream>
#include "TokenType.h"

class Token {
private:
    TokenType type;
    std::string input;
    int lineNumber;
    
    friend std::ostream& operator<<(std::ostream& os, Token& t) {
        os << t.toString();
        return os;
    }
    
public:
    Token(TokenType type, std::string input, int lineNumber) : type(type), input(input), lineNumber(lineNumber) {}
    
    TokenType getType() const {
        return type;
    }
    
    std::string getContent() const {
        return input;
    }
    
    std::string toString() {
        std::ostringstream out;
        out << "(" << type << ",\"" << input << "\"," << lineNumber << ")";
        return out.str();
    }
};

#endif /* Token_h */

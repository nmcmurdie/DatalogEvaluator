//
//  TokenType.h
//  Project 1 - Lexer
//
//  Created by Nicholas McMurdie on 9/15/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef TokenType_h
#define TokenType_h

#include <sstream>
#include <string>

enum TType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD,
    SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, FILE_END};

class TokenType {
private:
    TType type;
    
    friend std::ostream& operator<<(std::ostream& os, TokenType& o) {
        os << o.toString();
        return os;
    }
    
    friend bool operator==(const TokenType& lhs, const TokenType& rhs) {
        return lhs.getType() == rhs.getType();
    }
    
public:
    TokenType(TType type) : type(type) {}
    
    TType getType() const {
        return type;
    }
    
    std::string toString() const {
        switch (type) {
            case COMMA: return "COMMA"; break;
            case PERIOD: return "PERIOD"; break;
            case Q_MARK: return "Q_MARK"; break;
            case LEFT_PAREN: return "LEFT_PAREN"; break;
            case RIGHT_PAREN: return "RIGHT_PAREN"; break;
            case COLON: return "COLON"; break;
            case COLON_DASH: return "COLON_DASH"; break;
            case MULTIPLY: return "MULTIPLY"; break;
            case ADD: return "ADD"; break;
            case SCHEMES: return "SCHEMES"; break;
            case FACTS: return "FACTS"; break;
            case RULES: return "RULES"; break;
            case QUERIES: return "QUERIES"; break;
            case ID: return "ID"; break;
            case STRING: return "STRING"; break;
            case COMMENT: return "COMMENT"; break;
            case UNDEFINED: return "UNDEFINED"; break;
            case FILE_END: return "EOF"; break;
            default: return "ERROR";
        }
    }
};

#endif /* TokenType_h */

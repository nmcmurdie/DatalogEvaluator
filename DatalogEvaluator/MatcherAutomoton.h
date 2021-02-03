//
//  MatcherAutomoton.h
//  Project 1 - Lexer
//
//  Created by Nicholas McMurdie on 9/16/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef MatcherAutomoton_h
#define MatcherAutomoton_h

#include "Automoton.h"
#include "TokenType.h"

class MatcherAutomoton : public Automoton {
private:
    std::string toMatch;
    
public:
    MatcherAutomoton(std::string match, TokenType type) : Automoton(type), toMatch(match) {}
    
    int read(const std::string& input) {
        int numRead = 0;
        
        for (int i = 0; i < (int)input.size() && i < (int)toMatch.size(); ++i) {
            if (input[i] == toMatch[i]) ++numRead;
            else {
                numRead = 0;
                break;
            }
        }
        
        return numRead;
    }
};

#endif /* MatcherAutomoton_h */

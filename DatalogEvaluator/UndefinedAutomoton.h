//
//  UndefinedAutomoton.h
//  Project 1 - Lexer
//
//  Created by Nicholas McMurdie on 9/16/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef UndefinedAutomoton_h
#define UndefinedAutomoton_h

#include "Automoton.h"

class UndefinedAutomoton : public Automoton {
public:
    UndefinedAutomoton() : Automoton(TokenType(UNDEFINED)) {}
    
    int read(const std::string& input) {
        newLines = 0;
        // Produce UNDEFINED token when multi-line comment isn't ended (capped)
        if ((int)input.size() > 1 && input[0] == '#' && input[1] == '|') {
            bool missingCap = true;
            
            for (int i = 2; i < (int)input.size() && missingCap; ++i) {
                if (i < (int)input.size() - 1 && input[i] == '|' && input[i + 1] == '#') missingCap = false;
                else if (input[i] == '\n') ++newLines;
                
            }
            
            return missingCap ? (int)input.size() : 0;
        }
        // Produce UNDEFINED token when string isn't closed (capped)
        else if (input[0] == '\'') {
            bool missingCap = true;
            
            for (int i = 1; i < (int)input.size() && missingCap; ++i) {
                // Skip over double paren
                if (i < (int)input.size() - 1 && input[i] == '\'' && input[i + 1] == '\'') {
                    ++i;
                    continue;
                }
                else if (input[i] == '\'') missingCap = false;
                else if (input[i] == '\n') ++newLines;
            }
            
            return missingCap ? (int)input.size() : 0;
        }
        return 0;
    }
};

#endif /* UndefinedAutomoton_h */

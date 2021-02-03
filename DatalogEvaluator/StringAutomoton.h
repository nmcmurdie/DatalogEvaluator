//
//  StringAutomoton.h
//  Project 1 - Lexer
//
//  Created by Nicholas McMurdie on 9/16/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef StringAutomoton_h
#define StringAutomoton_h

#include "Automoton.h"

class StringAutomoton : public Automoton {
public:
    StringAutomoton() : Automoton(TokenType(STRING)) {}
    
    int read(const std::string& input) {
        newLines = 0;
        int numRead = 0;
        bool isMatch = true;
        
        for (int i = 0; i < (int)input.size() && isMatch; ++i, ++numRead) {
            if (i == 0 && input[i] != '\'') isMatch = false;
            // Skip over 2 adjacent parens
            else if (i > 0 && i < (int)input.size() - 1 &&
                     input[i] == '\'' && input[i + 1] == '\'') {
                ++i;
                ++numRead;
                continue;
            }
            else if (i > 0 && input[i] == '\n') ++newLines;
            else if (i > 0 && input[i] == '\'') {
                ++numRead;
                break;
            }
        }
        
        return isMatch ? numRead : 0;
    }
};

#endif /* StringAutomoton_h */

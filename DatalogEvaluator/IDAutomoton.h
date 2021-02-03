//
//  IDAutomoton.h
//  Project 1 - Lexer
//
//  Created by Nicholas McMurdie on 9/16/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef IDAutomoton_h
#define IDAutomoton_h

#include "Automoton.h"

class IDAutomoton : public Automoton {
public:
    IDAutomoton() : Automoton(TokenType(ID)) {}
    
    int read(const std::string& input) {
        int numRead = 0;
        
        for (int i = 0; i < (int)input.size(); ++i, ++numRead) {
            if ((i == 0 && !isalpha(input[i]))
                || (i > 0 && !isalpha(input[i]) && !isdigit(input[i]))) break;
        }
        return numRead;
    }
};

#endif /* IDAutomoton_h */

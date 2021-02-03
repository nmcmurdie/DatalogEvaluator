//
//  CommentAutomoton.h
//  Project 1 - Lexer
//
//  Created by Nicholas McMurdie on 9/16/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef CommentAutomoton_h
#define CommentAutomoton_h

#include "Automoton.h"

class CommentAutomoton : public Automoton {
public:
    CommentAutomoton() : Automoton(TokenType(COMMENT)) {}
    
    int read(const std::string& input) {
        newLines = 0;
        int numRead = 0;
        
        // Detect single-line comment
        if (input[0] == '#' && ((int)input.size() < 2 || input[1] != '|')) {
            bool isMatch = true;
            
            for (int i = 0; i < (int)input.size() && isMatch; ++i, ++numRead) {
                if (i == 0 && input[i] != '#') isMatch = false;
                else if (i > 0 && input[i] == '\n') {
                    isMatch = false;
                    --numRead;
                }
            }
            
            return numRead;
        }
        // Detect multi-line comment
        else if ((int)input.size() > 1 && input[0] == '#' && input[1] == '|'){
            if (input[0] != '#' || input[1] != '|') return 0;
            else {
                for (int i = 2; i < (int)input.size(); ++i, ++numRead) {
                    if (i < (int)input.size() - 1 && input[i] == '|' && input[i + 1] == '#') {
                        numRead += 4;
                        break;
                    }
                    else if (input[i] == '\n') ++newLines;
                }
                
                return numRead;
            }
        }
        return 0;
    }
};

#endif /* CommentAutomoton_h */

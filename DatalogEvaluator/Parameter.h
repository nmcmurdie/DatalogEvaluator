//
//  Parameter.h
//  Project 2 - Parser
//
//  Created by Nicholas McMurdie on 10/4/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef Parameter_h
#define Parameter_h

#include <vector>
#include <ostream>
#include "Token.h"

class Parameter {
private:
    std::vector<std::string> tokens;
    bool constant = false;
    
public:
    Parameter(std::vector<Token*> tokens) {
        for (size_t i = 0; i < tokens.size(); ++i)
            this -> tokens.push_back(tokens.at(i) -> getContent());
        if (tokens.at(0) -> getContent().at(0) == '\'') constant = true;
    }
    
    Parameter(Token* token) {
        tokens.push_back(token -> getContent());
        if (token -> getContent().at(0) == '\'') constant = true;
    }
    
    bool isConstant() const {
        return this -> constant;
    }
    
    std::string toString() {
        std::ostringstream out;
        out << tokens.at(0);
        
        for (size_t i = 1; i < tokens.size(); ++i)
            out << tokens.at(i);
        
        return out.str();
    }
};

#endif /* Parameter_h */

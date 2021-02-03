//
//  Predicate.h
//  Project 2 - Parser
//
//  Created by Nicholas McMurdie on 10/4/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef Predicate_h
#define Predicate_h

#include "Parameter.h"

class Predicate {
private:
    std::string ID;
    std::vector<Parameter> params;
    
public:
    Predicate(Token* ID, std::vector<Parameter> params) : ID(ID -> getContent()), params(params) {}
    
    std::string getID() const {
        return this -> ID;
    }
    
    std::vector<Parameter> getParams() const {
        return this -> params;
    }
    
    std::string toString() {
        std::ostringstream out;
        out << ID << "(" << params.at(0).toString();
        
        for (size_t i = 1; i < params.size(); ++i) {
            out << "," << params.at(i).toString();
        }
        
        out << ")";
        
        return out.str();
    }
};

#endif /* Predicate_h */

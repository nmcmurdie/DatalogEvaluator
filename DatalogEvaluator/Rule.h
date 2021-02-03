//
//  Rule.h
//  Project 2 - Parser
//
//  Created by Nicholas McMurdie on 10/4/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef Rule_h
#define Rule_h

#include "Predicate.h"

class Rule {
private:
    Predicate head;
    std::vector<Predicate> body;
    
public:
    Rule(Predicate head, std::vector<Predicate> body) : head(head), body(body) {}
    
    Predicate headPredicate() {
        return this -> head;
    }
    
    std::vector<Predicate> bodyPredicates() {
        return this -> body;
    }
    
    std::string toString() {
        std::ostringstream out;
        out << head.toString() << " :- " << body.at(0).toString();
        
        for (size_t i = 1; i < body.size(); ++i) {
            out << "," << body.at(i).toString();
        }
        
        out << ".";
        return out.str();
    }
};

#endif /* Rule_h */

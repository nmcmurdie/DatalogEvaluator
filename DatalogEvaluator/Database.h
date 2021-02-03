//
//  Database.h
//  Project 3 - Interpreter
//
//  Created by Nicholas McMurdie on 11/1/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef Database_h
#define Database_h

#include <map>
#include "Relation.h"

class Database {
private:
    std::map<std::string, Relation*> relations;
    
public:
    void addRelation(Relation* r) {
        relations.insert(std::pair<std::string, Relation*>(r -> getName(), r));
    }
    
    void setRelation(std::string name, Relation* r) {
        std::map<std::string, Relation*>::iterator itr = relations.find(name);
        
        if (itr != relations.end()) itr -> second = r;
    }
    
    Relation* getRelation(std::string name) {
        return relations.find(name) -> second;
    }
};

#endif /* Database_h */

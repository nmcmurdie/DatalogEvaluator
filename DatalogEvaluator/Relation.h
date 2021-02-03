//
//  Relation.h
//  Project 3 - Interpreter
//
//  Created by Nicholas McMurdie on 11/1/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef Relation_h
#define Relation_h

#include "Tuple.h"
#include "Header.h"

class Relation {
private:
    std::string name;
    Header head;
    std::set<Tuple> tuples;
    
    bool contains(std::vector<std::string>& array, std::string val) {
        bool found = false;
        for (size_t i = 0; i < array.size(); ++i) {
            if (array.at(i) == val) found = true;
        }
        return found;
    }
    
public:
    Relation(std::string name, Header head) : name(name), head(head) {}
    
    bool addTuple(Tuple tuple) {
        return tuples.insert(tuple).second;
    }
    
    std::string getName() const {
        return name;
    }
    
    int size() const {
        return (int) this -> tuples.size();
    }
    
    bool isEmpty() const {
        return tuples.empty();
    }
    
    std::string toString() const {
        std::ostringstream out;
        
        for (Tuple t : tuples) {
            std::vector<Parameter> params = t.getContents();
            std::vector<std::string> headers = head.getContents();
            
            if (headers.size() > 0) {
                std::cout << "  " << headers.at(0) << "=" << params.at(0).toString();
            
                for (size_t i = 1; i < params.size(); ++i) {
                    std::cout << ", " << headers.at(i) << "=" << params.at(i).toString();
                }
                
                std::cout << std::endl;
            }
        }
        
        return out.str();
    }
    
    Relation* select(int index, std::string value) {
        Relation* r = new Relation(name, head);
        
        for (Tuple t : tuples) {
            std::string match = t.getValues().at(index);
            if (value == match) r -> addTuple(t);
        }
        
        return r;
    }
    
    Relation* select(int index1, int index2) {
        Relation* r = new Relation(name, head);
        
        for (Tuple t : tuples) {
            std::vector<std::string> contents = t.getValues();
            std::string match = contents.at(index2);
            std::string value = contents.at(index1);
            if (value == match) r -> addTuple(t);
        }
        
        return r;
    }
    
    Relation* project(std::vector<int> indices) {
        Relation* r = new Relation(name, head.project(indices));
        
        for (Tuple t : tuples) r -> addTuple(t.project(indices));
        
        return r;
    }
    
    Relation* rename(std::vector<std::string>& values) {
        Relation* r = new Relation(name, Header(values));
        
        for (Tuple t : tuples) r -> addTuple(t);
        
        return r;
    }
    
    std::set<Tuple> getTuples() {
        return this -> tuples;
    }
    
    Header getHeader() {
        return this -> head;
    }
    
    std::pair<Relation*, Relation*> combine(Relation* rel) {
        Relation* r = new Relation(name, head);
        Relation* d = new Relation(name, head);
        
        for (Tuple t : this -> tuples) r -> addTuple(t);
        for (Tuple t : rel -> getTuples()) {
            if (r -> addTuple(t)) d -> addTuple(t);
        }
        
        return std::make_pair(r, d);
    }
    
    Relation* join(Relation* rel) {
        std::vector<std::pair<int, int>> matchingCols;
        std::vector<std::string> origHead = head.getContents(),
                                 joinHead = rel -> getHeader().getContents(),
                                 resHead = head.getContents();
        std::vector<int> joinProject;
        std::set<Tuple> joinTuples = rel -> getTuples();
        
        for (size_t i = 0; i < origHead.size(); ++i) {
            for (int j = 0; j < (int) joinHead.size(); ++j) {
                if (origHead.at(i) == joinHead.at(j)) {
                    matchingCols.push_back(std::make_pair(i, j));
                }
                else if (!contains(resHead, joinHead.at(j))) {
                    resHead.push_back(joinHead.at(j));
                    joinProject.push_back(j);
                }
            }
        }
        Relation* r = new Relation(name, Header(resHead));
        
        for (Tuple x : this -> tuples) {
            for (Tuple y : joinTuples) {
                bool combine = true;
                for (size_t i = 0; i < matchingCols.size(); ++i) {
                    std::pair<int, int> toMatch = matchingCols.at(i);
                    if (x.valAt(toMatch.first) != y.valAt(toMatch.second)) {
                        combine = false;
                        break;
                    }
                }
                
                if (combine) r -> addTuple(x.combine(y.project(joinProject)));
            }
        }
        
        return r;
    }
};


#endif /* Relation_h */

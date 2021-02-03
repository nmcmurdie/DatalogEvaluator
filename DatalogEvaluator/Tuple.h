//
//  Tuple.h
//  Project 3 - Interpreter
//
//  Created by Nicholas McMurdie on 11/1/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef Tuple_h
#define Tuple_h

#include <vector>
#include <sstream>

class Tuple {
private:
    std::vector<Parameter> params;
    std::vector<std::string> values;
    
public:
    Tuple(std::vector<Parameter> list) : params(list) {
        for (Parameter p : list) values.push_back(p.toString());
    }
    
    std::vector<Parameter> getContents() const {
        return this -> params;
    }
    
    bool constantAt(int index) const {
        return params.at(index).isConstant();
    }
    
    std::string valAt(int index) const {
        return values.at(index);
    }
    
    std::vector<std::string> getValues() const {
        return this -> values;
    }
    
    Tuple combine(Tuple t) {
        std::vector<Parameter> p = params, q = t.getContents();
        p.insert(p.end(), q.begin(), q.end());
        
        return Tuple(p);
    }
    
    Tuple project(std::vector<int> indices) {
        std::vector<Parameter> output;
        
        for (size_t i = 0; i < indices.size(); ++i) {
            output.push_back(params.at(indices.at(i)));
        }
        
        return Tuple(output);
    }
    
    std::string toString() const {
        std::ostringstream out;
        out << values.at(0);
        for (size_t i = 1; i < values.size(); ++i) out << ", " << values.at(i);
        
        return out.str();
    }
    
    bool operator< (const Tuple& other) const {
        return values < other.getValues();
    }
    
    bool operator== (const Tuple& other) const {
        return values == other.getValues();
    }
    
};


#endif /* Tuple_h */

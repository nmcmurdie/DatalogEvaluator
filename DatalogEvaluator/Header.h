//
//  Header.h
//  Project 3 - Interpreter
//
//  Created by Nicholas McMurdie on 11/1/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <vector>
#include "Parameter.h"

class Header {
private:
    std::vector<std::string> values;
    
public:
    Header(std::vector<Parameter> values) {
        for (Parameter p : values) {
            this -> values.push_back(p.toString());
        }
    }
    
    Header(std::vector<std::string> values) : values(values) {}
    
    std::vector<std::string> getContents() const {
        return this -> values;
    }
    
    Header project(std::vector<int> indices) {
        std::vector<std::string> output;
        
        for (size_t i = 0; i < indices.size(); ++i) {
            output.push_back(values.at(indices.at(i)));
        }
        
        return Header(output);
    }
    
    std::string toString() const {
        std::ostringstream out;
        out << values.at(0);
        for (size_t i = 1; i < values.size(); ++i) out << ", " << values.at(i);
        
        return out.str();
    }
};

#endif /* Header_h */

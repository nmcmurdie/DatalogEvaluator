//
//  DatalogProgram.h
//  Project 2 - Parser
//
//  Created by Nicholas McMurdie on 10/4/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef DatalogProgram_h
#define DatalogProgram_h

#include <set>
#include "Rule.h"

class DatalogProgram {
private:
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Predicate> queries;
    std::vector<Rule> rules;
    std::set<std::string> domain;
    
public:
    DatalogProgram(std::vector<Predicate> schemes, std::vector<Predicate> facts, std::vector<Predicate> queries, std::vector<Rule> rules, std::set<std::string> domain) :
        schemes(schemes), facts(facts), queries(queries), rules(rules), domain(domain) {}
    
    std::vector<Predicate> getSchemes() const {
        return this -> schemes;
    }
    
    std::vector<Predicate> getFacts() const {
        return this -> facts;
    }
    
    std::vector<Predicate> getQueries() const {
        return this -> queries;
    }
    
    std::vector<Rule> getRules() const {
        return this -> rules;
    }
    
    std::string toString() {
        std::ostringstream out;
        out << "Schemes(" << schemes.size() << "):" << std::endl;
        for (size_t i = 0; i < schemes.size(); ++i)
            out << "  " << schemes.at(i).toString() << std::endl;
        
        out << "Facts(" << facts.size() << "):" << std::endl;
        for (size_t i = 0; i < facts.size(); ++i)
            out << "  " << facts.at(i).toString() << "." << std::endl;
        
        out << "Rules(" << rules.size() << "):" << std::endl;
        for (size_t i = 0; i < rules.size(); ++i)
            out << "  " << rules.at(i).toString() << std::endl;
        
        out << "Queries(" << queries.size() << "):" << std::endl;
        for (size_t i = 0; i < queries.size(); ++i)
            out << "  " << queries.at(i).toString() << "?" << std::endl;
        
        out << "Domain(" << domain.size() << "):" << std::endl;
        std::set<std::string>::iterator it;
        for (it = domain.begin(); it != domain.end(); it++)
            out << "  " << *it << std::endl;
        
        return out.str();
    }
};

#endif /* DatalogProgram_h */

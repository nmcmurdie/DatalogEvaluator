//
//  Interpreter.h
//  Project 3 - Interpreter
//
//  Created by Nicholas McMurdie on 11/1/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef Interpreter_h
#define Interpreter_h

#include "Database.h"
#include "DatalogProgram.h"
#include "Graph.h"
#include <stack>
#include <vector>
#include <map>

class Interpreter {
private:
    DatalogProgram program;
    Database database;
    
    void evaluateFacts() {
        std::vector<Predicate> schemes = program.getSchemes(), facts = program.getFacts();
        
        for (Predicate p : schemes) {
            Relation* r = new Relation(p.getID(), Header(p.getParams()));
            
            for (Predicate f : facts) {
                std::string name = f.getID();
                if (p.getID() == f.getID()) r -> addTuple(Tuple(f.getParams()));
            }
            
            database.addRelation(r);
        }
    }
    
    bool evaluateRule(Rule r) {
        Predicate head = r.headPredicate();
        std::vector<Predicate> bodyPredicates = r.bodyPredicates();
        
        Relation* body = evaluatePredicate(bodyPredicates.at(0));
        bodyPredicates.erase(bodyPredicates.begin());
        
        while (bodyPredicates.size() > 0) {
            Relation* r = evaluatePredicate(bodyPredicates.at(0));
            body = body -> join(r);
            bodyPredicates.erase(bodyPredicates.begin());
        }
        
        std::vector<Parameter> headParams = head.getParams();
        std::vector<std::string> bodyParams = body -> getHeader().getContents();
        std::vector<int> indices;
        
        for (size_t i = 0; i < headParams.size(); ++i) {
            for (int j = 0; j < (int) bodyParams.size(); ++j) {
                if (headParams.at(i).toString() == bodyParams.at(j)) {
                    indices.push_back(j);
                    break;
                }
            }
        }
        body = body -> project(indices);
        
        std::pair<Relation*, Relation*> result = database.getRelation(head.getID()) -> combine(body);
        
        std::cout << r.toString() << std::endl << result.second -> toString();
        
        database.setRelation(head.getID(), result.first);
        return !result.second -> isEmpty();
    }
    
    void createGraphs(std::vector<Rule>& rules, Graph& forward, Graph& reverse, std::vector<std::set<int>>& components) {
        std::vector<int> postOrder;
        
        for (int r = 0; r < (int)rules.size(); ++r) {
            std::string ID = rules.at(r).headPredicate().getID();
            
            for (Predicate b : rules.at(r).bodyPredicates()) {
                std::string bodyID = b.getID();
                for (int d = 0; d < (int)rules.size(); ++d) {
                    if (rules.at(d).headPredicate().getID() == bodyID) {
                        forward.addEdge(r, d);
                        reverse.addEdge(d, r);
                    }
                }
            }
        }
        
        std::stack<int> postStack = reverse.postOrder();
        for(; !postStack.empty(); postStack.pop()) postOrder.push_back(postStack.top());
        components = forward.SCC(postOrder);
    }
    
    void evaluateRules() {
        std::vector<Rule> rules = program.getRules();
        std::vector<std::set<int>> components;
        
        Graph forward((int)rules.size());
        Graph reverse((int)rules.size());
        
        createGraphs(rules, forward, reverse, components);
        
        std::cout << "Dependency Graph" << std::endl << forward.toString() << std::endl;
        
        std::cout << "Rule Evaluation" << std::endl;
        
        for (std::set<int> s : components) {
            std::ostringstream sccName;
            int numPasses = 0, firstRule;
            
            std::cout << "SCC: ";
            std::set<int>::iterator itr = s.begin();
            firstRule = *itr;
            
            sccName << "R" << *itr++;
            for (; itr != s.end(); itr++) sccName << ",R" << *itr;
            
            std::cout << sccName.str();
            std::cout << std::endl;
            
            if (s.size() == 1 && forward.isTrivial(firstRule)) {
                numPasses = 1;
                evaluateRule(rules.at(firstRule));
            }
            else {
                for (bool tuplesAdded = true; tuplesAdded;) {
                    tuplesAdded = false;
                    for (int r : s) {
                        tuplesAdded = evaluateRule(rules.at(r)) ? true : tuplesAdded;
                    }
                    ++numPasses;
                }
            }
            
            std::cout << numPasses << " passes: " << sccName.str() << std::endl;
        }
    }
    
    void evaluateQueries() {
        std::vector<Predicate> queries = program.getQueries();
        
        std::cout << std::endl << "Query Evaluation" << std::endl;
        for (Predicate q : queries) {
            Relation* r = evaluatePredicate(q);
            std::cout << q.toString() << "?";
            
            if (r -> size() > 0) {
                std::cout << " Yes(" << r -> size() << ")" << std::endl;
                std::cout << r -> toString();
            }
            else std::cout << " No" << std::endl;
        }
    }
    
    Relation* evaluatePredicate(Predicate p) {
        Relation* r = database.getRelation(p.getID());
        std::map<std::string, int> vars;
        std::vector<std::string> varOrder;
        std::vector<int> proj;
        
        for (size_t i = 0; i < p.getParams().size(); ++i) {
            Parameter param = p.getParams().at(i);
            if (param.isConstant()) {
                r = r -> select((int) i, param.toString());
            }
            else if (vars.find(param.toString()) == vars.end()) {
                vars.insert({param.toString(), i});
                varOrder.push_back(param.toString());
            }
            else {
                int index = vars.find(param.toString()) -> second;
                r = r -> select((int) i, index);
            }
        }
        
        for (size_t i = 0; i < varOrder.size(); ++i)
            proj.push_back(vars.find(varOrder.at(i)) -> second);
        
        r = r -> project(proj) -> rename(varOrder);
        
        return r;
    }
    
public:
    Interpreter(DatalogProgram prgm) : program(prgm) {
        evaluateFacts();
        evaluateRules();
        evaluateQueries();
    }
};

#endif /* Interpreter_h */

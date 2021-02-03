//
//  Parser.h
//  Project 2 - Parser
//
//  Created by Nicholas McMurdie on 10/4/20.
//  Copyright © 2020 Nicholas McMurdie. All rights reserved.
//

#ifndef Parser_h
#define Parser_h

#include <vector>
#include <set>
#include <iostream>
#include "DatalogProgram.h"

class Parser {
private:
    std::vector<Token*> tokens;
    std::set<std::string> domain;
    std::vector<Predicate> schemes, facts, queries;
    std::vector<Rule> rules;
    std::vector<Token*>::iterator it;
    
    Token* match(TType type) {
        if ((*it) -> getType() == TokenType(type)) {
            Token* output = *it;
            advance(it, 1);
            return output;
        }
        else throw *it;
    }
    
    void parseDatalog() {
        match(SCHEMES);
        match(COLON);
        
        schemes.push_back(parseScheme());
        parseSchemeList(schemes);
        
        match(FACTS);
        match(COLON);
        
        parseFactList(facts);
        
        match(RULES);
        match(COLON);
        
        parseRuleList(rules);
        
        match(QUERIES);
        match(COLON);
        
        queries.push_back(parseQuery());
        parseQueryList(queries);
        
        match(FILE_END);
    }
    
    void parseSchemeList(std::vector<Predicate>& schemes) {
        if ((*it) -> getType() == TokenType(ID)) {
            schemes.push_back(parseScheme());
            parseSchemeList(schemes);
        }
    }
    
    void parseRuleList(std::vector<Rule>& list) {
        if ((*it) -> getType() == TokenType(ID)) {
            list.push_back(parseRule());
            parseRuleList(list);
        }
    }
    
    void parseFactList(std::vector<Predicate>& list) {
        if ((*it) -> getType() == TokenType(ID)) {
            list.push_back(parseFact());
            parseFactList(list);
        }
    }
    
    void parseQueryList(std::vector<Predicate>& list) {
        if ((*it) -> getType() == TokenType(ID)) {
            list.push_back(parseQuery());
            parseQueryList(list);
        }
    }
    
    Predicate parseScheme() {
        Token* schemeID;
        std::vector<Parameter> params;
        
        schemeID = match(ID);
        match(LEFT_PAREN);
        params.push_back(Parameter(match(ID)));
        parseIDList(params);
        match(RIGHT_PAREN);
        
        return Predicate(schemeID, params);
    }
    
    Predicate parseFact() {
        Token* factID = match(ID);
        std::vector<Parameter> params;
        
        match(LEFT_PAREN);
        Token* firstParam = match(STRING);
        params.push_back(Parameter(firstParam));
        domain.insert(firstParam -> getContent());
        
        parseStringList(params);
        
        match(RIGHT_PAREN);
        match(PERIOD);
        
        return Predicate(factID, params);
    }
    
    Rule parseRule() {
        std::vector<Predicate> body;
        Predicate head = parseHeadPredicate();
        
        match(COLON_DASH);
        body.push_back(parsePredicate());
        parsePredicateList(body);
        match(PERIOD);
        
        return Rule(head, body);
    }
    
    Predicate parseQuery() {
        Predicate output = parsePredicate();
        match(Q_MARK);
        
        return output;
    }
    
    Predicate parseHeadPredicate() {
        Token* predicateID = match(ID);
        std::vector<Parameter> params;
        
        match(LEFT_PAREN);
        params.push_back(match(ID));
        parseIDList(params);
        match(RIGHT_PAREN);
        
        return Predicate(predicateID, params);
    }
    
    Predicate parsePredicate() {
        Token* predicateID = match(ID);
        std::vector<Parameter> params;
        std::vector<Token*> tokens;
        
        match(LEFT_PAREN);
        params.push_back(parseParameter(tokens));
        parseParameterList(params, tokens);
        match(RIGHT_PAREN);
        
        return Predicate(predicateID, params);
    }
    
    void parsePredicateList(std::vector<Predicate>& list) {
        if ((*it) -> getType() == TokenType(COMMA)) {
            match(COMMA);
            list.push_back(parsePredicate());
            parsePredicateList(list);
        }
    }
    
    void parseParameterList(std::vector<Parameter>& list, std::vector<Token*>& tokens) {
        if ((*it) -> getType() == TokenType(COMMA)) {
            match(COMMA);
            list.push_back(parseParameter(tokens));
            parseParameterList(list, tokens);
        }
    }
    
    void parseStringList(std::vector<Parameter>& list) {
        if ((*it) -> getType() == TokenType(COMMA)) {
            match(COMMA);
            Token* str = match(STRING);
            list.push_back(Parameter(str));
            domain.insert(str -> getContent());
            parseStringList(list);
        }
    }
    
    void parseIDList(std::vector<Parameter>& list) {
        if ((*it) -> getType() == TokenType(COMMA)) {
            match(COMMA);
            list.push_back(Parameter(match(ID)));
            parseIDList(list);
        }
    }
    
    Parameter parseParameter(std::vector<Token*>& tokens, bool inExpr = false) {
        TokenType type = (*it) -> getType();
        
        if (!inExpr && type == TokenType(STRING)) return Parameter(match(STRING));
        else if (!inExpr && type == TokenType(ID)) return Parameter(match(ID));
        else if (inExpr && type == TokenType(STRING)) {
            Token* str = match(STRING);
            tokens.push_back(str);
            return Parameter(str);
        }
        else if (inExpr && type == TokenType(ID)) {
            Token* id = match(ID);
            tokens.push_back(id);
            return Parameter(id);
        }
        else if (type == TokenType(LEFT_PAREN)) {
            parseExpression(tokens);
            return Parameter(tokens);
        }
        else throw *it;
    }
    
    void parseExpression(std::vector<Token*>& list) {
        list.push_back(match(LEFT_PAREN));
        parseParameter(list, true);
        list.push_back(parseOperator());
        parseParameter(list, true);
        list.push_back(match(RIGHT_PAREN));
    }
    
    Token* parseOperator() {
        TokenType type = (*it) -> getType();
        if (type == TokenType(ADD)) return match(ADD);
        else if (type == TokenType(MULTIPLY)) return match(MULTIPLY);
        else throw *it;
    }
    
public:
    Parser(std::vector<Token*> tokens) : tokens(tokens), it(tokens.begin()) {
        try {
            parseDatalog();
        } catch (Token* err) {
            std::cout << "Failure!" << std::endl << "  " << err -> toString() << std::endl;
        }
    }
    
    DatalogProgram getDatalog() const {
        return DatalogProgram(schemes, facts, queries, rules, domain);
    }
};

#endif /* Parser_h */

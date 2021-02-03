//
//  Graph.h
//  Project 5 - Rule Optimization
//
//  Created by Nicholas McMurdie on 12/6/20.
//

#ifndef Graph_h
#define Graph_h
#include <map>
#include <vector>
#include <sstream>
#include <stack>
#include <vector>

class Graph {
private:
    std::map<int, std::set<int>> edges;
    std::map<int, bool> visited;
    std::stack<int> post;
    int size;
    
    void postRecurse(int n) {
        int nextNode = -1;
        std::set<int> adj = edges[n];
        visited[n] = true;
        
        for (int i : adj) {
            if (!visited[i]) {
                nextNode = i;
                postRecurse(i);
            }
        }
        if (nextNode == -1) return post.push(n);
        post.push(n);
    }
    
    std::set<int>& sccRecurse(std::vector<int>& order, std::set<int>& comp, int n) {
        for (size_t i = 0; i < order.size(); ++i) {
            if (order.at(i) == n) {
                order.erase(order.begin() + i);
                break;
            }
        }
        comp.insert(n);
        visited[n] = true;
        if (!order.empty()) {
            int nextNode = -1;
            std::set<int> adj = edges[n];
            
            for (int i : adj) {
                if (!visited[i]) {
                    nextNode = i;
                    sccRecurse(order, comp, i);
                }
            }
            if (nextNode == -1) return comp;
        }
        return comp;
    }
    
public:
    Graph(int size) : size(size) {
        for (int i = 0; i < size; ++i) edges[i].clear();
    }
    
    void addEdge(int node, int dest) {
        edges[node].insert(dest);
    }
    
    std::set<int>& getNode(int node) {
        return edges[node];
    }
    
    std::stack<int> postOrder() {
        for (int i = 0; i < size; ++i) {
            if (!visited[i]) postRecurse(i);
        }
        return this -> post;
    }
    
    std::vector<std::set<int>> SCC(std::vector<int> order) {
        std::vector<std::set<int>> components;
        
        while (!order.empty()) {
            std::set<int> component;
            components.push_back(sccRecurse(order, component, order.at(0)));
        }
        
        return components;
    }
    
    bool isTrivial(int r) {
        std::set<int> firstConnect = edges[r];
        for (int i : firstConnect) {
            if (i == r) return false;
        }
        return firstConnect.size() <= 1 && firstConnect.empty() ? true : *firstConnect.begin() != r;
    }
    
    std::string toString() const {
        std::ostringstream out;
        
        for (const auto& p : edges) {
            out << "R" << p.first << ":";
            if (!p.second.empty()) {
                std::set<int>::iterator it = p.second.begin();
                out << "R" << *it++;
                for (;it != p.second.end(); it++) {
                    out << ",R" << *it;
                }
            }
            out << std::endl;
        }
        return out.str();
    }
};

#endif /* Graph_h */

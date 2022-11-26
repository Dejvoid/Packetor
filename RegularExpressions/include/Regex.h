#ifndef REGEX_H_
#define REGEX_H_

#include <set>
#include <string>
#include "Node.h"

class Regex {
    private:
        Node* root_;
        std::set<LiteralNode*> starting_;
        std::set<LiteralNode*> ending_;
        std::set<LiteralNode*> neighbors_;
    public: 
        Regex(const std::string& expr);
        std::string print_starting();
        std::string print_ending();
        std::string print_neighbors();
        std::string print_info();
        std::string print_epsilon();
};

#endif
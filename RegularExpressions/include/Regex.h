#ifndef REGEX_H_
#define REGEX_H_

#include <set>
#include <string>
#include <iostream>
#include "Node.h"

class Regex {
    private:
        Node* root_;
        std::set<LiteralNode*> starting_;
        std::set<LiteralNode*> ending_;
        std::set<Neighbor*> neighbors_;
        bool epsilon_;
        void get_neighbors();
        void get_ending();
        void get_starting();
    public: 
        Regex(const std::string& expr);
        void init_neighbor_method();
        void print_starting(std::ostream& os = std::cout);
        void print_ending(std::ostream& os = std::cout);
        void print_neighbors(std::ostream& os = std::cout);
        void print_epsilon(std::ostream& os = std::cout);
        void print_info(std::ostream& os = std::cout);
};

#endif
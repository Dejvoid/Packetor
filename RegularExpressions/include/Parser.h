#ifndef PARSER_H_
#define PARSER_H_ 

#include "Node.h"
#include <string>
#include <stack>

class Parser{
    private:
        inline static bool is_literal(unsigned char val);
        inline static bool is_binary_operator(char val);
        inline static bool is_unary_operator(char val);
        inline static Node* pop_operand(std::stack<Node*>& operands);
        inline static char pop_operator(std::stack<char>& operators);
        static Node* process_binary_op(std::stack<Node*>& operands, char op);
        static Node* process_unary_op(std::stack<Node*>& operands, char op);
        inline static bool is_lower_equal_precedence(char l, char r);
    public:
        static Node* parse_from_str(const std::string& expr);
};

#endif
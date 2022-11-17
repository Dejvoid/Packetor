#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <iostream>

enum class Type {
    NUMBER, OPERATION
};

constexpr char ADD_OPERATOR = '+';
constexpr char SUB_OPERATOR = '-';
constexpr char MUL_OPERATOR = '*';
constexpr char DIV_OPERATOR = '/';

class Node { 
    public:
        virtual void print_node_infix(std::ostream& os) const = 0;
        virtual void print_node_postfix(std::ostream& os) const = 0;
        virtual Type get_type() const = 0;
        virtual ~Node();
};

class NumberNode final : public Node {
    private:
        int value_; 
    public: 
        NumberNode(int value);
        Type get_type() const override;
        void print_node_infix(std::ostream& os) const override;
        void print_node_postfix(std::ostream& os) const override;
};

class OperationNode : public Node {
    protected:
        Node* left_;
        Node* right_;
        virtual char get_operator() const = 0;
    public:
        OperationNode(Node* left, Node* right);
        ~OperationNode();
        Type get_type() const override;
        void print_node_infix(std::ostream& os) const override;
        void print_node_postfix(std::ostream& os) const override;
};

class AdditionNode final : public OperationNode {
    public: 
        using OperationNode::OperationNode;
        char get_operator() const override;
};

class SubtractionNode final : public OperationNode{
    public: 
        using OperationNode::OperationNode;
        char get_operator() const override;
};

class MultiplicationNode final : public OperationNode {
    public:
        using OperationNode::OperationNode;public: 
        char get_operator() const override;
};

class DivisionNode final : public OperationNode {
    public:
        using OperationNode::OperationNode;
        char get_operator() const override;
};

class Expression{
    private:
        Node* root_;
    public:
        Expression(Node* root);
        ~Expression();
        void print_postfix(std::ostream& os = std::cout) const;
        void print_infix(std::ostream& os = std::cout) const;
};

#endif
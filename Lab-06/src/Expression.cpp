#include "Expression.h"

Node::~Node(){}

// Number Node
NumberNode::NumberNode(int value){
    value_ = value;
}
Type NumberNode::get_type() const{
    return Type::NUMBER;
}

// Operation Node
OperationNode::OperationNode(Node* left, Node* right){
    left_ = left;
    right_ = right;
}

OperationNode::~OperationNode(){
    if (left_ != nullptr){
        delete left_;
        left_ = nullptr;
    }
    if (right_ != nullptr){
        delete right_;
        right_ = nullptr;
    }
}

Type OperationNode::get_type() const{
    return Type::OPERATION;
}

char AdditionNode::get_operator() const {
    return ADD_OPERATOR;
}

char SubtractionNode::get_operator() const {
    return SUB_OPERATOR;
}

char DivisionNode::get_operator() const {
    return DIV_OPERATOR;
}

char MultiplicationNode::get_operator() const {
    return MUL_OPERATOR;
}

Expression::Expression(Node* root){
    root_ = root;
}

Expression::~Expression(){
    if (root_ != nullptr){
        delete root_;
        root_ = nullptr;
    }
}
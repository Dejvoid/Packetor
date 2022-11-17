#include "Expression.h"

Node::~Node(){}

// Number Node
NumberNode::NumberNode(int value){
    value_ = value;
}

Type NumberNode::get_type() const{
    return Type::NUMBER;
}

void NumberNode::print_node_infix(std::ostream& os) const {
    os << value_;
}

void NumberNode::print_node_postfix(std::ostream& os) const {
    os << value_ << " ";
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

void OperationNode::print_node_infix(std::ostream& os) const { // TODO: ADD PRIORITIES AND ZAVORKY :-)
    left_->print_node_infix(os);
    os << " " <<get_operator() << " ";
    right_->print_node_infix(os);
}

void OperationNode::print_node_postfix(std::ostream& os) const {
    left_->print_node_postfix(os);
    right_->print_node_postfix(os);
    os << get_operator() << " ";
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

void Expression::print_postfix(std::ostream& os) const {
    root_->print_node_postfix(os);
    os << std::endl;
}

void Expression::print_infix(std::ostream& os) const {
    root_->print_node_infix(os);
    os << std::endl;
}

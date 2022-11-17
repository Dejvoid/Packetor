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

int NumberNode::evaluate() const{
    return value_;
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
    bool parentheses = false;
    if (left_->get_type() == Type::OPERATION){
        auto l = (OperationNode*)left_;
        parentheses = is_lower_priority(l->get_operator());
    }
    if (parentheses)
        os << LEFT_PARENTHESIS;
    left_->print_node_infix(os);
    if (parentheses)
        os << RIGHT_PARENTHESIS;
    os << get_operator();
    parentheses = false;
    if (right_->get_type() == Type::OPERATION){
        auto r = (OperationNode*)right_;
        parentheses = is_lower_priority(r->get_operator());
    }
    if (parentheses)
        os << LEFT_PARENTHESIS;
    right_->print_node_infix(os);
    if (parentheses)
        os << RIGHT_PARENTHESIS;
}

void OperationNode::print_node_postfix(std::ostream& os) const {
    left_->print_node_postfix(os);
    right_->print_node_postfix(os);
    os << get_operator() << " ";
}

bool OperationNode::is_lower_priority(const char op) const {
    switch (op)
    {
    case ADD_OPERATOR:
    case SUB_OPERATOR:
        return get_operator() == DIV_OPERATOR || get_operator() == MUL_OPERATOR;
    break;
    default: return false;
    }
}

// Addition
char AdditionNode::get_operator() const {
    return ADD_OPERATOR;
}

int AdditionNode::evaluate() const {
    return left_->evaluate() + right_->evaluate();
}

// Subtraction
char SubtractionNode::get_operator() const {
    return SUB_OPERATOR;
}

int SubtractionNode::evaluate() const {
    return left_->evaluate() - right_->evaluate();
}

// Division
char DivisionNode::get_operator() const {
    return DIV_OPERATOR;
}

int DivisionNode::evaluate() const {
    return left_->evaluate() / right_->evaluate();
}

// Multiplication
char MultiplicationNode::get_operator() const {
    return MUL_OPERATOR;
}

int MultiplicationNode::evaluate() const {
    return left_->evaluate() * right_->evaluate();
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
}

void Expression::print_infix(std::ostream& os) const {
    root_->print_node_infix(os);
}

int Expression::evaluate() const {
    return root_->evaluate();
}

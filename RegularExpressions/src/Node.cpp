#include "Node.h"

Node::~Node(){};

bool operator<(const LiteralNode& n1, const LiteralNode& n2){
    return n1.index() < n2.index();
}

LiteralNode::LiteralNode(char value, int index){
    value_ = value;
    index_ = index;
};

BinaryOperatorNode::BinaryOperatorNode(Node* left, Node* right){
    left_ = left;
    right_ = right;
};

BinaryOperatorNode::~BinaryOperatorNode(){
    if (left_ != nullptr){
        delete left_;
        left_ = nullptr;
    }
    if (right_ != nullptr){
        delete right_;
        right_ = nullptr;
    }
}

UnaryOperatorNode::UnaryOperatorNode(Node* operand){
    operand_ = operand;
}

UnaryOperatorNode::~UnaryOperatorNode(){
    if (operand_ != nullptr){
        delete operand_;
        operand_ = nullptr;
    }
}


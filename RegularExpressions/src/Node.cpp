#include "Node.h"

Node::~Node(){};

bool operator<(const LiteralNode& n1, const LiteralNode& n2){
    return n1.index() < n2.index();
};

bool operator<(const Neighbor& n1, const Neighbor& n2){
    return n1.left->index() < n2.left->index() ||
        (n1.left->index() == n2.left->index() && n1.right->index() < n2.right->index());
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
};

UnaryOperatorNode::UnaryOperatorNode(Node* operand){
    operand_ = operand;
};

UnaryOperatorNode::~UnaryOperatorNode(){
    if (operand_ != nullptr){
        delete operand_;
        operand_ = nullptr;
    }
};

void LiteralNode::add_starting(std::set<LiteralNode*>& parent_s){
    parent_s.insert(this);
};
void LiteralNode::add_neighbors(std::set<Neighbor*>& parent_n){
    return;
};
void LiteralNode::add_ending(std::set<LiteralNode*>& parent_e){
    parent_e.insert(this);
};
bool LiteralNode::epsilon(){
    return false;
};

void ConcatNode::add_starting(std::set<LiteralNode*>& parent_s){
    if (this->left_->epsilon()){
        this->left_->add_starting(parent_s);
        this->right_->add_starting(parent_s);
    }
    else
        this->left_->add_starting(parent_s);
};
void ConcatNode::add_neighbors(std::set<Neighbor*>& parent_n){
    this->left_->add_neighbors(parent_n);
    this->right_->add_neighbors(parent_n);
    std::set<LiteralNode*> starting;
    std::set<LiteralNode*> ending;
    left_->add_ending(ending);
    right_->add_starting(starting);
    for (auto ite = ending.begin(); ite !=ending.end(); ++ite){
        for (auto its = starting.begin(); its != starting.end(); ++its){
            Neighbor* n = new Neighbor;
            n->left = *ite;
            n->right = *its;
            parent_n.insert(n);
        }
    }
    //this->left_->ending(), this->right_->starting();
};
void ConcatNode::add_ending(std::set<LiteralNode*>& parent_e){
    if (this->right_->epsilon()){
        this->left_->add_ending(parent_e);
        this->right_->add_ending(parent_e);
    }
    else 
        this->right_->add_ending(parent_e);
};
bool ConcatNode::epsilon(){
    return this->left_->epsilon() && this->right_->epsilon();
};

void AlterNode::add_starting(std::set<LiteralNode*>& parent_s){
    this->left_->add_starting(parent_s);
    this->right_->add_starting(parent_s);
};
void AlterNode::add_neighbors(std::set<Neighbor*>& parent_n){
    this->left_->add_neighbors(parent_n);
    this->right_->add_neighbors(parent_n);
};
void AlterNode::add_ending(std::set<LiteralNode*>& parent_e){
    this->left_->add_ending(parent_e);
    this->right_->add_ending(parent_e);
};
bool AlterNode::epsilon(){
    return this->left_->epsilon() || this->right_->epsilon();
};

void IterNode::add_starting(std::set<LiteralNode*>& parent_s){
    operand_->add_starting(parent_s);
};
void IterNode::add_neighbors(std::set<Neighbor*>& parent_n){
    operand_->add_neighbors(parent_n);
    std::set<LiteralNode*> starting;
    std::set<LiteralNode*> ending;
    operand_->add_ending(ending);
    operand_->add_starting(starting);
    for (auto ite = ending.begin(); ite !=ending.end(); ++ite){
        for (auto its = starting.begin(); its != starting.end(); ++its){
            Neighbor* n = new Neighbor;
            n->left = *ite;
            n->right = *its;
            parent_n.insert(n);
        }
    }
    //this->operand_->ending(),this->operand_->starting();
};
void IterNode::add_ending(std::set<LiteralNode*>& parent_e){
    operand_->add_ending(parent_e);
};
bool IterNode::epsilon(){
    return true;
};
#ifndef NODE_H_
#define NODE_H_

#include "Constants.h"
#include <set>

enum class NodeType{
    UNARY_OPERATOR,
    BINARY_OPERATOR,
    LITERAL,
    EPSILON,
    EMPTY_SET
};

class Node;
class LiteralNode;
struct NeighborCmp;
struct LiteralCmp;

struct Neighbor{
    LiteralNode* left;
    LiteralNode* right;
};



class Node{
    public:
        virtual ~Node();
        inline virtual NodeType get_type() const = 0;
        virtual void add_neighbors(std::set<Neighbor*,NeighborCmp>& parent_n)=0;
        virtual void add_starting(std::set<LiteralNode*, LiteralCmp>& parent_n)=0;
        virtual void add_ending(std::set<LiteralNode*, LiteralCmp>& parent_n)=0;
        virtual bool epsilon()=0;
};

class EpsilonNode final : public Node{
    inline virtual NodeType get_type() const {return NodeType::EPSILON; };
    void add_neighbors(std::set<Neighbor*,NeighborCmp>& parent_n) override;
    void add_starting(std::set<LiteralNode*, LiteralCmp>& parent_n) override;
    void add_ending(std::set<LiteralNode*, LiteralCmp>& parent_n) override;
    bool epsilon() override;
};

class EmptySetNode final : public Node{
        inline NodeType get_type() const {return NodeType::EMPTY_SET;};
        void add_neighbors(std::set<Neighbor*,NeighborCmp>& parent_n) override;
        void add_starting(std::set<LiteralNode*, LiteralCmp>& parent_n) override;
        void add_ending(std::set<LiteralNode*, LiteralCmp>& parent_n) override;
        bool epsilon() override;
};
class LiteralNode final : public Node{
    private:
        char value_; // literal itself
        int index_;  // index in expression
    public:
        LiteralNode(char value, int index);
        inline NodeType get_type() const override { return NodeType::LITERAL; };
        inline char value() const {return value_;};
        inline int index() const {return index_;};
        void add_neighbors(std::set<Neighbor*,NeighborCmp>& parent_n) override;
        void add_starting(std::set<LiteralNode*, LiteralCmp>& parent_s) override;
        void add_ending(std::set<LiteralNode*, LiteralCmp>& parent_e) override;
        bool epsilon() override;
};
class BinaryOperatorNode : public Node{
    protected:
        Node *left_;  // left operand
        Node *right_; // right operand
    public:
        BinaryOperatorNode(Node *left, Node *right);
        ~BinaryOperatorNode();
        inline NodeType get_type() const override { return NodeType::BINARY_OPERATOR; };
        inline virtual char get_operator() const = 0;
};

class UnaryOperatorNode : public Node{
    protected:
        Node *operand_; // operand
    public:
        UnaryOperatorNode(Node *operand);
        ~UnaryOperatorNode();
        NodeType get_type() const override { return NodeType::UNARY_OPERATOR; };
        inline virtual char get_operator() const = 0;
};

class ConcatNode final : public BinaryOperatorNode{
    public:
        using BinaryOperatorNode::BinaryOperatorNode;
        inline char get_operator() const override { return CONCAT_OP; };
        void add_neighbors(std::set<Neighbor*,NeighborCmp>& parent_n) override;
        void add_starting(std::set<LiteralNode*, LiteralCmp>& parent_s) override;
        void add_ending(std::set<LiteralNode*, LiteralCmp>& parent_e) override;
        bool epsilon() override;
};

class AlterNode final : public BinaryOperatorNode{
    public:
        using BinaryOperatorNode::BinaryOperatorNode;
        inline char get_operator() const override { return ALTER_OP; };
        void add_neighbors(std::set<Neighbor*,NeighborCmp>& parent_n) override;
        void add_starting(std::set<LiteralNode*, LiteralCmp>& parent_s) override;
        void add_ending(std::set<LiteralNode*, LiteralCmp>& parent_e) override;
        bool epsilon() override;
};

class IterNode final : public UnaryOperatorNode{
    public:
        using UnaryOperatorNode::UnaryOperatorNode;
        inline char get_operator() const override { return ITER_OP; };
        void add_neighbors(std::set<Neighbor*,NeighborCmp>& parent_n) override;
        void add_starting(std::set<LiteralNode*, LiteralCmp>& parent_s) override;
        void add_ending(std::set<LiteralNode*, LiteralCmp>& parent_e) override;
        bool epsilon() override;
};



struct NeighborCmp
{
    bool operator()(const Neighbor* n1, const Neighbor* n2) const{
        return n1->left->index() < n2->left->index() ||
            (n1->left->index() == n2->left->index() && n1->right->index() < n2->right->index());
}
};

struct LiteralCmp
{
    bool operator()(const LiteralNode* n1, const LiteralNode* n2) const{
        return n1->index() < n2->index();
}
};

#endif
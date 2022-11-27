#ifndef NODE_H_
#define NODE_H_

#include "Constants.h"
#include <set>

enum class NodeType{
    UNARY_OPERATOR,
    BINARY_OPERATOR,
    LITERAL
};

class Node;
class LiteralNode;

struct Neighbor{
    LiteralNode* left;
    LiteralNode* right;
};

class Node{
    public:
        virtual ~Node();
        inline virtual NodeType get_type() const = 0;
        virtual void add_neighbors(std::set<Neighbor*>& parent_n)=0;
        virtual void add_starting(std::set<LiteralNode*>& parent_n)=0;
        virtual void add_ending(std::set<LiteralNode*>& parent_n)=0;
        virtual bool epsilon()=0;
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
        void add_neighbors(std::set<Neighbor*>& parent_n) override;
        void add_starting(std::set<LiteralNode*>& parent_s) override;
        void add_ending(std::set<LiteralNode*>& parent_e) override;
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
        void add_neighbors(std::set<Neighbor*>& parent_n) override;
        void add_starting(std::set<LiteralNode*>& parent_s) override;
        void add_ending(std::set<LiteralNode*>& parent_e) override;
        bool epsilon() override;
};

class AlterNode final : public BinaryOperatorNode{
    public:
        using BinaryOperatorNode::BinaryOperatorNode;
        inline char get_operator() const override { return ALTER_OP; };
        void add_neighbors(std::set<Neighbor*>& parent_n) override;
        void add_starting(std::set<LiteralNode*>& parent_s) override;
        void add_ending(std::set<LiteralNode*>& parent_e) override;
        bool epsilon() override;
};

class IterNode final : public UnaryOperatorNode{
    public:
        using UnaryOperatorNode::UnaryOperatorNode;
        inline char get_operator() const override { return ITER_OP; };
        void add_neighbors(std::set<Neighbor*>& parent_n) override;
        void add_starting(std::set<LiteralNode*>& parent_s) override;
        void add_ending(std::set<LiteralNode*>& parent_e) override;
        bool epsilon() override;
};

#endif
#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include "Array.h"
template <typename NData>
class Node;
template <typename NData, typename EData>
class Nodes;
#include "Edge.h"

template <typename NData>
class Node {
    private:
    size_t id_;
    NData data_;
    public:
    Node() = default;
    Node(size_t id, NData data);
    size_t getId() const;
    NData& getData();
};

template <typename NData, typename EData>
class Nodes {
    private:
    lib::Array<Node<NData>> nodes_;
    Edges<NData, EData>& edges_;
    public:
    void print(std::ostream& os = std::cout) const;
    Node<NData>& add(size_t id, NData data);
    Node<NData>& add(NData data);
    size_t size() const;
    bool exists(size_t id) const;
    Node<NData>& get(size_t id) const;
    Node<NData>& operator[](size_t id) const;
    typename lib::Array<Node<NData>>::iterator begin() const;
    typename lib::Array<Node<NData>>::iterator end() const;
};

template <typename NData>
std::ostream& operator<<(std::ostream& os, const Node<NData>& node) {
    os << "node (" << node.getId() << " {" << node.getData() << "})" << std::endl;
    return os;
};

template <typename NData, typename EData>
std::ostream& operator<<(std::ostream& os, const Nodes<NData, EData>& nodes) {
    nodes.print(os);
    return os;
};

#pragma region NodeMethods
template <typename NData>
Node<NData>::Node(size_t id, NData data) {
    id_ = id;
    data_ = data;
};
template <typename NData>
NData& Node<NData>::getData() {
    return data_;
};

template <typename NData>
size_t Node<NData>::getId() const {
    return id_;
};

#pragma endregion
#pragma region NodesMethods
template <typename NData, typename EData>
void Nodes<NData, EData>::print(std::ostream& os) const {
    for (auto it = nodes_.begin(); it != nodes_.end(); ++it) {
        os << *it;
    }
};
template <typename NData, typename EData>
Node<NData>& Nodes<NData, EData>::add(size_t id, NData data) {
    nodes_.push_back(Node<NData>(id, data));
    edges_.adjacency_matrix_.push_back(std::vector<Edge<NData, EData>*>(id + 1, nullptr));
    return nodes_[nodes_.size() - 1];
};
template <typename NData, typename EData>
Node<NData>& Nodes<NData, EData>::add(NData data) {
    size_t id = nodes_.size();
    return Nodes<NData, EData>::add(id, data);
};
template <typename NData, typename EData>
size_t Nodes<NData, EData>::size() const {
    return nodes_.size();
};
template <typename NData, typename EData>
bool Nodes<NData, EData>::exists(size_t id) const {
    return id < nodes_.size() && id >= 0;
};
template <typename NData, typename EData>
Node<NData>& Nodes<NData, EData>::get(size_t id) const {
    return nodes_[id];
};
template <typename NData, typename EData>
Node<NData>& Nodes<NData, EData>::operator[](size_t id) const {
    //return nodes_[id];
};
template <typename NData, typename EData>
typename lib::Array<Node<NData>>::iterator Nodes<NData, EData>::begin() const {
    return nodes_.begin();
};
template <typename NData, typename EData>
typename lib::Array<Node<NData>>::iterator Nodes<NData, EData>::end() const {
    return nodes_.end();
};
#pragma endregion
#endif
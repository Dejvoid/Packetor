#ifndef EDGE_H_
#define EDGE_H_

#include <iostream>
#include "Array.h"
template <typename NData, typename EData>
class Edge;
template <typename NData, typename EData>
class Edges;
#include "Node.h"

template <typename NData, typename EData>
class Edge {
    private:
    size_t id_;
    EData data_;
    Node<NData>& source_;
    Node<NData>& target_;
    public:
    Edge() = default;
    Edge(size_t id, Node<NData>& source, Node<NData>& target, EData data);
    inline size_t getId() const;
    inline EData& getData();
    inline Node<NData>& getSource() const;
    inline Node<NData>& getTarget() const;
};

template <typename NData, typename EData>
class Edges {
    private:
    Nodes<NData, EData>& nodes_;
    lib::Array<Edge<NData,EData>> edges_;
    std::vector<std::vector<Edge<NData,EData>*>> adjacency_matrix_;
    friend Node<NData>& Nodes<NData, EData>::add(size_t id, NData data);
    size_t get_id_from_matrix(size_t source, size_t target);
    public:
    Edges(Nodes<NData, EData>& nodes);
    void print(std::ostream& os = std::cout) const;
    void printMatrix(std::ostream& os = std::cout) const;
    Edge<NData, EData>& add(size_t id, size_t source, size_t target, EData data);
    Edge<NData, EData>& add(size_t source, size_t target, EData data);
    size_t size() const;
    bool exists(size_t id) const;
    bool exists(size_t source, size_t target) const;
    Edge<NData, EData>& get(size_t id) const;
    Edge<NData, EData>& get(size_t source, size_t target) const;
    typename lib::Array<Edge<NData, EData>>::iterator begin() const;
    typename lib::Array<Edge<NData, EData>>::iterator end() const;
};

template <typename NData, typename EData>
std::ostream& operator<<(std::ostream& os, const Edge<NData, EData>& edge) {
    os << "edge (" << edge.getSource().getId() << ")-[" << edge.getId() << " {" << edge.getData() << "}]->(" << edge.getTarget().getId() << ")" << std::endl;
    return os;
};

template <typename NData, typename EData>
std::ostream& operator<<(std::ostream& os, const Edges<NData, EData>& edges) {
    edges.print(os);
    return os;
};

#pragma region EdgeMethods
template <typename NData, typename EData>
Edge<NData, EData>::Edge(size_t id, Node<NData>& source, Node<NData>& target, EData data) {
    id_ = id;
    data_ = data;
    source_ = source;
    target_ = target;
};
template <typename NData, typename EData>
size_t Edge<NData,EData>::getId() const {
    return id_;
};
template <typename NData, typename EData>
EData& Edge<NData,EData>::getData() {
    return data_;
};
template <typename NData, typename EData>
Node<NData>& Edge<NData,EData>::getSource() const {
    return source_;
};
template <typename NData, typename EData>
Node<NData>& Edge<NData,EData>::getTarget() const {
    return target_;
};
#pragma endregion

#pragma region EdgesMethods
template <typename NData, typename EData>
size_t Edges<NData, EData>::get_id_from_matrix(size_t source, size_t target) {
    return adjacency_matrix_[source][target]->getId();
};
template <typename NData, typename EData>
Edges<NData, EData>::Edges(Nodes<NData, EData>& nodes) {
    nodes_ = nodes;
};
template <typename NData, typename EData>
void Edges<NData,EData>::print(std::ostream& os) const {
    for (auto it = edges_.begin(); it != edges_.end(); ++it) {
        os << *it;
    }
};
template <typename NData, typename EData>
void Edges<NData,EData>::printMatrix(std::ostream& os) const {
/*
-|0|1
0|-|-
1|-|-
*/
};
template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData,EData>::add(size_t id, size_t source, size_t target, EData data) {
    //Edge<NData, EData> edge(id,nodes_[source], nodes_[target], data);
    //edges_.push_back(edge);
    //return edges_[edges_.size() - 1];
};
template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData,EData>::add(size_t source, size_t target, EData data) {
    //return add(edges_.size(), source, target, data);
};
template <typename NData, typename EData>
size_t Edges<NData,EData>::size() const {
    return edges_.size();
};
template <typename NData, typename EData>
bool Edges<NData,EData>::exists(size_t id) const {
    return id < edges_.size() && id >= 0;
};
template <typename NData, typename EData>
bool Edges<NData,EData>::exists(size_t source, size_t target) const {
    size_t id = get_id_from_matrix(source, target);
    return id < edges_.size() && id >= 0;
};
template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData,EData>::get(size_t id) const {
    return edges_[id];
};
template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData,EData>::get(size_t source, size_t target) const {
    size_t id = get_id_from_matrix(source, target);
    return edges_[id];
};
#pragma endregion


#endif
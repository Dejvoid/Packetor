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
    Node<NData>* source_;
    Node<NData>* target_;
    public:
    //friend std::ostream& operator<<(std::ostream& os, const Edge<NData, EData>& edge);
    Edge() = default;
    Edge(size_t id, Node<NData>* source, Node<NData>* target, EData data);
    inline size_t getId() const;
    inline EData& getData();
    inline const EData& getData() const;
    inline Node<NData>& getSource() const;
    inline Node<NData>& getTarget() const;
};

template <typename NData, typename EData>
class Edges {
    private:
    lib::Array<Edge<NData,EData>> edges_;
    std::vector<std::vector<Edge<NData,EData>*>> adjacency_matrix_;
    friend Node<NData>& Nodes<NData, EData>::add(size_t id, NData data);
    Edge<NData, EData>* get_from_matrix(size_t source, size_t target);
    Nodes<NData, EData>* nodes_;
    public:
    Edges() = default;
    Edges(const Edges& other);
    Edges(Edges&& other) noexcept;
    ~Edges();
    Edges& operator=(const Edges& other);
    Edges& operator=(Edges&& other) noexcept;
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
std::ostream& operator<<(std::ostream& os, const Edges<NData, const EData>& edges) {
    edges.print(os);
    return os;
};

#pragma region EdgeMethods
template <typename NData, typename EData>
Edge<NData, EData>::Edge(size_t id, Node<NData>* source, Node<NData>* target, EData data) {
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
const EData& Edge<NData,EData>::getData() const {
    return data_;
};
template <typename NData, typename EData>
Node<NData>& Edge<NData,EData>::getSource() const {
    return (*source_);
};
template <typename NData, typename EData>
Node<NData>& Edge<NData,EData>::getTarget() const {
    return (*target_);
};
#pragma endregion

#pragma region EdgesMethods
template <typename NData, typename EData>
Edges<NData, EData>::Edges(const Edges& other) {

};
template <typename NData, typename EData>
Edges<NData, EData>::Edges(Edges&& other) noexcept {

};
template <typename NData, typename EData>
Edges<NData, EData>::~Edges() {

};
template <typename NData, typename EData>
Edges<NData, EData>& Edges<NData, EData>::operator=(const Edges& other) {

};
template <typename NData, typename EData>
Edges<NData, EData>& Edges<NData, EData>::operator=(Edges&& other) noexcept {

};

template <typename NData, typename EData>
Edge<NData,EData>* Edges<NData, EData>::get_from_matrix(size_t source, size_t target) {
    return adjacency_matrix_[source][target];
};
template <typename NData, typename EData>
void Edges<NData,EData>::print(std::ostream& os) const {
    for (auto it = edges_.begin(); it != edges_.end(); ++it) {
        const Edge<NData,EData>& e = *it;
        os << e;
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
    if (get_from_matrix() != nullptr)
        throw ConflictingItemException("Attempting to add a new edge between a pair of nodes with identifiers "+ std::string(source) +" and "+ std::string(target) +" which already are connected with another existing edge");
    if (source >= adjacency_matrix_.size() || target >= adjacency_matrix_.size())
        throw NonexistingItemException("Attempting to add a new edge between a nonexisting pair of nodes with identifiers $source and " + std::string(target)+", only "+ std::string(adjacency_matrix_.size()) +" nodes are available");
    if (exists(id))
        throw ConflictingItemException("Attempting to add a new edge with identifier "+ std::string(id) +" which already is associated with another existing edge");
    if (id != size())
        throw InvalidIdentifierException("Attempting to add a new edge with invalid identifier "+std::string(id)+", expected $size instead");
    Edge<NData, EData> edge(id, &(nodes_->get(source)) , &(nodes_->get(target)), data);
    try{
        edges_.push_back(edge);
    } catch (UnavailableMemoryException){
        throw UnavailableMemoryException("Unable to insert a new edge record into the underlying container of edges");
    }
    return edges_[edges_.size() - 1];
};
template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData,EData>::add(size_t source, size_t target, EData data) {
    size_t id = edges_.size();
    Edge<NData, EData> edge(id, &(nodes_->get(source)) , &(nodes_->get(target)), data);
    edges_.push_back(edge);
    return edges_[edges_.size() - 1];
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
    if (source >= adjacency_matrix_.size() || target >= adjacency_matrix_.size())
        throw NonexistingItemException("Attempting to test the existence of an edge between a nonexisting pair of nodes with identifiers "+std::string(source)+" and "+std::string(target)+", only "+std::string(adjacency_matrix_.size())+" nodes are available");
    size_t id = get_from_matrix(source, target)->getId();
    return id < edges_.size() && id >= 0;
};
template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData,EData>::get(size_t id) const {
    if (!exists(id)) 
        throw NonexistingItemException("Attempting to access a nonexisting edge with identifier "+std::string(id)+", only "+std::string(adjacency_matrix_.size())+" edges are available"); 
    return edges_[id];
};
template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData,EData>::get(size_t source, size_t target) const {
    if (adjacency_matrix_.size() <= source || adjacency_matrix_.size() <= target)
        throw NonexistingItemException("Attempting to access an edge between a nonexisting pair of nodes with identifiers "+std::string(source)+" and $target, only "+std::string(size)+" nodes are available"); 
    size_t id = get_from_matrix(source, target)->getId();
    return edges_[id];
};
#pragma endregion


#endif
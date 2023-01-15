/// @file Node.h
#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include "Array.h"
template <typename NData>
class Node;
template <typename NData, typename EData>
class Nodes;
#include "Edge.h"
/// @brief Graph node representation class. Allows user to store custom information to Node
/// @tparam NData 
template <typename NData>
class Node {
    private:
    /// @brief Identifier of the node
    size_t id_;
    /// @brief Node data
    NData data_;
    public:
    Node() = default;
    Node(size_t id, NData data);
    /// @brief 
    /// @return Identifier of the node
    size_t getId() const;
    /// @brief 
    /// @return Node data
    NData& getData();
    const NData& getData() const;
};
/// @brief Graph nodes list.
/// @tparam NData 
/// @tparam EData 
template <typename NData, typename EData>
class Nodes {
    private:
    /// @brief Nodes storage
    lib::Array<Node<NData>> nodes_;
    /// @brief Edge, used to fill adjacency matrix of the graph
    Edges<NData,EData>* edges_;
    public:
    Nodes() = default;
    /// @brief 
    /// @param edges ptr to edges of the graph
    Nodes(Edges<NData, EData>* edges) : edges_(edges){};
    /// @brief 
    /// @param other 
    Nodes(const Nodes& other);
    /// @brief 
    /// @param other 
    Nodes(Nodes&& other) noexcept;
    ~Nodes() = default;
    /// @brief 
    /// @param other 
    /// @return 
    Nodes& operator=(const Nodes& other);
    /// @brief 
    /// @param other 
    /// @return 
    Nodes& operator=(Nodes&& other) noexcept;
    /// @brief 
    /// @param os 
    void print(std::ostream& os = std::cout) const;
    /// @brief Adds new Node to the list
    /// @param id Node identifier
    /// @param data Node data
    /// @return Reference to created node
    Node<NData>& add(size_t id, NData data);
    /// @brief Adds new Node to the list with implicitly created identifier
    /// @param data Node data
    /// @return Reference to created node
    Node<NData>& add(NData data);
    /// @brief 
    /// @return Node count
    size_t size() const;
    /// @brief Tells if node id is present in the list
    /// @param id 
    /// @return true if exists
    bool exists(size_t id) const;
    /// @brief Gets reference to node from
    /// @param id 
    /// @return 
    Node<NData>& get(size_t id) const;
    /// @brief 
    /// @param id 
    /// @return 
    Node<NData>& operator[](size_t id) const;
    /// @brief 
    /// @return 
    typename lib::Array<Node<NData>>::iterator begin() const;
    /// @brief 
    /// @return 
    typename lib::Array<Node<NData>>::iterator end() const;
};
/// @brief 
/// @tparam NData 
/// @param os 
/// @param node 
/// @return 
template <typename NData>
std::ostream& operator<<(std::ostream& os, const Node<NData>& node) {
    os << "node (" << node.getId() << " {" << node.getData() << "})" << std::endl;
    return os;
};
/// @brief 
/// @tparam NData 
/// @tparam EData 
/// @param os 
/// @param nodes 
/// @return 
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
const NData& Node<NData>::getData() const {
    return data_;
};
template <typename NData>
size_t Node<NData>::getId() const {
    return id_;
};

#pragma endregion
#pragma region NodesMethods

template <typename NData, typename EData>
Nodes<NData, EData>::Nodes(const Nodes& other) {

};
template <typename NData, typename EData>
Nodes<NData, EData>::Nodes(Nodes&& other) noexcept {

};
template <typename NData, typename EData>
Nodes<NData,EData>& Nodes<NData, EData>::operator=(const Nodes& other) {
    this->nodes_.~Array();
    this->nodes_ = other.nodes_;
    return *this;
};
template <typename NData, typename EData>
Nodes<NData,EData>& Nodes<NData, EData>::operator=(Nodes&& other) noexcept {
    std::swap(this->nodes_, other.nodes_);
    return *this;
};

template <typename NData, typename EData>
void Nodes<NData, EData>::print(std::ostream& os) const {
    for (auto it = begin(); it != end(); ++it) {
        os << *it;
    }
};
template <typename NData, typename EData>
Node<NData>& Nodes<NData, EData>::add(size_t id, NData data) {
    if (exists(id))
        throw ConflictingItemException("Attempting to add a new node with identifier "+std::to_string(id)+" which already is associated with another existing node");
    if (id != size())
        throw InvalidIdentifierException("Attempting to add a new node with invalid identifier "+std::to_string(id)+", expected "+std::to_string(size())+" instead");
    try {
        nodes_.push_back(Node<NData>(id, data));
    } catch (UnavailableMemoryException){
        throw UnavailableMemoryException("Unable to insert a new node record into the underlying container of nodes");
    }
    try {
        for (auto it = edges_->adjacency_matrix_.begin(); it != edges_->adjacency_matrix_.end(); ++it){
            it->push_back((size_t)(-1));
        }
        edges_->adjacency_matrix_.push_back(std::vector<size_t>(id + 1, (size_t)(-1)));
    } catch (const std::bad_alloc&) {
        nodes_.pop_back();
        throw UnavailableMemoryException("Unable to extend the underlying adjacency matrix container for edges");
    }
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
    if (!exists(id))
        throw NonexistingItemException("Attempting to access a nonexisting node with identifier "+std::to_string(id)+", only "+std::to_string(size())+" nodes are available");
    return nodes_[id];
};
template <typename NData, typename EData>
Node<NData>& Nodes<NData, EData>::operator[](size_t id) const {
    if (!exists(id))
        throw NonexistingItemException("Attempting to access a nonexisting node with identifier "+std::to_string(id)+", only "+std::to_string(size())+" nodes are available");
    return nodes_[id];
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
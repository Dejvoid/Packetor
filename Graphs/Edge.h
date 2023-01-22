/// @file Edge.h
#ifndef EDGE_H_
#define EDGE_H_

#include <iostream>
#include "Array.h"

template <typename NData, typename EData>
class Edge;
template <typename NData, typename EData>
class Edges;
#include "Graph.h"

/// @brief Structure for storing graph edges
/// @tparam NData 
/// @tparam EData 
template <typename NData, typename EData>
class Edge {
    private:
    /// @brief Unique identifier of the edge
    size_t id_;
    /// @brief Data content of the edge, must support reading from stream
    EData data_;
    /// @brief Source node of the edge
    Node<NData>* source_;
    /// @brief Target node of the edge
    Node<NData>* target_;
    public:
    Edge() = default;
    /// @brief 
    /// @param id - Identifier for the edge
    /// @param source - Source node
    /// @param target - Target node
    /// @param data - Data of the edge
    Edge(size_t id, Node<NData>* source, Node<NData>* target, EData data);
    /// @brief 
    /// @return Identifier of the edge
    inline size_t getId() const;
    /// @brief 
    /// @return Data of the edge
    inline EData& getData();
    /// @brief 
    /// @return Data of the edge
    inline const EData& getData() const;
    /// @brief 
    /// @return Source node of the edge
    inline Node<NData>& getSource() const;
    /// @brief 
    /// @return Target node of the edge
    inline Node<NData>& getTarget() const;
};
/// @brief Structure for storing graph edges 
/// @tparam NData 
/// @tparam EData 
template <typename NData, typename EData>
class Edges {
    private:
    /// @brief Storage of edges
    lib::Array<Edge<NData,EData>> edges_;
    /// @brief Adjacency matrix of the graph for faster edge searching
    std::vector<std::vector<size_t>> adjacency_matrix_;
    friend Node<NData>& Nodes<NData, EData>::add(size_t id, NData data);
    friend class Graph<NData, EData>;
    friend class IncidentEdges;
    /// @brief Gets identifier of the edge based on its nodes
    /// @param source - source node of the edge
    /// @param target - target node of the edge
    /// @return Identifier of the edge
    size_t get_from_matrix(size_t source, size_t target) const;
    /// @brief Adds new node to adj. matrix
    void add_n_to_matrix();
    /// @brief adds new edge to adj. matrix
    /// @param edge 
    void add_e_to_matrix(Edge<NData, EData>& edge);
    /// @brief Pointer to graph owner of the edges
    const Graph<NData, EData>* graph_;
    public:
    Edges() = default;
    /// @brief 
    /// @param nodes 
    Edges(const Graph<NData, EData>* graph) : graph_(graph) {};
    Edges(const Edges& other);
    Edges(Edges&& other) noexcept;
    ~Edges() = default;
    Edges& operator=(const Edges& other);
    Edges& operator=(Edges&& other) noexcept;
    /// @brief Prints edges
    /// @param os 
    void print(std::ostream& os = std::cout) const;
    /// @brief Prints the adj. matrix
    /// @param os 
    void printMatrix(std::ostream& os = std::cout) const;
    /// @brief Creates new edge in the graph with given id
    /// @param id - dependent on the state of the structure
    /// @param source - source node
    /// @param target - target node
    /// @param data 
    /// @return reference to the created edge
    Edge<NData, EData>& add(size_t id, size_t source, size_t target, EData data);
    /// @brief Creates new edge in the graph
    /// @param source - source node
    /// @param target - target node
    /// @param data 
    /// @return reference to the created edge
    Edge<NData, EData>& add(size_t source, size_t target, EData data);
    /// @brief gets the size of the structure
    /// @return 
    size_t size() const;
    /// @brief tells if edge exists
    /// @param id 
    /// @return 
    bool exists(size_t id) const;
    /// @brief tells if edge exists
    /// @param source 
    /// @param target 
    /// @return 
    bool exists(size_t source, size_t target) const;
    /// @brief gets edge based on its id
    /// @param id 
    /// @return 
    Edge<NData, EData>& get(size_t id) const;
    /// @brief class to represent nodes incident with give node, used for indexing
    class IncidentEdges;
    /// @brief gets edge based on incident nodes
    /// @param source 
    /// @param target 
    /// @return 
    Edge<NData, EData>& get(size_t source, size_t target) const;
    IncidentEdges operator[](size_t index) const;
    /// @brief 
    /// @return 
    typename lib::Array<Edge<NData, EData>>::iterator begin() const;
    /// @brief 
    /// @return 
    typename lib::Array<Edge<NData, EData>>::iterator end() const;
};
template <typename NData, typename EData>
class Edges<NData, EData>::IncidentEdges {
    private:
    const Edges* edges_;
    size_t source_;
    public:
    IncidentEdges(const Edges* edges, size_t source) : edges_(edges), source_(source) {};
    Edge<NData, EData>& operator[](size_t index) const; 
};

template <typename NData, typename EData> 
typename Edges<NData, EData>::IncidentEdges Edges<NData, EData>::operator[](size_t index) const {
    return IncidentEdges(this, index);
}
template <typename NData, typename EData> 
Edge<NData, EData>& Edges<NData, EData>::IncidentEdges::operator[](size_t index) const {
    if (edges_->adjacency_matrix_.size() <= source_)
        throw NonexistingItemException("Attempting to access an edge outgoing from a nonexisting source node with identifier "+std::to_string(source_) + ", only "+ std::to_string(edges_->adjacency_matrix_.size()) +" nodes are available"); 
    if (edges_->adjacency_matrix_.size() <= index)
        throw NonexistingItemException("Attempting to access an edge incoming to a nonexisting target node with identifier "+ std::to_string(index) +", only "+ std::to_string(edges_->adjacency_matrix_.size()) +" nodes are available");
    if (!edges_->exists(source_, index))
        throw NonexistingItemException("Attempting to access a nonexisting edge between a pair of nodes with identifiers "+ std::to_string(source_) +" and "+ std::to_string(index) +"");
    size_t id = edges_->get_from_matrix(source_, index);
    return edges_->edges_[id];
};
/// @brief 
/// @tparam NData 
/// @tparam EData 
/// @param os 
/// @param edge 
/// @return 
template <typename NData, typename EData>
std::ostream& operator<<(std::ostream& os, const Edge<NData, EData>& edge) {
    os << "edge (" << edge.getSource().getId() << ")-[" << edge.getId() << " {" << edge.getData() << "}]->(" << edge.getTarget().getId() << ")" << std::endl;
    return os;
};

/// @brief 
/// @tparam NData 
/// @tparam EData 
/// @param os 
/// @param edges 
/// @return 
template <typename NData, typename EData>
std::ostream& operator<<(std::ostream& os, const Edges<NData, EData>& edges) {
    edges.print(os);
    return os;
};


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



template <typename NData, typename EData>
Edges<NData, EData>::Edges(const Edges& other) {
    this->adjacency_matrix_ = other.adjacency_matrix_;
    this->edges_ = other.edges_;
};
template <typename NData, typename EData>
Edges<NData, EData>::Edges(Edges&& other) noexcept {
    std::swap(this->adjacency_matrix_, other.adjacency_matrix_);
    std::swap(this->edges_, other.edges_);
};
template <typename NData, typename EData>
Edges<NData, EData>& Edges<NData, EData>::operator=(const Edges& other) {
    this->adjacency_matrix_ = other.adjacency_matrix_;
    this->edges_ = other.edges_;
    return *this;
};
template <typename NData, typename EData>
Edges<NData, EData>& Edges<NData, EData>::operator=(Edges&& other) noexcept {
    std::swap(this->adjacency_matrix_, other.adjacency_matrix_);
    std::swap(this->edges_, other.edges_);
    return *this;
};

template <typename NData, typename EData>
size_t Edges<NData, EData>::get_from_matrix(size_t source, size_t target) const {
    return adjacency_matrix_[source][target] - 1;
};

template <typename NData, typename EData>
void Edges<NData, EData>::add_e_to_matrix(Edge<NData, EData>& edge){
    size_t source = edge.getSource().getId();
    size_t target = edge.getTarget().getId();
    size_t id = edge.getId();
    adjacency_matrix_[source][target] = id + 1;
    if (graph_->type() == Type::UNDIRECTED)
        adjacency_matrix_[target][source] = id + 1;
};

template <typename NData, typename EData>
void Edges<NData, EData>::add_n_to_matrix(){
    for (auto it = adjacency_matrix_.begin(); it != adjacency_matrix_.end(); ++it){
            it->push_back(0);
    }
    adjacency_matrix_.push_back(std::vector<size_t>(adjacency_matrix_.size() + 1, 0));
};

template <typename NData, typename EData>
void Edges<NData,EData>::print(std::ostream& os) const {
    for (auto it = begin(); it != end(); ++it) {
        const Edge<NData,EData>& e = *it;
        os << e;
    }
};
template <typename NData, typename EData>
void Edges<NData,EData>::printMatrix(std::ostream& os) const {
    for (auto it = adjacency_matrix_.begin(); it != adjacency_matrix_.end(); it++) {
        for (auto it2 = it->begin() ; it2 != it->end(); it2++) {
            if (*it2 == 0)
                std::cout << '-';
            else
                std::cout << (*it2) - 1;
            if (it2 + 1 != it->end())
            std::cout << "|";
        }
        std::cout << std::endl;
    }
};
template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData,EData>::add(size_t id, size_t source, size_t target, EData data) {
    if (id > size())
        throw InvalidIdentifierException("Attempting to add a new edge with invalid identifier "+std::to_string(id)+", expected "+std::to_string(size())+" instead");
    if (exists(id))
        throw ConflictingItemException("Attempting to add a new edge with identifier "+ std::to_string(id) +" which already is associated with another existing edge");
    if (source >= adjacency_matrix_.size() || target >= adjacency_matrix_.size())
        throw NonexistingItemException("Attempting to add a new edge between a nonexisting pair of nodes with identifiers " + std::to_string(source)+" and "+std::to_string(target)+", only "+ std::to_string(adjacency_matrix_.size()) +" nodes are available");
    if (exists(source, target))
        throw ConflictingItemException("Attempting to add a new edge between a pair of nodes with identifiers "+ std::to_string(source) +" and "+ std::to_string(target) +" which already are connected with another existing edge");
    Edge<NData, EData> edge(id, &(graph_->nodes().get(source)) , &(graph_->nodes().get(target)), data);
    try{
        edges_.push_back(edge);
    } catch (UnavailableMemoryException){
        throw UnavailableMemoryException("Unable to insert a new edge record into the underlying container of edges");
    }
    add_e_to_matrix(edge);
    return edges_[edges_.size() - 1];
};
template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData,EData>::add(size_t source, size_t target, EData data) {
    size_t id = edges_.size();
    return add(id,source,target,data);
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
        throw NonexistingItemException("Attempting to test the existence of an edge between a nonexisting pair of nodes with identifiers "+std::to_string(source)+" and "+std::to_string(target)+", only "+std::to_string(adjacency_matrix_.size())+" nodes are available");
    size_t id = get_from_matrix(source, target);
    return id < edges_.size() && id >= 0;
};
template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData,EData>::get(size_t id) const {
    if (!exists(id)) 
        throw NonexistingItemException("Attempting to access a nonexisting edge with identifier "+std::to_string(id)+", only "+std::to_string(size())+" edges are available"); 
    return edges_[id];
};
template <typename NData, typename EData>
Edge<NData, EData>& Edges<NData,EData>::get(size_t source, size_t target) const {
    if (adjacency_matrix_.size() <= source || adjacency_matrix_.size() <= target)
        throw NonexistingItemException("Attempting to access an edge between a nonexisting pair of nodes with identifiers "+std::to_string(source)+" and "+std::to_string(target)+", only "+std::to_string(adjacency_matrix_.size())+" nodes are available"); 
    if (!exists(source, target))
        throw NonexistingItemException("Attempting to access a nonexisting edge between a pair of nodes with identifiers "+std::to_string(source)+" and "+std::to_string(target));; 
    size_t id = get_from_matrix(source, target);
    return edges_[id];
};

template<typename NData, typename EData>
typename lib::Array<Edge<NData, EData>>::iterator Edges<NData,EData>::begin() const {
    return edges_.begin();
};
template<typename NData, typename EData>
typename lib::Array<Edge<NData, EData>>::iterator Edges<NData,EData>::end() const {
    return edges_.end();
};

#endif
/// @file Graph.h
#ifndef GRAPH_H_
#define GRAPH_H_

#include "Node.h"
#include "Edge.h"
#include <fstream>
/// @brief 
enum class Type{
    DIRECTED, UNDIRECTED
};
/// @brief 
/// @tparam NData 
/// @tparam EData 
template <typename NData, typename EData>
class Graph {
protected: 
    Nodes<NData, EData> nodes_;
    Edges<NData, EData> edges_;
public:
    Graph() : nodes_(&edges_), edges_(&nodes_) { };
    Graph(const Graph& other);
    Graph(Graph&& other) noexcept;
    ~Graph() = default;
    Graph& operator=(const Graph& other);
    Graph& operator=(Graph&& other) noexcept;
    /// @brief 
    /// @return 
    Nodes<NData, EData>& nodes();
    /// @brief 
    /// @return 
    Edges<NData, EData>& edges();
    /// @brief 
    /// @param os 
    void print(std::ostream& os = std::cout) const;
    /// @brief 
    /// @param filename 
    void print(const std::string& filename) const;
    /// @brief 
    /// @param is 
    void import(std::istream& is = std::cin);
    /// @brief 
    /// @param filename 
    void import(const std::string& filename);
    virtual Type type() const = 0;
};
/// @brief 
/// @tparam NData 
/// @tparam EData 
template <typename NData, typename EData>
class UndirectedGraph : public Graph <NData, EData> {
    private: 
    public:
    Type type() const override {return Type::UNDIRECTED; };
};
/// @brief 
/// @tparam NData 
/// @tparam EData 
template <typename NData, typename EData>
class DirectedGraph : public Graph <NData, EData> {
    private: 
    public:
    Type type() const override {return Type::DIRECTED; };
};

#pragma region GraphMethods
template <typename NData, typename EData>
Graph<NData, EData>::Graph(const Graph& other) {
    this->nodes_.~Nodes();
    this->edges_.~Edges();
    this->nodes_ = other.nodes_;
    this->edges_ = other.edges_;
};
template <typename NData, typename EData>
Graph<NData, EData>::Graph(Graph&& other) noexcept {
    this->nodes_ = std::move(other.nodes_);
    this->edges_ = std::move(other.edges_);
};
template <typename NData, typename EData>
Graph<NData, EData>& Graph<NData, EData>::operator=(const Graph& other) {
    // nodes_.~Nodes();
    // edges_.~Edges();
    this->nodes_ = other.nodes_;
    this->edges_ = other.edges_;
};
template <typename NData, typename EData>
Graph<NData, EData>& Graph<NData, EData>::operator=(Graph&& other) noexcept {
    std::swap(this->nodes_, other.nodes_);
    std::swap(this->edges_, other.edges_);
};
template <typename NData, typename EData>
Nodes<NData, EData>& Graph<NData, EData>::nodes() {
    return nodes_;
};
template <typename NData, typename EData>
Edges<NData, EData>& Graph<NData, EData>::edges() {
    return edges_;
};
template <typename NData, typename EData>
void Graph<NData, EData>::print(std::ostream& os) const {
    nodes_.print(os);
    edges_.print(os);
};
template <typename NData, typename EData>
void Graph<NData, EData>::print(const std::string& filename) const {
    std::ofstream ofs;
    try {
    ofs.open(filename);
    } catch (std::ofstream::failure){
        throw FileProcessingException("Unable to open an output file " + filename);
    }
    print(ofs);
    ofs.close();
};
template <typename NData, typename EData>
void Graph<NData, EData>::import(std::istream& is) {
    std::string type;
    while(is >> type){
    if (type == "node") {
        is.ignore(3, '(');
        size_t id;
        NData data;
        is >> id;
        char a = is.get();
        is.ignore(3, '{');
        is >> data;
        std::cout << "id: "<< id << " data: " << data <<std::endl;
        char b = is.get();
    }
    else if (type == "edge") {
        is.ignore(3, '(');
        size_t source;
        is >> source;
        is.ignore(3, '[');
        size_t id;
        is >> id;
        is.ignore(3, '{');
        EData data;
        is >> data;
        is.ignore(6, '(');
        size_t target;
        is >> target;
        std::cout << "id: "<< id << " data: " << data << " source:  "<< source << " target: "<< target <<std::endl;
        char b = is.get();
    }
    }
    //std::cout << type << std::endl;
    
};
template <typename NData, typename EData>
void Graph<NData, EData>::import(const std::string& filename) {
    std::ifstream ifs;
    try {
        ifs.open(filename);
    }
    catch (std::ifstream::failure){
        FileProcessingException("Unable to open an input file $filename"); 
    }
    import(ifs);
    ifs.close();
};
#pragma endregion

#pragma region UndirectedGraph

#pragma endregion

#pragma region DirectedGraph

#pragma endregion
#endif
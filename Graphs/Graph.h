/// @file Graph.h
#ifndef GRAPH_H_
#define GRAPH_H_
template <typename NData, typename EData>
class Graph;
/// @brief 
enum class Type{
    DIRECTED, UNDIRECTED
};
#include "Node.h"
#include "Edge.h"
#include <fstream>
#include <sstream>
/// @brief Abstract graph structure
/// @tparam NData 
/// @tparam EData 
template <typename NData, typename EData>
class Graph {
protected: 
    Nodes<NData, EData> nodes_;
    Edges<NData, EData> edges_;
public:
    Graph() : nodes_(&edges_), edges_(this) { };
    Graph(const Graph& other);
    Graph(Graph&& other) noexcept;
    ~Graph() = default;
    Graph& operator=(const Graph& other);
    Graph& operator=(Graph&& other) noexcept;
    /// @brief 
    /// @return Nodes structure with graph associated nodes
    Nodes<NData, EData>& nodes();
    const Nodes<NData, EData>& nodes() const;
    /// @brief 
    /// @return Edges structure with graph associated edges
    Edges<NData, EData>& edges();
    /// @brief Serialize the graph content to stream
    /// @param os 
    void print(std::ostream& os = std::cout) const;
    /// @brief Serialize the graph content to file
    /// @param filename 
    void print(const std::string& filename) const;
    /// @brief Imports graph from a give stream
    /// @param is 
    void import(std::istream& is = std::cin);
    /// @brief Imports graph from filename
    /// @param filename 
    void import(const std::string& filename);
    /// @brief Used to determine the type of the graph
    /// @return 
    virtual Type type() const = 0;
};
/// @brief Undirected graph structure class
/// @tparam NData 
/// @tparam EData 
template <typename NData, typename EData>
class UndirectedGraph : public Graph <NData, EData> {
    private: 
    public:
    Type type() const override {return Type::UNDIRECTED; };
};
/// @brief Directed graph structure class
/// @tparam NData 
/// @tparam EData 
template <typename NData, typename EData>
class DirectedGraph : public Graph <NData, EData> {
    private: 
    public:
    Type type() const override {return Type::DIRECTED; };
};

template <typename NData, typename EData>
std::ostream& operator<<(std::ostream& os, const Graph<NData, EData>& graph) {
    graph.print(os);
    return os;
};

template <typename NData, typename EData>
Graph<NData, EData>::Graph(const Graph& other) {
    this->nodes_ = other.nodes_;
    this->edges_ = other.edges_;
    edges_.graph_ = this;
    nodes_.edges_ = &edges_;
};
template <typename NData, typename EData>
Graph<NData, EData>::Graph(Graph&& other) noexcept {
    this->nodes_ = std::move(other.nodes_);
    this->edges_ = std::move(other.edges_);
    nodes_.edges_ = &edges_;
    edges_.graph_ = this;
};
template <typename NData, typename EData>
Graph<NData, EData>& Graph<NData, EData>::operator=(const Graph& other) {
    // nodes_.~Nodes();
    // edges_.~Edges();
    nodes_ = other.nodes_;
    edges_ = other.edges_;
    nodes_.edges_ = &edges_;
    edges_.graph_ = this;
    return *this;
};
template <typename NData, typename EData>
Graph<NData, EData>& Graph<NData, EData>::operator=(Graph&& other) noexcept {
    std::swap(this->nodes_, other.nodes_);
    std::swap(this->edges_, other.edges_);
    nodes_.edges_ = &edges_;
    edges_.graph_ = this;
    return *this;
};
template <typename NData, typename EData>
Nodes<NData, EData>& Graph<NData, EData>::nodes() {
    return nodes_;
};
template <typename NData, typename EData>
const Nodes<NData, EData>& Graph<NData, EData>::nodes() const {
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
    ofs.open(filename);
    if (!ofs.good())
        throw FileProcessingException("Unable to open an output file " + filename);
    print(ofs);
    ofs.close();
};
template <typename NData, typename EData>
void Graph<NData, EData>::import(std::istream& is) {
    std::string line;
    while (is.good()){
        std::getline(is, line);
        std::stringstream ss(line);
        //ss << line;
        std::string type;
        std::getline(ss, type, ' ');
        if (type == "node") {
            ss.get(); // '('
            size_t id;
            ss >> id; // id
            ss.get(); // ' '
            ss.get(); // '{'
            std::string temp;
            std::getline(ss, temp, '}');
            NData data;
            std::stringstream(temp) >> data;
            nodes_.add(id, data);
        }
        else if (type == "edge") {
            ss.get(); // '('
            size_t source;
            ss >> source;
            ss.get(); // ')'
            ss.get(); // '-'
            ss.get(); // '['
            size_t id;
            ss >> id;
            ss.get(); // ' '
            ss.get(); // '{'
            std::string temp;
            std::getline(ss, temp, '}');
            EData data;
            std::stringstream(temp) >> data;
            std::getline(ss, temp, '('); // "]->("
            size_t target;
            ss >> target;
            edges_.add(source, target, data);
        }
    }
};
template <typename NData, typename EData>
void Graph<NData, EData>::import(const std::string& filename) {
    std::ifstream ifs;
    ifs.open(filename);
    if (!ifs.good())
       throw FileProcessingException("Unable to open an input file "+filename); 
    import(ifs);
    ifs.close();
};

#endif
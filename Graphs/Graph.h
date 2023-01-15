#ifndef GRAPH_H_
#define GRAPH_H_

#include "Node.h"
#include "Edge.h"
#include <fstream>

template <typename NData, typename EData>
class Graph {
private:
    /* data */
protected: 
    Nodes<NData, EData> nodes_;
    Edges<NData, EData> edges_;
public:
    Graph() = default;
    Graph(const Graph& other);
    Graph(Graph&& other) noexcept;
    virtual ~Graph() = default;
    Nodes<NData, EData>& nodes();
    Edges<NData, EData>& edges();
    void print(std::ostream& os = std::cout) const;
    void print(const std::string& filename) const;
    void import(std::istream& is = std::cin);
    void import(const std::string& filename);
};

template <typename NData, typename EData>
class UndirectedGraph : public Graph <NData, EData> {
    private: 
    public:
    UndirectedGraph& operator=(const UndirectedGraph& other);
    UndirectedGraph& operator=(UndirectedGraph&& other) noexcept;
};

template <typename NData, typename EData>
class DirectedGraph : public Graph <NData, EData> {
    private: 
    public:
    DirectedGraph& operator=(const DirectedGraph& other);
    DirectedGraph& operator=(DirectedGraph&& other) noexcept;
};

#pragma region GraphMethods
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
    ofs.open(filename);
    print(ofs);
    ofs.close();
};
template <typename NData, typename EData>
void Graph<NData, EData>::import(std::istream& is) {

};
template <typename NData, typename EData>
void Graph<NData, EData>::import(const std::string& filename) {
    
};
#pragma endregion

#pragma region UndirectedGraph

#pragma endregion

#pragma region DirectedGraph

#pragma endregion
#endif
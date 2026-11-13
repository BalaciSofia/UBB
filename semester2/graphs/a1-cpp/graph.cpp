#include "graph.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

Graph::Graph(int v) {
    for (int i = 0; i < v; i++) {
        d_in[i] = std::vector<int>();
        d_out[i] = std::vector<int>();
    }
}

Graph::Graph(std::vector<int> v) {
    for (auto node : v) {
        d_in[node] = std::vector<int>();
        d_out[node] = std::vector<int>();
    }
}

Graph::Graph(std::map<int,std::vector<int>> in,std::map<int,std::vector<int>> out,std::map<std::pair<int,int>,int> costs) {
    d_in = in;
    d_out = out;
    cost = costs;
}

int Graph::Number_of_Vertices() {
    return int(this->d_in.size());
}

std::vector<int> Graph::Parse_Vertices() {
    std::vector<int> vertices;
    for (const auto& pair : d_out) {
        vertices.push_back(pair.first);
    }
    return vertices;
}

bool Graph::Is_Edge(int x, int y) {
    if (!Valid_Vertex(x) || !Valid_Vertex(y)) {
        throw std::invalid_argument("Vertex does not exist");
    }
    // We must also check if the edge is in the cost map
    return cost.find({x, y}) != cost.end();
}

std::pair<int, int> Graph::InOut_Degree(int x) {
    if (!Valid_Vertex(x)) {
        throw std::invalid_argument("Vertex does not exist");
    }
    return {d_in[x].size(), d_out[x].size()};
}

std::vector<int> Graph::Parse_Out(int x) {
    if (!Valid_Vertex(x)) {
        throw std::invalid_argument("Vertex does not exist");
    }
    return d_out[x];
}

std::vector<int> Graph::Parse_In(int x) {
    if (!Valid_Vertex(x)) {
        throw std::invalid_argument("Vertex does not exist");
    }
    return d_in[x];
}

int Graph::Get_Cost(int v1, int v2) {
    if (!Valid_Vertex(v1) || !Valid_Vertex(v2)) {
        throw std::invalid_argument("One or both vertices do not exist");
    }
    if (!Is_Edge(v1, v2)) {
        throw std::invalid_argument("Edge does not exist");
    }
    return cost[{v1, v2}];
}

void Graph::Update_Cost(int v1, int v2, int new_cost) {
    if (!Valid_Vertex(v1) || !Valid_Vertex(v2)) {
        throw std::invalid_argument("One or both vertices do not exist");
    }
    if (!Is_Edge(v1, v2)) {
        throw std::invalid_argument("Edge does not exist");
    }
    cost[{v1, v2}] = new_cost;
}

void Graph::Append_Edge(int x, int y, int c) {
    if (!Valid_Vertex(x) || !Valid_Vertex(y)) {
        throw std::invalid_argument("One or both vertices do not exist");
    }
    if (Is_Edge(x, y)) {
        throw std::invalid_argument("Edge already exists");
    }
    d_out[x].push_back(y);
    d_in[y].push_back(x);
    cost[{x, y}] = c;
}

void Graph::Delete_Edge(int x, int y) {
    if (!Valid_Vertex(x) || !Valid_Vertex(y)) {
        throw std::invalid_argument("One or both vertices do not exist");
    }
    if (!Is_Edge(x, y)) {
        throw std::invalid_argument("Edge does not exist");
    }
    cost.erase({x, y});
    d_out[x].erase(std::remove(d_out[x].begin(), d_out[x].end(), y), d_out[x].end());
    d_in[y].erase(std::remove(d_in[y].begin(), d_in[y].end(), x), d_in[y].end());
}

void Graph::Append_Vertex(int x) {
    if (Valid_Vertex(x)) {
        throw std::invalid_argument("Vertex already exists");
    }
    d_in[x] = {};
    d_out[x] = {};
}

void Graph::Delete_Vertex(int x) {
    if (!Valid_Vertex(x)) {
        throw std::invalid_argument("Vertex does not exist");
    }
    // Remove all edges to/from this vertex
    for (int v : Parse_In(x)) {
        Delete_Edge(v, x);
    }
    for (int v : Parse_Out(x)) {
        Delete_Edge(x, v);
    }
    d_in.erase(x);
    d_out.erase(x);
}

bool Graph::Valid_Vertex(int v) {
    return d_in.find(v) != d_in.end();
}

void Graph::Print_Graph() {
    std::cout << "Outbound:" << std::endl;
    for (const auto& pair : d_out) {
        std::cout << pair.first << ": ";
        for (int v : pair.second) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Inbound:" << std::endl;
    for (const auto& pair : d_in) {
        std::cout << pair.first << ": ";
        for (int v : pair.second) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
}

std::map<int,std::vector<int>> Graph:: get_d_out() {
    return this->d_out;
}

Graph Graph:: Copy_Graph() const {
    Graph new_graph;
    new_graph.d_out = this->d_out;
    new_graph.d_in=this->d_in;
    new_graph.cost=this->cost;
    return new_graph;
}

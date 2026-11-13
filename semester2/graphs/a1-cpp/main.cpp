#include <iostream>
#include <fstream>
#include "graph.h"
#include <ctime>
#include <vector>
#include <sstream>

void print_menu() {
    std::cout << "1: Get number of vertices\n";
    std::cout << "2: Display the set of vertices\n";
    std::cout << "3: Check if there is an edge between 2 vertices\n";
    std::cout << "4: Get in/out degree of a vertex\n";
    std::cout << "5: Display the set of outbound edges of a specified vertex\n";
    std::cout << "6: Display the set of inbound edges of a specified vertex\n";
    std::cout << "7: Modify the cost attached to a specified edge.\n";
    std::cout << "8: Get cost attached to a specified edge.\n";
    std::cout << "9: Add edge\n";
    std::cout << "a: Remove edge\n";
    std::cout << "b: Add vertex\n";
    std::cout << "c: Remove vertex\n";
    std::cout << "d: Read graph from file\n";
    std::cout << "e: Write graph to file\n";
    std::cout << "f: Create random graph\n";
    std::cout << "g: Print graph\n";
    std::cout << "h: Copy graph and write to file\n";
    std::cout << "i: Exit\n";
    std::cout << "==================================================================================\n";
}
//----------------------------------------------------
void write_graph_to_file(Graph& g,std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Error opening file");
    }
    file << "special\n";
    std::vector<int> vertices = g.Parse_Vertices();
    for (int x : vertices) {
        file << x << " ";
    }
    file << "\n";
    for (int vertex1 : vertices) {
        std::vector<int> out_vertices = g.Parse_Out(vertex1);
        for (int vertex2 : out_vertices) {
            file << vertex1 << " " << vertex2 << " " << g.Get_Cost(vertex1, vertex2) << "\n";
        }
    }
    file.close();
}

Graph read_graph_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Error opening file");
    }
    std::string line;
    std::getline(file, line);
    Graph g;
    if (line == "special") {
        std::getline(file, line);
        std::istringstream iss(line);
        std::vector<int> vertices;
        int v;
        while (iss >> v) {
            vertices.push_back(v);
        }
        g = Graph(vertices);
    } else {
        std::istringstream iss(line);
        int num_vertices;
        iss >> num_vertices;
        g = Graph(num_vertices);
    }
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int vertex1, vertex2, cost;
        if (!(iss >> vertex1 >> vertex2 >> cost)) {
            continue;
        }
        try {
            g.Append_Edge(vertex1, vertex2, cost);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    file.close();
    return g;
}

Graph random_graph(int num_vertices, int num_edges) {
    if (num_edges > num_vertices * num_vertices) {
        throw std::invalid_argument("Too many edges for the given number of vertices");
    }
    Graph g(num_vertices);
    std::srand(std::time(nullptr));
    int edges_added = 0;
    while (edges_added < num_edges) {
        int x = std::rand() % num_vertices;
        int y = std::rand() % num_vertices;
        if (x != y && !g.Is_Edge(x, y)) {
            int cost = std::rand() % 100;
            try {
                g.Append_Edge(x, y, cost);
                edges_added++;
            } catch (const std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
    return g;
}
//----------------------------------------------------

void number_vertices(Graph &g) {
    std::cout << "Number of vertices: " << g.Number_of_Vertices() << std::endl;
}

void display_vertices(Graph& g) {
    std::vector<int> vertices = g.Parse_Vertices();
    for (int v : vertices) {
        std::cout << v << std::endl;
    }
}

void check_edge(Graph& g) {
    int x, y;
    std::cout << "Enter vertex x > ";
    std::cin >> x;
    std::cout << "Enter vertex y > ";
    std::cin >> y;
    try {
        if (g.Is_Edge(x, y)) {
            std::cout << "Edge exists\n";
        } else {
            std::cout << "Edge does not exist\n";
        }
    }catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void get_inout_degree(Graph& g) {
    int x;
    std::cout << "Enter vertex > ";
    std::cin >> x;
    try {
        std::pair<int, int> degree = g.InOut_Degree(x);
        std::cout << "In degree: " << degree.first << "\n";
        std::cout << "Out degree: " << degree.second << "\n";
    }catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void outbound_edges(Graph& g) {
    int x;
    std::cout << "Enter vertex > ";
    std::cin >> x;
    try {
        std::vector<int> outbounds = g.Parse_Out(x);
        for (int o : outbounds) {
            std::cout << o << std::endl;
        }
    }catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void inbound_edges(Graph& g) {
    int x;
    std::cout << "Enter vertex > ";
    std::cin >> x;
    try {
        std::vector<int> inbounds = g.Parse_In(x);
        for (int i : inbounds) {
            std::cout << i << std::endl;
        }
    }catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void modify_cost(Graph& g) {
    int x, y, c;
    std::cout << "Enter vertex x > ";
    std::cin >> x;
    std::cout << "Enter vertex y > ";
    std::cin >> y;
    std::cout << "Enter new cost > ";
    std::cin >> c;

    try {
        g.Update_Cost(x, y, c);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void get_cost(Graph& g) {
    int x, y;
    std::cout << "Enter the edge (x, y)\n";
    std::cout << "Enter vertex x > ";
    std::cin >> x;
    std::cout << "Enter vertex y > ";
    std::cin >> y;

    try {
        int cost = g.Get_Cost(x, y);
        std::cout << "The cost of the edge (" << x << "," << y << ") is " << cost << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void add_edge(Graph& g) {
    int x, y, c;
    std::cout << "Enter vertex x > ";
    std::cin >> x;
    std::cout << "Enter vertex y > ";
    std::cin >> y;
    std::cout << "Enter cost > ";
    std::cin >> c;

    try {
        g.Append_Edge(x, y, c);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void remove_edge(Graph& g) {
    int x, y;
    std::cout << "Enter vertex x > ";
    std::cin >> x;
    std::cout << "Enter vertex y > ";
    std::cin >> y;

    try {
        g.Delete_Edge(x, y);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void add_vertex(Graph& g) {
    int x;
    std::cout << "Enter vertex x > ";
    std::cin >> x;

    try {
        g.Append_Vertex(x);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void remove_vertex(Graph& g) {
    int x;
    std::cout << "Enter vertex x > ";
    std::cin >> x;

    try {
        g.Delete_Vertex(x);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void write_graph_file(Graph &g) {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    write_graph_to_file(g, filename);
}

Graph read_graph_file(Graph &g) {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    return read_graph_from_file(filename);
}

Graph create_random_graph() {
    int n,m;
    std::cout << "Enter number of vertices: ";
    std::cin >> n;
    std::cout << "Enter number of edges: ";
    std::cin >> m;
    try {
        if (m >n*n ) {
            throw std::invalid_argument("Too many edges");
        }
        return random_graph(n, m);
    }catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

}

void copy_write_graph(Graph &g) {
    Graph copy=g.Copy_Graph();
    write_graph_file(copy);
}

int main() {
    Graph g;
    char command;

    while (true) {
        print_menu();
        std::cout << ">>> ";
        std::cin >> command;
        std::cin.ignore();

        switch (command) {
            case '1': number_vertices(g); break;
            case '2': display_vertices(g); break;
            case '3': check_edge(g); break;
            case '4': get_inout_degree(g); break;
            case '5': outbound_edges(g); break;
            case '6': inbound_edges(g); break;
            case '7': modify_cost(g); break;
            case '8': get_cost(g); break;
            case '9': add_edge(g); break;
            case 'a': remove_edge(g); break;
            case 'b': add_vertex(g); break;
            case 'c': remove_vertex(g); break;
            case 'd': g = read_graph_file(g); break;
            case 'e': write_graph_file(g); break;
            case 'f': g = create_random_graph(); break;
            case 'g': g.Print_Graph(); break;
            case 'h': copy_write_graph(g); break;
            case 'i': std::cout << "Exiting...\n"; return 0;
            default: std::cout << "Invalid command\n"; break;
        }
    }
    return 0;
}

#ifndef __GRAPH_A__
#define __GRAPH_A__

#include<vector>
#include<string>

class graph_edge {

    public:
        unsigned int start_node;
        unsigned int end_node;
        graph_edge(unsigned int start_node, unsigned int end_node);
        std::string toString();
};

class weighted_graph_edge : public graph_edge {

    public:
        unsigned int weight;
        weighted_graph_edge(unsigned int start_node, unsigned int end_node, unsigned int weight);
        std::string toString();
};

class way_in_graph {

    public:
        std::vector<unsigned int> nodes;
        unsigned int weight = 0;
        std::string toString();
};

std::vector<graph_edge> deep_first_search(bool** graph, const unsigned int quantity_of_nodes, unsigned int current_node);
std::vector<graph_edge> breadth_first_search(bool** graph, const unsigned int quantity_of_nodes, unsigned int start_node);
way_in_graph* Dijkstra_algorithm(int** graph, const unsigned int quantity_of_nodes, unsigned int start_node);
way_in_graph** Floyd_Warshall_algorithm(int** graph, const unsigned int quantity_of_nodes);
int** Prims_algorithm(int** graph, const unsigned int quantity_of_nodes, unsigned int start_node);
int** Kruskals_algorithm(int** graph, const unsigned int quantity_of_nodes);

#endif
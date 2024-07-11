#ifndef __GRAPH_B__
#define __GRAPH_B__


#include<vector>
#include<string>
#include<deque>

class graph_edge {

    public:
        unsigned int start_node;
        unsigned int end_node;
        graph_edge(unsigned int start_node, unsigned int end_node);
        graph_edge(const graph_edge &original);
        graph_edge reverse();
        std::string toString();
};

template<typename value_type>
void delete_square_matrix(value_type** matrix, unsigned int size);
unsigned* Tarjans_topological_sort(bool** graph, const unsigned quantity_of_nodes, bool test_for_correctness);
std::deque<unsigned> find_Euler_cycle_based_on_simple_cycles(bool** graph, const unsigned quantity_of_nodes, bool oriented);
std::vector<std::vector<unsigned>> Kosarajs_algorithm(bool** graph, const unsigned int quantity_of_nodes);
std::vector<unsigned> Fleurys_algorithm(bool** graph, const unsigned quantity_of_nodes, bool oriented);


#endif
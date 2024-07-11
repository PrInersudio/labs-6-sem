#include"graph-b.h"
#include<stdexcept>
#include<list>
#include<stack>
#include<algorithm>
#define min(a,b) a<b ? a : b

void deep_first_search(bool** graph, const unsigned quantity_of_nodes, unsigned int current_node, bool* visit, std::vector<unsigned>* nodes_of_tree) {
    visit[current_node] = true;
    for (unsigned int i = 0; i < quantity_of_nodes; i++) {
        if ((graph[current_node][i] == false)||(visit[i]==true)) continue;
        nodes_of_tree->push_back(i);
        deep_first_search(graph, quantity_of_nodes, i, visit, nodes_of_tree);
    }
}

graph_edge::graph_edge(unsigned int start_node, unsigned int end_node) {
    this->start_node = start_node;
    this->end_node = end_node;
}

graph_edge::graph_edge(const graph_edge &original) {
    this->start_node = original.start_node;
    this->end_node = original.end_node;
}

graph_edge graph_edge::reverse() {
    return graph_edge(end_node, start_node);
}

std::string graph_edge::toString() {
    return "(" + std::to_string(start_node) + "," + std::to_string(end_node) + ")";
}

bool operator==(graph_edge edge1, graph_edge edge2) {
    return (edge1.start_node==edge2.start_node)&&(edge1.end_node==edge2.end_node);
}

template<typename value_type>
void delete_square_matrix(value_type** matrix, unsigned int size) {
    for (unsigned int i = 0; i < size; i++)
        delete[] matrix[i];
    delete[] matrix;
}

void deep_first_search_inverted(bool** graph, const unsigned quantity_of_nodes, unsigned current_node, std::stack<unsigned>* sorted_nodes, bool* visit) {
    visit[current_node] = true;
    for (int i = 0; i < quantity_of_nodes; i++)
        if ((graph[current_node][i] == true)&&(visit[i] == false)) {
            deep_first_search_inverted(graph, quantity_of_nodes, i, sorted_nodes, visit);
        }
    sorted_nodes->push(current_node);
}

bool test_correctness_of_topological_sort(bool** graph, unsigned* sort_result, const unsigned quantity_of_nodes) {
    for (int i = 0; i < quantity_of_nodes; i++)
        for (int j = i; j <  quantity_of_nodes; j++)
            if (graph[sort_result[j]][sort_result[i]] == true)
                return false;
    return true;
}

unsigned* Tarjans_topological_sort(bool** graph, const unsigned quantity_of_nodes, bool test_for_correctness) {
    bool visit[quantity_of_nodes] = {false};
    std::stack<unsigned> sorted_nodes;
    for (int i = 0; i < quantity_of_nodes; i++)
        if (visit[i] == false)
            deep_first_search_inverted(graph, quantity_of_nodes, i, &sorted_nodes, visit);
    unsigned* result = new unsigned[quantity_of_nodes];
    for (int i = 0; i < quantity_of_nodes; i++) {
        result[i] = sorted_nodes.top();
        sorted_nodes.pop();
    }
    if ((test_for_correctness)&&(!test_correctness_of_topological_sort(graph, result, quantity_of_nodes))) {
        delete[] result;
        throw std::invalid_argument("Topological sort for this graph does not exist.");
    }
    return result;
}

void find_Euler_cycle_based_on_simple_cycle(bool** graph, const unsigned quantity_of_nodes, std::deque<unsigned>* sequence_of_nodes, unsigned current_node, bool oriented) {
    for (int i = 0; i < quantity_of_nodes; i++)
        if (graph[current_node][i] == true) {
            graph[current_node][i] = false;
            if (!oriented) graph[i][current_node] = false;
            find_Euler_cycle_based_on_simple_cycle(graph, quantity_of_nodes, sequence_of_nodes, i, oriented);
        }
    sequence_of_nodes->push_front(current_node);
}

std::deque<unsigned> find_Euler_cycle_based_on_simple_cycles(bool** graph, const unsigned quantity_of_nodes, bool oriented) {
    bool** copy_of_graph = new bool*[quantity_of_nodes];
    for (int i = 0; i < quantity_of_nodes; i++) {
        copy_of_graph[i] = new bool[quantity_of_nodes];
        for (int j = 0; j < quantity_of_nodes; j++) copy_of_graph[i][j] = graph[i][j];
    }
    std::deque<unsigned> sequence_of_nodes;
    find_Euler_cycle_based_on_simple_cycle(copy_of_graph, quantity_of_nodes, &sequence_of_nodes, 0, oriented);
    for (int i = 0; i < quantity_of_nodes; i++)
        for (int j = 0; j < quantity_of_nodes; j++)
                if (copy_of_graph[i][j] == true) {
                    delete_square_matrix(copy_of_graph, quantity_of_nodes);
                    throw std::invalid_argument("There are no Euler cycles in this graph");
                }
    delete_square_matrix(copy_of_graph, quantity_of_nodes);
    if (sequence_of_nodes.back() != sequence_of_nodes.front()) throw std::invalid_argument("There are no Euler cycles in this graph");
    for (int i = 0; i < sequence_of_nodes.size() - 1; i++)
        if (graph[sequence_of_nodes[i]][sequence_of_nodes[i+1]] == false)
            throw std::invalid_argument("There are no Euler cycles in this graph");
    return sequence_of_nodes;
}

bool** reverse_edges(bool** graph, const unsigned quantity_of_nodes) {
    bool** reversed_graph = new bool*[quantity_of_nodes];
    for (int i = 0; i < quantity_of_nodes; i++) {
        reversed_graph[i] = new bool[quantity_of_nodes];
        for (int j = 0; j < quantity_of_nodes; j++) reversed_graph[i][j] = graph[j][i];
    }
    return reversed_graph;
}

std::vector<std::vector<unsigned>> Kosarajs_algorithm(bool** graph, const unsigned int quantity_of_nodes) {
    bool** reversed_graph = reverse_edges(graph, quantity_of_nodes);
    unsigned* topological_sort = Tarjans_topological_sort(reversed_graph, quantity_of_nodes, false);
    bool visit[quantity_of_nodes] = {false};
    std::vector<std::vector<unsigned>> strongly_connected_components;
    for (unsigned i = 0; i < quantity_of_nodes; i++) {
        if (visit[topological_sort[i]] == false) {
            std::vector<unsigned> new_strongly_connected_component = {i};
            deep_first_search(graph, quantity_of_nodes, topological_sort[i], visit, &new_strongly_connected_component);
            strongly_connected_components.push_back(new_strongly_connected_component);
        }
    }
    delete_square_matrix(reversed_graph, quantity_of_nodes);
    delete[] topological_sort;
    return strongly_connected_components;
}

void find_briges(std::vector<graph_edge> edges, const unsigned quantity_of_nodes, unsigned* timer, bool* visit, unsigned* enter_time, unsigned* return_time, std::vector<graph_edge>* briges, unsigned current_node, int parent = -1) {
    visit[current_node] = true;
    enter_time[current_node] = return_time[current_node] = (*timer)++;
    for (int i = 0; i < edges.size(); i++)
        if (edges[i].start_node == current_node) {
            if (edges[i].end_node == parent) continue;
            if (visit[edges[i].end_node] == true) return_time[current_node] = min(return_time[current_node], enter_time[edges[i].end_node]);
            else {
                find_briges(edges, quantity_of_nodes, timer, visit, enter_time, return_time, briges, edges[i].end_node, current_node);
                return_time[current_node] = min(return_time[current_node], return_time[edges[i].end_node]);
                if (return_time[edges[i].end_node] > enter_time[current_node])
                    briges->push_back(graph_edge(current_node, edges[i].end_node));
            }
        }
}

std::vector<graph_edge> find_briges(std::vector<graph_edge> edges, const unsigned quantity_of_nodes) {
    unsigned timer = 0;
    bool visit[quantity_of_nodes] = {false};
    unsigned enter_time[quantity_of_nodes] = {0};
    unsigned return_time[quantity_of_nodes] = {0};
    std::vector<graph_edge> briges;
    for (unsigned i = 0; i < quantity_of_nodes; i++)
        if (visit[i] == false)
            find_briges(edges, quantity_of_nodes, &timer, visit, enter_time, return_time, &briges, i);
    return briges;
}

std::vector<graph_edge> make_vector_of_edges(bool** graph, const unsigned quantity_of_nodes) {
    std::vector<graph_edge> edges;
    for (int i = 0; i < quantity_of_nodes; i++)
        for (int j = 0; j < quantity_of_nodes; j++)
             if (graph[i][j] == true) edges.push_back(graph_edge(i,j));
    return edges;
}

std::vector<unsigned> Fleurys_algorithm(bool** graph, const unsigned quantity_of_nodes, bool oriented) {
    std::vector<graph_edge> edges = make_vector_of_edges(graph, quantity_of_nodes);
    std::vector<graph_edge> briges = find_briges(edges, quantity_of_nodes);
    std::vector<unsigned> sequence_of_nodes;
    unsigned current_node = 0;
    unsigned i = 0;
    unsigned last_found_bridge_index = 0;
    while (edges.size() != 0) {
        if (i >= edges.size()) {
            if (edges[last_found_bridge_index].start_node == current_node)
                i = last_found_bridge_index;
            else throw std::invalid_argument("There are no Euler cycles in this graph");
        }
        else {
            if (edges[i].start_node != current_node) {
                i++;
                continue;
            }
            if (std::find(briges.begin(), briges.end(), edges[i]) != briges.end()) {
                last_found_bridge_index = i;
                i++;
                continue;
            }
            if ((!oriented)&&(std::find(briges.begin(), briges.end(), edges[i].reverse()) != briges.end())) {
                last_found_bridge_index = i;
                i++;
                continue;
            }
        }
        sequence_of_nodes.push_back(current_node);
        current_node = edges[i].end_node;
        if (oriented) {
            edges[i] = edges.back();
            edges.pop_back();
        }
        else {
            graph_edge reversed_edge = edges[i].reverse();
            edges[i] = edges.back();
            edges.pop_back();
            auto it = std::find(edges.begin(), edges.end(), reversed_edge);
            if (it != edges.end()) {
                (*it) = edges.back();
                edges.pop_back();
            }
        }
        i = 0;
        briges = find_briges(edges, quantity_of_nodes);
    }
    sequence_of_nodes.push_back(current_node);
    if (sequence_of_nodes.back() != sequence_of_nodes.front()) throw std::invalid_argument("There are no Euler cycles in this graph");
    for (int i = 0; i < sequence_of_nodes.size() - 1; i++)
        if (graph[sequence_of_nodes[i]][sequence_of_nodes[i+1]] == false)
            throw std::invalid_argument("There are no Euler cycles in this graph");
    return sequence_of_nodes;
}
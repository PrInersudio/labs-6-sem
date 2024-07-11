#include "graph-a.h"
#include <stdexcept>
#include <queue>
#include <climits>
#include <algorithm>

graph_edge::graph_edge(unsigned int start_node, unsigned int end_node) {
    this->start_node = start_node;
    this->end_node = end_node;
}

std::string graph_edge::toString() {
    return "(" + std::to_string(start_node) + "," + std::to_string(end_node) + ")";
}

weighted_graph_edge::weighted_graph_edge(unsigned int start_node, unsigned int end_node, unsigned int weight) : graph_edge(start_node, end_node) {
    this->weight = weight;
}

std::string weighted_graph_edge::toString() {
    return graph_edge::toString() + " w:" + std::to_string(weight);
}

std::string way_in_graph::toString() {
    if (nodes.size() == 0) return "Way is empty";
    std::string way_string = "Way: " + std::to_string(nodes[0]);
    for (int i = 1; i < nodes.size(); i++) way_string += "->" + std::to_string(nodes[i]);
    way_string += " Weight: "  + std::to_string(weight);
    return way_string;
}

bool operator > (weighted_graph_edge edge1, weighted_graph_edge edge2) {
    return edge1.weight > edge2.weight;
}

bool operator < (weighted_graph_edge edge1, weighted_graph_edge edge2) {
    return edge1.weight < edge2.weight;
}

bool operator == (weighted_graph_edge edge1, weighted_graph_edge edge2) {
    return edge1.weight == edge2.weight;
}

bool operator != (weighted_graph_edge edge1, weighted_graph_edge edge2) {
    return edge1.weight != edge2.weight;
}

bool operator <= (weighted_graph_edge edge1, weighted_graph_edge edge2) {
    return edge1.weight <= edge2.weight;
}

bool operator >= (weighted_graph_edge edge1, weighted_graph_edge edge2) {
    return edge1.weight >= edge2.weight;
}

void deep_first_search(bool** graph, const unsigned int quantity_of_nodes, unsigned int current_node, bool* visit, std::vector<graph_edge>* used_edges) {
    visit[current_node] = true;
    for (unsigned int i = 0; i < quantity_of_nodes; i++) {
        if ((graph[current_node][i] == false)||(visit[i]==true)) continue;
        used_edges->push_back(graph_edge(current_node, i));
        deep_first_search(graph, quantity_of_nodes, i, visit, used_edges);
    }
}

std::vector<graph_edge> deep_first_search(bool** graph, const unsigned int quantity_of_nodes, unsigned int start_node) {
    if (start_node >= quantity_of_nodes) throw std::invalid_argument("Number of start node cannot be bigger or equal than quantity of nodes");
    std::vector<graph_edge> used_edges;
    bool visit[quantity_of_nodes] = {false};
    visit[start_node] = true;
    deep_first_search(graph, quantity_of_nodes, start_node, visit, &used_edges);
    return used_edges;
}

std::vector<graph_edge> breadth_first_search(bool** graph, const unsigned int quantity_of_nodes, unsigned int start_node) {
    if (start_node >= quantity_of_nodes) throw std::invalid_argument("Number of start node cannot be bigger or equal than quantity of nodes");
    std::vector<graph_edge> used_edges;
    std::queue<unsigned int> nodes_queue;
    bool visit[quantity_of_nodes] = {false};
    nodes_queue.push(start_node);
    visit[start_node] = true;
    while (!nodes_queue.empty()) {
        int current_node = nodes_queue.front();
        nodes_queue.pop();
        for (unsigned int i = 0; i < quantity_of_nodes; i++) {
            if ((graph[current_node][i] == false)||(visit[i]==true)) continue;
            used_edges.push_back(graph_edge(current_node, i));
            nodes_queue.push(i);
            visit[i] = true;
        }
    }
    return used_edges;
}

way_in_graph* Dijkstra_algorithm(int** graph, const unsigned int quantity_of_nodes, unsigned int start_node) {
    if (start_node >= quantity_of_nodes) throw std::invalid_argument("Number of start node cannot be bigger or equal than quantity of nodes");
    way_in_graph* ways = new way_in_graph[quantity_of_nodes];
    for (int i = 0; i < quantity_of_nodes; i++) ways[i].weight = UINT_MAX;
    ways[start_node].weight = 0;
    ways[start_node].nodes.push_back(start_node);
    bool visit[quantity_of_nodes] = {false};
    int quantity_of_viseted_nodes = 0;
    while(quantity_of_viseted_nodes < quantity_of_nodes) {
        unsigned int smallest_distance = UINT_MAX;
        unsigned int current_node = 0;
        for (unsigned int i = 0; i < quantity_of_nodes; i++)
            if ((smallest_distance > ways[i].weight)&&(visit[i] == false)) {
                smallest_distance = ways[i].weight;
                current_node = i;
            }
        visit[current_node] = true;
        quantity_of_viseted_nodes++;
        for (unsigned int i = 0; i < quantity_of_nodes; i++)
            if ((graph[current_node][i] >= 0) && (ways[i].weight > ways[current_node].weight+ graph[current_node][i])) {
                ways[i].weight = ways[current_node].weight + graph[current_node][i];
                ways[i].nodes = ways[current_node].nodes;
                ways[i].nodes.push_back(i);
            }
    }
    return ways;
}

way_in_graph** Floyd_Warshall_algorithm(int** graph, const unsigned int quantity_of_nodes) {
    way_in_graph** ways = new way_in_graph*[quantity_of_nodes];
    for (unsigned int i = 0; i < quantity_of_nodes; i++) {
        ways[i] = new way_in_graph[quantity_of_nodes];
        for (unsigned int j = 0; j < quantity_of_nodes; j++) {
            if (i == j) {
                ways[i][j].weight = 0;
                ways[i][j].nodes.push_back(i);
                continue;
            }
            ways[i][j].weight = graph[i][j] < 0 ? UINT_MAX : graph[i][j];
            ways[i][j].nodes.push_back(i);
            ways[i][j].nodes.push_back(j);
        }
    }
    for (unsigned int k = 0; k < quantity_of_nodes; k++)
        for (unsigned int i = 0; i < quantity_of_nodes; i++)
            for (unsigned int j = 0; j < quantity_of_nodes; j++)
                if ((ways[i][k].weight != UINT_MAX)&&(ways[k][j].weight != UINT_MAX)&&(ways[i][j].weight > ways[i][k].weight + ways[k][j].weight)) {
                    ways[i][j].weight = ways[i][k].weight + ways[k][j].weight;
                    ways[i][j].nodes = ways[i][k].nodes;
                    for (int l = 1; l < ways[k][j].nodes.size(); l++) ways[i][j].nodes.push_back(ways[k][j].nodes[l]);
                }       
    return ways;
}

int** Prims_algorithm(int** graph, const unsigned int quantity_of_nodes, unsigned int start_node) {
    if (start_node >= quantity_of_nodes) throw std::invalid_argument("Number of start node cannot be bigger or equal than quantity of nodes");
    unsigned int distances[quantity_of_nodes];
    int parent[quantity_of_nodes];
    bool visit[quantity_of_nodes];
    for (int i = 0; i < quantity_of_nodes; i++) {
        distances[i] = UINT_MAX;
        parent[i] = -1;
        visit[i] = false;
    }
    distances[start_node] = 0;
    parent[start_node] = start_node;
    int visited_nodes = 0;
    while(visited_nodes < quantity_of_nodes) {
        unsigned int current_node = start_node;
        unsigned int smallest_distance = UINT_MAX;
        for (unsigned int i = 0; i < quantity_of_nodes; i++)
            if ((smallest_distance > distances[i])&&(visit[i] == false)) {
                current_node = i;
                smallest_distance = distances[i];
            }
        visit[current_node] = true;
        visited_nodes++;
        for (unsigned int i = 0; i < quantity_of_nodes; i++)
            if ((graph[current_node][i] >= 0)&&(graph[current_node][i] < distances[i])&&(visit[i] == false)) {
                distances[i] = graph[current_node][i];
                parent[i] = current_node;
            }
    }
    int** minimal_spanning_tree = new int*[quantity_of_nodes];
    for (int i = 0; i < quantity_of_nodes; i++) {
        minimal_spanning_tree[i] = new int[quantity_of_nodes];
        for (int j = 0; j < quantity_of_nodes; j++) minimal_spanning_tree[i][j] = -1;
    }
    for (int i = 0; i < quantity_of_nodes; i++)
        minimal_spanning_tree[i][parent[i]] = minimal_spanning_tree[parent[i]][i] = graph[parent[i]][i];
    return minimal_spanning_tree;
}

std::vector<weighted_graph_edge> matrix_of_weights_to_vector(int** matrix, const unsigned int quantity_of_nodes) {
    std::vector<weighted_graph_edge> edges;
    for (int i = 0; i < quantity_of_nodes; i++)
        for (int j = i+1; j < quantity_of_nodes; j++)
            if (matrix[i][j] >= 0) edges.push_back(weighted_graph_edge(i,j,matrix[i][j]));
    return edges;
}

int** Kruskals_algorithm(int** graph, const unsigned int quantity_of_nodes) {
    std::vector<weighted_graph_edge> edges = matrix_of_weights_to_vector(graph, quantity_of_nodes);
    std::sort(edges.begin(), edges.end());
    unsigned int in_tree[quantity_of_nodes];
    int** minimal_spanning_tree = new int*[quantity_of_nodes];
    for (unsigned int i = 0; i < quantity_of_nodes; i++) {
        in_tree[i] = i;
        minimal_spanning_tree[i] = new int[quantity_of_nodes];
        for (unsigned int j = 0; j < quantity_of_nodes; j++) minimal_spanning_tree[i][j] = -1;
    }
    for(unsigned int i = 0; i < edges.size(); i++) {
        if(in_tree[edges[i].start_node]!=in_tree[edges[i].end_node]) {
            minimal_spanning_tree[edges[i].start_node][edges[i].end_node] = minimal_spanning_tree[edges[i].end_node][edges[i].start_node] = edges[i].weight;
            unsigned int temp = in_tree[edges[i].start_node];
            for(unsigned int j = 0; j < quantity_of_nodes; j++)
                if (in_tree[j] == temp)
                    in_tree[j] = in_tree[edges[i].end_node];
        }
    }
    return minimal_spanning_tree;
}
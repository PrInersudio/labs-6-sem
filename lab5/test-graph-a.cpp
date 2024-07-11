#include "graph-a.h"
#include <iostream>
#define QUANTITY_OF_NODES_FOR_BYPASS 7
const bool original_graph_for_bypass[QUANTITY_OF_NODES_FOR_BYPASS][QUANTITY_OF_NODES_FOR_BYPASS] =  {
                                                                                                        {false, true, true, false, false, false, false},
                                                                                                        {true, false, false, true, true, false, false},
                                                                                                        {true, false, false, true, false, true, true},
                                                                                                        {false, true, true, false, true, false, false},
                                                                                                        {false, true, false, true, false, false, false},
                                                                                                        {false, false, true, false, false, false, false},
                                                                                                        {false, false, true, false, false, false, false}
                                                                                                    };
#define QUANTITY_OF_NODES_FOR_DIJKSTRA 7
const int original_graph_for_Dijkstra[QUANTITY_OF_NODES_FOR_DIJKSTRA][QUANTITY_OF_NODES_FOR_DIJKSTRA] = {
                                                                                                            {-1, 2, 1, 4, -1, 6, -1},
                                                                                                            {2, -1, -1, 1, 3, -1, -1},
                                                                                                            {1, -1, -1, 2, -1, 4, -1},
                                                                                                            {4, 1, 2, -1, -1, -1, 1},
                                                                                                            {-1, 3, -1, -1, -1, -1, 4},
                                                                                                            {6, -1, 4, -1, -1, -1, 7},
                                                                                                            {-1, -1, -1, 1, 4, 7, -1}
                                                                                                        };

#define QUANTITY_OF_NODES_FOR_FLOYD_WARSHALL 7
const int original_graph_for_Floyd_Warshall[QUANTITY_OF_NODES_FOR_FLOYD_WARSHALL][QUANTITY_OF_NODES_FOR_FLOYD_WARSHALL] =   {
                                                                                                                                {-1, 1, 2, 4, -1, -1, -1},
                                                                                                                                {1, -1, -1, 2, 5, -1, -1},
                                                                                                                                {2, -1, -1, 7, -1, 4, 1},
                                                                                                                                {4, 2, 7, -1, 1, -1, 1},
                                                                                                                                {-1, 5, -1, 1, -1, -1, -1},
                                                                                                                                {-1, -1, 4, -1, -1, -1, -1},
                                                                                                                                {-1, -1, 1, 1, -1, -1, -1},
                                                                                                                            };

#define QUANTITY_OF_NODES_FOR_SPANNING_TREE 7
const int original_graph_for_spanning_tree[QUANTITY_OF_NODES_FOR_SPANNING_TREE][QUANTITY_OF_NODES_FOR_SPANNING_TREE] =  {
                                                                                                                            {-1, 2, 1, 3, -1, 6, -1},
                                                                                                                            {2, -1, -1, 1, 3, -1, -1},
                                                                                                                            {1, -1, -1, 2, -1, 3, -1},
                                                                                                                            {3, 1, 2, -1, -1, -1, 1},
                                                                                                                            {-1, 3, -1, -1, -1, -1, 4},
                                                                                                                            {6, -1, 3, -1, -1, -1, 7},
                                                                                                                            {-1, -1, -1, 1, 4, 7, -1}
                                                                                                                        };
template<typename value_type>
void delete_square_matrix(value_type** matrix, unsigned int size) {
    for (unsigned int i = 0; i < size; i++)
        delete[] matrix[i];
    delete[] matrix;
}

int main() {

    bool** graph_for_bypass = new bool*[QUANTITY_OF_NODES_FOR_BYPASS];
    for (int i = 0; i < QUANTITY_OF_NODES_FOR_BYPASS; i++) {
        graph_for_bypass[i] = new bool[QUANTITY_OF_NODES_FOR_BYPASS];
        for (int j = 0; j < QUANTITY_OF_NODES_FOR_BYPASS; j++)
            graph_for_bypass[i][j] = original_graph_for_bypass[i][j];
    }
    std::vector<graph_edge> dfs_output = deep_first_search(graph_for_bypass, QUANTITY_OF_NODES_FOR_BYPASS, 0);
    std::cout << "\n\nDeep first search: ";
    for (int i = 0; i < dfs_output.size(); i++) std::cout << dfs_output[i].toString() << " ";
    std::vector<graph_edge> bfs_output = breadth_first_search(graph_for_bypass, QUANTITY_OF_NODES_FOR_BYPASS, 0);
    std::cout << "\n\n\nBreadth first search: ";
    for (int i = 0; i < bfs_output.size(); i++) std::cout << bfs_output[i].toString() << " ";

    int** graph_for_Dijkstra = new int*[QUANTITY_OF_NODES_FOR_DIJKSTRA];
    for (int i = 0; i < QUANTITY_OF_NODES_FOR_DIJKSTRA; i++) {
        graph_for_Dijkstra[i] = new int[QUANTITY_OF_NODES_FOR_DIJKSTRA];
        for (int j = 0; j < QUANTITY_OF_NODES_FOR_DIJKSTRA; j++)
            graph_for_Dijkstra[i][j] = original_graph_for_Dijkstra[i][j];
    }
    way_in_graph* Dijkstra_ways = Dijkstra_algorithm(graph_for_Dijkstra, QUANTITY_OF_NODES_FOR_DIJKSTRA, 3);
    std::cout << "\n\n\nDijkstra algorithm: \n";
    for (int i = 0; i < QUANTITY_OF_NODES_FOR_DIJKSTRA; i++) std::cout << Dijkstra_ways[i].toString() << "\n";

    int** graph_for_Floyd_Warshall = new int*[QUANTITY_OF_NODES_FOR_FLOYD_WARSHALL];
    for (int i = 0; i < QUANTITY_OF_NODES_FOR_FLOYD_WARSHALL; i++) {
        graph_for_Floyd_Warshall[i] = new int[QUANTITY_OF_NODES_FOR_FLOYD_WARSHALL];
        for (int j = 0; j < QUANTITY_OF_NODES_FOR_FLOYD_WARSHALL; j++)
            graph_for_Floyd_Warshall[i][j] = original_graph_for_Floyd_Warshall[i][j];
    }
    way_in_graph** Floyd_Warshall_ways = Floyd_Warshall_algorithm(graph_for_Floyd_Warshall, QUANTITY_OF_NODES_FOR_FLOYD_WARSHALL);
    std::cout << "\n\nFloyd Warshall algorithm: \n\n";
    for (int i = 0; i < QUANTITY_OF_NODES_FOR_FLOYD_WARSHALL; i++) {
        for (int j = 0; j < QUANTITY_OF_NODES_FOR_FLOYD_WARSHALL; j++)
            std::cout << Floyd_Warshall_ways[i][j].toString() << "\n";
        std::cout << "\n";
    }

    int** graph_for_spanning_tree = new int*[QUANTITY_OF_NODES_FOR_SPANNING_TREE];
    for (int i = 0; i < QUANTITY_OF_NODES_FOR_SPANNING_TREE; i++) {
        graph_for_spanning_tree[i] = new int[QUANTITY_OF_NODES_FOR_SPANNING_TREE];
        for (int j = 0; j < QUANTITY_OF_NODES_FOR_SPANNING_TREE; j++)
            graph_for_spanning_tree[i][j] = original_graph_for_spanning_tree[i][j];
    }
    int** minimal_spanning_tree_Prim = Prims_algorithm(graph_for_spanning_tree, QUANTITY_OF_NODES_FOR_SPANNING_TREE, 4);
    std::cout << "\nPrim's algorithm: \n";
    for (int i = 0; i < QUANTITY_OF_NODES_FOR_SPANNING_TREE; i++) {
        for (int j = 0; j < QUANTITY_OF_NODES_FOR_SPANNING_TREE; j++)
            std::cout << minimal_spanning_tree_Prim[i][j] << " ";
        std::cout << "\n";
    }

    int** minimal_spanning_tree_Kruskal = Kruskals_algorithm(graph_for_spanning_tree, QUANTITY_OF_NODES_FOR_SPANNING_TREE);
    std::cout << "\n\nKruskal's algorithm: \n";
    for (int i = 0; i < QUANTITY_OF_NODES_FOR_SPANNING_TREE; i++) {
        for (int j = 0; j < QUANTITY_OF_NODES_FOR_SPANNING_TREE; j++)
            std::cout << minimal_spanning_tree_Kruskal[i][j] << " ";
        std::cout << "\n";
    }
    
    delete_square_matrix(graph_for_bypass, QUANTITY_OF_NODES_FOR_BYPASS);
    delete_square_matrix(graph_for_Dijkstra, QUANTITY_OF_NODES_FOR_DIJKSTRA);
    delete[] Dijkstra_ways;
    delete_square_matrix(graph_for_Floyd_Warshall, QUANTITY_OF_NODES_FOR_FLOYD_WARSHALL);
    delete_square_matrix(Floyd_Warshall_ways, QUANTITY_OF_NODES_FOR_FLOYD_WARSHALL);
    delete_square_matrix(graph_for_spanning_tree, QUANTITY_OF_NODES_FOR_SPANNING_TREE);
    delete_square_matrix(minimal_spanning_tree_Prim, QUANTITY_OF_NODES_FOR_SPANNING_TREE);
    delete_square_matrix(minimal_spanning_tree_Kruskal, QUANTITY_OF_NODES_FOR_SPANNING_TREE);
    return 0;
}
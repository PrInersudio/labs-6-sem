#include"graph-b.h"
#include<iostream>
#include<stdexcept>

#define QUANTITY_OF_NODES_FOR_CORRECT_TOPOLOGICAL_SORT 7
const bool original_graph_for_correct_topological_sort[QUANTITY_OF_NODES_FOR_CORRECT_TOPOLOGICAL_SORT][QUANTITY_OF_NODES_FOR_CORRECT_TOPOLOGICAL_SORT] =    {
                                                                                                                                                                {false, true, true, false, false, false, false},
                                                                                                                                                                {false, false, false, true, false, false, false},
                                                                                                                                                                {false, false, false, true, false, true, false},
                                                                                                                                                                {false, false, false, false, false, false, true},
                                                                                                                                                                {false, false, false, false, false, true, false},
                                                                                                                                                                {false, false, false, false, false, false, true},
                                                                                                                                                                {false, false, false, false, false, false, false},
                                                                                                                                                            };
#define QUANTITY_OF_NODES_FOR_INCORRECT_TOPOLOGICAL_SORT 5
const bool original_graph_for_incorrect_topological_sort[QUANTITY_OF_NODES_FOR_INCORRECT_TOPOLOGICAL_SORT][QUANTITY_OF_NODES_FOR_INCORRECT_TOPOLOGICAL_SORT] =  {
                                                                                                                                                                    {false, true, true, false, false},
                                                                                                                                                                    {false, false, false, false, true},
                                                                                                                                                                    {false, true, false, false, true},
                                                                                                                                                                    {false, true, false, false, false},
                                                                                                                                                                    {false, false, false, true, false},
                                                                                                                                                                };

#define QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_UNORIENTED_GRAPH 6
const bool original_graph_for_euler_cycle_search_in_unoriented_graph[QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_UNORIENTED_GRAPH][QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_UNORIENTED_GRAPH] = {
                                                                                                                                                                                                        {false, true, true, true, true, false},
                                                                                                                                                                                                        {true, false, true, true, true, false},
                                                                                                                                                                                                        {true, true, false, true, false, true},
                                                                                                                                                                                                        {true, true, true, false, true, false},
                                                                                                                                                                                                        {true, true, false, true, false, true},
                                                                                                                                                                                                        {false, false, true, false, true, false},
                                                                                                                                                                                                    };
#define QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_ORIENTED_GRAPH 4
const bool original_graph_for_euler_cycle_search_in_oriented_graph[QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_ORIENTED_GRAPH][QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_ORIENTED_GRAPH] =    {
                                                                                                                                                                                                    {false, true, false, false},
                                                                                                                                                                                                    {false, false, true, false},
                                                                                                                                                                                                    {false, false, false, true},
                                                                                                                                                                                                    {true, false, false, false}
                                                                                                                                                                                                };

#define QUANTITY_OF_NODES_FOR_KOSARAJ 8
const bool original_graph_for_Kosaraj[QUANTITY_OF_NODES_FOR_KOSARAJ][QUANTITY_OF_NODES_FOR_KOSARAJ] =   {
                                                                                                            {false, false, false, true, false, false, false, false},
                                                                                                            {true, false, false, false, false, false, false, false},
                                                                                                            {false, true, false, false, false, false, true, false},
                                                                                                            {true, false, false, false, true, false, false, false},
                                                                                                            {false, true, false, false, false, false, false, false},
                                                                                                            {false, false, true, false, true, false, false, false},
                                                                                                            {false, false, true, false, false, true, false, false},
                                                                                                            {false, false, false, false, true, false, true, false},
                                                                                                        };

#define QUANTITY_OF_NODES_NO_EULER_PATH_1 4
const bool original_graph_no_Euler_cycle_1[QUANTITY_OF_NODES_NO_EULER_PATH_1][QUANTITY_OF_NODES_NO_EULER_PATH_1] =   {
                                                                                                                        {false, true, false, false},
                                                                                                                        {false, false, true, false},
                                                                                                                        {false, false, false, true},
                                                                                                                        {false, false, false, false}
                                                                                                                    };

#define QUANTITY_OF_NODES_NO_EULER_PATH_2 4
const bool original_graph_no_Euler_cycle_2[QUANTITY_OF_NODES_NO_EULER_PATH_2][QUANTITY_OF_NODES_NO_EULER_PATH_2] =   {
                                                                                                                        {false, true, false, false},
                                                                                                                        {false, false, true, true},
                                                                                                                        {false, false, false, true},
                                                                                                                        {true, false, false, false}
                                                                                                                    };

int main() {

    bool** graph_for_correct_topological_sort = new bool*[QUANTITY_OF_NODES_FOR_CORRECT_TOPOLOGICAL_SORT];
    for (unsigned i = 0; i < QUANTITY_OF_NODES_FOR_CORRECT_TOPOLOGICAL_SORT; i++) {
        graph_for_correct_topological_sort[i] = new bool[QUANTITY_OF_NODES_FOR_CORRECT_TOPOLOGICAL_SORT];
        for (unsigned j = 0; j < QUANTITY_OF_NODES_FOR_CORRECT_TOPOLOGICAL_SORT; j++)
            graph_for_correct_topological_sort[i][j] = original_graph_for_correct_topological_sort[i][j];
    }
    std::cout << "\n\nTarjan's correct topological sort: ";
    try {
        unsigned* correct_topological_sort_result = Tarjans_topological_sort(graph_for_correct_topological_sort, QUANTITY_OF_NODES_FOR_CORRECT_TOPOLOGICAL_SORT, true);
        for (int i = 0; i < QUANTITY_OF_NODES_FOR_CORRECT_TOPOLOGICAL_SORT; i++) std::cout << correct_topological_sort_result[i] << " ";
        std::cout << "\n";
        delete[] correct_topological_sort_result;
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
    }

    bool** graph_for_incorrect_topological_sort = new bool*[QUANTITY_OF_NODES_FOR_INCORRECT_TOPOLOGICAL_SORT];
    for (unsigned i = 0; i < QUANTITY_OF_NODES_FOR_INCORRECT_TOPOLOGICAL_SORT; i++) {
        graph_for_incorrect_topological_sort[i] = new bool[QUANTITY_OF_NODES_FOR_INCORRECT_TOPOLOGICAL_SORT];
        for (unsigned j = 0; j < QUANTITY_OF_NODES_FOR_INCORRECT_TOPOLOGICAL_SORT; j++)
            graph_for_incorrect_topological_sort[i][j] = original_graph_for_incorrect_topological_sort[i][j];
    }
    std::cout << "Test for incorrect sort: ";
    try {
        unsigned* incorrect_topological_sort_result = Tarjans_topological_sort(graph_for_incorrect_topological_sort, QUANTITY_OF_NODES_FOR_INCORRECT_TOPOLOGICAL_SORT, true);
        delete[] incorrect_topological_sort_result;
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
    }

    bool** graph_for_euler_cycle_search_in_unoriented_graph = new bool*[QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_UNORIENTED_GRAPH];
    for (unsigned i = 0; i < QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_UNORIENTED_GRAPH; i++) {
        graph_for_euler_cycle_search_in_unoriented_graph[i] = new bool[QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_UNORIENTED_GRAPH];
        for (unsigned j = 0; j < QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_UNORIENTED_GRAPH; j++)
            graph_for_euler_cycle_search_in_unoriented_graph[i][j] = original_graph_for_euler_cycle_search_in_unoriented_graph[i][j];
    }
    try {
        std::deque<unsigned> Euler_cycle_based_on_cycles_in_unoriented_graph = find_Euler_cycle_based_on_simple_cycles(graph_for_euler_cycle_search_in_unoriented_graph, QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_UNORIENTED_GRAPH, false);
        std::cout << "\n\nEuler cycle based on cycles in unoriented graph: ";
        for (int i = 0; i < Euler_cycle_based_on_cycles_in_unoriented_graph.size(); i++) std::cout << Euler_cycle_based_on_cycles_in_unoriented_graph[i] << " ";
        std::cout << "\n";
    }
    catch (std::invalid_argument &e) {
        std::cerr << e.what() << "\n";
    }

    bool** graph_for_euler_cycle_search_in_oriented_graph = new bool*[QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_ORIENTED_GRAPH];
    for (unsigned i = 0; i < QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_ORIENTED_GRAPH; i++) {
        graph_for_euler_cycle_search_in_oriented_graph[i] = new bool[QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_ORIENTED_GRAPH];
        for (unsigned j = 0; j < QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_ORIENTED_GRAPH; j++)
            graph_for_euler_cycle_search_in_oriented_graph[i][j] = original_graph_for_euler_cycle_search_in_oriented_graph[i][j];
    }
    try {
        std::deque<unsigned> Euler_cycle_based_on_cycles_in_oriented_graph = find_Euler_cycle_based_on_simple_cycles(graph_for_euler_cycle_search_in_oriented_graph, QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_ORIENTED_GRAPH, true);
        std::cout << "Euler cycle based on cycles in oriented graph: ";
        for (int i = 0; i < Euler_cycle_based_on_cycles_in_oriented_graph.size(); i++) std::cout << Euler_cycle_based_on_cycles_in_oriented_graph[i] << " ";
        std::cout << "\n";
    }
    catch (std::invalid_argument &e) {
        std::cerr << e.what() << "\n";
    }

    std::cout << "Test for no Euler cycle (based on simple cycles algorithm) 1: ";
    bool** graph_no_Euler_cycle_1 = new bool*[QUANTITY_OF_NODES_NO_EULER_PATH_1];
    for (int i = 0; i < QUANTITY_OF_NODES_NO_EULER_PATH_1; i++) {
        graph_no_Euler_cycle_1[i] = new bool[QUANTITY_OF_NODES_NO_EULER_PATH_1];
        for (int j = 0; j < QUANTITY_OF_NODES_NO_EULER_PATH_1; j++)
            graph_no_Euler_cycle_1[i][j] = original_graph_no_Euler_cycle_1[i][j];
    }
    try {
        find_Euler_cycle_based_on_simple_cycles(graph_no_Euler_cycle_1, QUANTITY_OF_NODES_NO_EULER_PATH_1, true);
    }
    catch (std::invalid_argument &e) {
        std::cerr << e.what() << "\n";
    }

    std::cout << "Test for no Euler cycle (based on simple cycles algorithm) 2: ";
    bool** graph_no_Euler_cycle_2 = new bool*[QUANTITY_OF_NODES_NO_EULER_PATH_2];
    for (int i = 0; i < QUANTITY_OF_NODES_NO_EULER_PATH_2; i++) {
        graph_no_Euler_cycle_2[i] = new bool[QUANTITY_OF_NODES_NO_EULER_PATH_2];
        for (int j = 0; j < QUANTITY_OF_NODES_NO_EULER_PATH_2; j++)
            graph_no_Euler_cycle_2[i][j] = original_graph_no_Euler_cycle_2[i][j];
    }
    try {
        find_Euler_cycle_based_on_simple_cycles(graph_no_Euler_cycle_2, QUANTITY_OF_NODES_NO_EULER_PATH_2, true);
    }
    catch (std::invalid_argument &e) {
        std::cerr << e.what() << "\n";
    }

    bool** graph_for_graph_for_Kosaraj = new bool*[QUANTITY_OF_NODES_FOR_KOSARAJ];
    for (unsigned i = 0; i < QUANTITY_OF_NODES_FOR_KOSARAJ; i++) {
        graph_for_graph_for_Kosaraj[i] = new bool[QUANTITY_OF_NODES_FOR_KOSARAJ];
        for (unsigned j = 0; j < QUANTITY_OF_NODES_FOR_KOSARAJ; j++)
            graph_for_graph_for_Kosaraj[i][j] = original_graph_for_Kosaraj[i][j];
    }
    std::vector<std::vector<unsigned>> strongly_connected_components = Kosarajs_algorithm(graph_for_graph_for_Kosaraj, QUANTITY_OF_NODES_FOR_KOSARAJ);
    std::cout << "\n\nKosaraj's algorithm:\n";
    for (int i = 0; i < strongly_connected_components.size(); i++) {
        for (int j = 0; j < strongly_connected_components[i].size(); j++)
            std::cout << strongly_connected_components[i][j] << " ";
        std::cout << "\n";
    }

    try {
        std::vector<unsigned> Euler_cycle_Fleurys_algorithm_in_unoriented_graph = Fleurys_algorithm(graph_for_euler_cycle_search_in_unoriented_graph, QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_UNORIENTED_GRAPH, false);
        std::cout << "\n\nFleury's_algorithm in unoriented graph: ";
        for (int i = 0; i < Euler_cycle_Fleurys_algorithm_in_unoriented_graph.size(); i++) std::cout << Euler_cycle_Fleurys_algorithm_in_unoriented_graph[i] << " ";
        std::cout << "\n";
    }
    catch (std::invalid_argument &e) {
        std::cerr << e.what() << "\n";
    }

    try {
        std::vector<unsigned> Euler_cycle_Fleurys_algorithm_in_oriented_graph = Fleurys_algorithm(graph_for_euler_cycle_search_in_oriented_graph, QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_ORIENTED_GRAPH, true);
        std::cout << "Fleury's_algorithm in oriented graph: ";
        for (int i = 0; i < Euler_cycle_Fleurys_algorithm_in_oriented_graph.size(); i++) std::cout << Euler_cycle_Fleurys_algorithm_in_oriented_graph[i] << " ";
        std::cout << "\n";
    }
    catch (std::invalid_argument &e) {
        std::cerr << e.what() << "\n";
    }

    std::cout << "Test for no Euler cycle (Fleury's algorithm) 1: ";
    try {
        Fleurys_algorithm(graph_no_Euler_cycle_2, QUANTITY_OF_NODES_NO_EULER_PATH_2, true);
    }
    catch (std::invalid_argument &e) {
        std::cerr << e.what() << "\n";
    }

    std::cout << "Test for no Euler cycle (Fleury's algorithm) 2: ";
    try {
        Fleurys_algorithm(graph_no_Euler_cycle_1, QUANTITY_OF_NODES_NO_EULER_PATH_1, true);
    }
    catch (std::invalid_argument &e) {
        std::cerr << e.what() << "\n";
    }

    std::cout << "\n\n";
    delete_square_matrix(graph_for_correct_topological_sort, QUANTITY_OF_NODES_FOR_CORRECT_TOPOLOGICAL_SORT);
    delete_square_matrix(graph_for_incorrect_topological_sort, QUANTITY_OF_NODES_FOR_INCORRECT_TOPOLOGICAL_SORT);
    delete_square_matrix(graph_for_euler_cycle_search_in_unoriented_graph, QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_UNORIENTED_GRAPH);
    delete_square_matrix(graph_for_euler_cycle_search_in_oriented_graph, QUANTITY_OF_NODES_FOR_EULER_CYCLE_SEARCH_IN_ORIENTED_GRAPH);
    delete_square_matrix(graph_for_graph_for_Kosaraj, QUANTITY_OF_NODES_FOR_KOSARAJ);
    delete_square_matrix(graph_no_Euler_cycle_1, QUANTITY_OF_NODES_NO_EULER_PATH_1);
    delete_square_matrix(graph_no_Euler_cycle_2, QUANTITY_OF_NODES_NO_EULER_PATH_2);
    return 0;
}
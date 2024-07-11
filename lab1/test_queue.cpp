#include"priority_queue.h"
#include<iostream>
#include<vector>

int main(int argc, const char *argv[]) {
    if (argc <= 1) {
        std::cout << "Enter test seqence of integers as parametrs of command line\n";
        return 0;
    }
    priority_queue<int, std::vector<int>> queue; 
    for (int i = 1; i < argc; i++)
        queue.push(atoi(argv[i]));
    while(!queue.empty()) {
        std::cout << "Biggest number: " << queue.top() << " Quantity of numbers: " << queue.size() << "\n";
        queue.pop();
    }
    return 0;
}
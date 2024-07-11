#include"substring.h"
#include<iostream>
int main(int _argc, char** _argv) {

    if (_argc != 3) {
        std::cout << "Run like this: " << _argv[0] << " <string> <substring>\n";
        return 0;
    }
    std::string String(_argv[1]);
    std::string Example(_argv[2]);
    std::cout << "Rabin-Karp:";
    std::vector<std::size_t> RabinKarp_result = RabinKarp(String, Example);
    for (int i = 0; i < RabinKarp_result.size(); i++) std::cout << " " << RabinKarp_result[i];
    std::cout << std::endl;

    std::cout << "Boyer-Moore:";
    std::vector<std::size_t> BoyerMoore_result = BoyerMoore(String, Example);
    for (int i = 0; i < BoyerMoore_result.size(); i++) std::cout << " " << BoyerMoore_result[i];
    std::cout << std::endl;

    std::cout << "Knuth-Morris-Pratt:";
    std::vector<std::size_t> KnuthMorrisPratt_result = KnuthMorrisPratt(String, Example);
    for (int i = 0; i < KnuthMorrisPratt_result.size(); i++) std::cout << " " << KnuthMorrisPratt_result[i];
    std::cout << std::endl;

    std::cout << "Based on automat algorithm:" << std::endl;
    std::cout << "Enter examples (enter 0 after last): ";
    std::vector<std::string> examples;
    std::string current_example;
    do {
        std::cin >> current_example;
        examples.push_back(current_example);
    } while(current_example != "0");
    examples.pop_back();
    std::cout << "Enter string: ";
    std::string string_for_automat;
    std::cin >> string_for_automat;
    std::vector<std::size_t>* automat_result = find_substrings_based_on_automat(examples, string_for_automat);
    for (int i = 0; i < examples.size(); i++) {
        std::cout << examples[i] << ": ";
        for (int j = 0; j < automat_result[i].size(); j++)
            std::cout << automat_result[i][j] << " ";
        std::cout << std::endl;
    }
    delete[] automat_result;
    return 0;
}
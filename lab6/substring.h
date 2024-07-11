#include<vector>
#include<string>

#define char_alphabet_size 256
#define RabinKarp_module 257

std::vector<std::size_t> RabinKarp(std::string& String, std::string& Example);
std::vector<std::size_t> BoyerMoore(std::string& String, std::string& Example);
std::vector<std::size_t> KnuthMorrisPratt(std::string& String, std::string& Example);
std::vector<std::size_t>* find_substrings_based_on_automat(std::vector<std::string> examples, std::string String);
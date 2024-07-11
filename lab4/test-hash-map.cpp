#include <iostream>
#include<string>
#include "hash-map.h"

void help_message() {
    std::cout << "Use this commands to test hash-map:\n";
    std::cout << "test_copy - tests copy constractor\n";
    std::cout << "is_empty - outputs the state of hash-map (empty ot not)\n";
    std::cout << "contains <key> - check if is there an element with this key\n";
    std::cout << "size - outputs hash-map size\n";
    std::cout << "clear - deletes all elements in hash-map\n";
    std::cout << "add <key> <value> - adds a new pair of key-value or replaces value if this key parameter already exists. String parameters are used for key and value in this test programm\n";
    std::cout << "print <key> - prints a value that is associated with the entered key. Behavior for nonexistrnt key is undefined\n";
    std::cout << "delete <key> - deletes a key-value pair found with the entered key\n";
    std::cout << "test_it - test for iterators. All element will be printed in ascending(to test iterator increment) and descending(decrement) order \n";
    std::cout << "find <key> - creates an iterator that points on element with this key and then uses it to print this element. Behavior for nonexistrnt key is undefined\n";
    std::cout << "rehash <new_segments_quantity> - rehashes this map with new quantity of segments(uses closest to entered number bigger prime number)\n";
    std::cout << "print_max_load_factor - outputs hash-map max_load_factor\n";
    std::cout << "change_max_load_factor <new_max_load_factor> - changes max_load_factor. Behavior for 0 is undefined\n";
    std::cout << "print_load_factor - prints current load factor\n";
    std::cout << "bucket <key> - prints number of segment which corresponds to entered key\n";
    std::cout << "bucket_size <n> - prints size of nth segiment. Behavior for n > quantity of segments is undefined\n";
    std::cout << "bucket_count - prints quantity of segments\n";
    std::cout << "help - display this message\n";
    std::cout << "quit - quit from this programm\n";
}

int main() {
    std::cout << "Welcome. Hash-map tests on strings.\n";
    hash_map<std::string,std::string>  test;
    std::cout << "\nHash-map is created.\n";
    help_message();
    while(true) {
        std::cout << "Enter next command: ";
        std::string command;
        std::cin >> command;
        if (command == "test_copy") {
            hash_map<std::string,std::string> copy = test;
            std::cout << "Copy of hash-map:\n" << copy;
        }
        else if (command == "is_empty")
            if (test.empty())
                std::cout << "Hash-map is empty\n";
            else
                std::cout << "Hash-map is not empty\n";
        else if (command == "contains") {
            std::string key;
            std::cin >> key;
            if (test.contains(key))
                std::cout << "The element with this key is found\n";
            else
                std::cout << "The element with this key is not found\n";
        }
        else if (command == "size")
            std::cout << "Hash-map size is " << test.size() << "\n";
        else if (command == "clear")
            test.clear();
        else if (command == "add") {
            std::string key, value;
            std::cin >> key >> value;
            test.emplace(key, value);
        }
        else if (command == "print") {
            std::string key;
            std::cin >> key;
            std::cout << "Your value: " << test[key] << "\n";
        }
        else if (command == "delete") {
            std::string key;
            std::cin >> key;
            test.erase(key);
        }
        else if (command == "test_it") {
            hash_map<std::string,std::string>::iterator it = test.begin();
            while (it != test.end()) {
                std::cout << (*it) << " ";
                it++;
            }
            std::cout << "\n";
            it = test.end();
            while (it != test.begin()) {
                it--;
                std::cout << (*it) << " ";
            }
            std::cout << "\n";
        }
        else if (command == "find") {
            std::string key;
            std::cin >> key;
            try {
                hash_map<std::string,std::string>::iterator it = test.find(key);
                std::cout << "Your value: " << (*it) << "\n";
            }
            catch (std::out_of_range& e) {
                std::cout << e.what() << "\n";
            }
        }
        else if (command == "rehash") {
            std::size_t new_lists_quantity;
            std::cin >> new_lists_quantity;
            test.rehash(new_lists_quantity);
        }
        else if (command == "print_max_load_factor") {
            std::cout << test.max_load_factor() << std::endl;
        }
        else if (command == "change_max_load_factor") {
            double new_max_load_factor;
            std::cin >> new_max_load_factor;
            test.max_load_factor(new_max_load_factor);
        }
        else if (command == "print_load_factor") {
            std::cout << test.load_factor() << std::endl;
        }
        else if (command == "bucket") {
            std::string key;
            std::cin >> key;
            std::cout << test.bucket(key) << std::endl;
        }
        else if (command == "bucket_size") {
            std::size_t number;
            std::cin >> number;
            std::cout << test.bucket_size(number) << std::endl;
        }
        else if (command == "bucket_count") {
            std::cout << test.bucket_count() << std::endl;
        }
        else if (command == "help")
            help_message();
        else if (command == "quit")
            break;
        else
            std::cout << "Unknown command. Enter help to see the list of commands\n";
        std::cout << test;
        std::cin.ignore(32767, '\n');
    }
    std::cout << "Test of hash-map is ended. Goodbye.\n";
    return 0;
}
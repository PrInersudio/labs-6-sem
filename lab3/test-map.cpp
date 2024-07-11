#include <iostream>
#include "btree_map.h"

void help_message() {
    std::cout << "Use this commands to test btree:\n";
    std::cout << "test_copy - tests copy constractor\n";
    std::cout << "is_empty - outputs the state of btree (empty ot not)\n";
    std::cout << "contains <key> - check if is there an element with this key\n";
    std::cout << "size - outputs btree size\n";
    std::cout << "clear - deletes all elements in tree\n";
    std::cout << "add <key> <value> - adds a new pair of key-value or replaces value if this key parameter already exists. Integer parameters are used for key and value in this test programm\n";
    std::cout << "print <key> - prints a value that is associated with the entered key\n";
    std::cout << "delete <key> - deletes a key-value pair found with the entered key\n";
    std::cout << "test_it - test for iterators. Btree iterators are used to print all values in btree in deep first search order and inverted\n";
    std::cout << "find <key> - creates an iterator that points on element with this key and then uses it to print this element\n";
    std::cout << "help - display this message\n";
    std::cout << "quit - quit from this programm\n";
}

int main() {
    std::cout << "Welcome. Btree tests on integers.\n";
    std::cout << "Enter minimal degree of node (parameter t): ";
    unsigned t;
    std::cin >> t;
    btree_map<int, int> test = btree_map<int, int>(t);
    std::cout << "\nBtree with t=" << test.get_t() << " is created.\n";
    help_message();
    while(true) {
        std::cout << "Enter next command: ";
        std::string command;
        std::cin >> command;
        if (command == "test_copy") {
            btree_map<int, int> copy = test;
            std::cout << "Copy of btree:\n" << copy;
        }
        else if (command == "is_empty")
            if (test.empty())
                std::cout << "Tree is empty\n";
            else
                std::cout << "Tree is not empty\n";
        else if (command == "contains") {
            int key;
            std::cin >> key;
            if (test.contains(key))
                std::cout << "The element with this key is found\n";
            else
                std::cout << "The element with this key is not found\n";
        }
        else if (command == "size")
            std::cout << "Btree size is " << test.size() << "\n";
        else if (command == "clear")
            test.clear();
        else if (command == "add") {
            int key, value;
            std::cin >> key >> value;
            test.insert(key, value);
        }
        else if (command == "print") {
            int key;
            std::cin >> key;
            try {
                std::cout << "Your value: " << test[key] << "\n";
            }
            catch (std::out_of_range& e) {
                std::cout << e.what() << "\n";
            }
        }
        else if (command == "delete") {
            int key;
            std::cin >> key;
            test.erase(key);
        }
        else if (command == "test_it") {
            btree_map<int, int>::iterator it = test.begin();
            do {
                std::cout << (*it) << " ";
                it++;
            } while (it != test.begin());
            std::cout << "\n";
            it = test.end();
            do {
                std::cout << (*it) << " ";
                it--;
            } while (it != test.end());
            std::cout << "\n";
        }
        else if (command == "find") {
            int key;
            std::cin >> key;
            try {
                btree_map<int, int>::iterator it = test.find(key);
                std::cout << "Your value: " << (*it) << "\n";
            }
            catch (std::out_of_range& e) {
                std::cout << e.what() << "\n";
            }
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
    std::cout << "Test of btree is ended. Goodbye.\n";
    return 0;
}
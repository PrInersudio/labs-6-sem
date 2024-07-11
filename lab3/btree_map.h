#ifndef __BTREE_MAP__
#define __BTREE_MAP__


#include <stdexcept>
#include <string>
#include <deque>
#include <stack>
#include <queue>
#include <iterator>
#include <ostream>
#include <initializer_list>


template<typename comparable_type>
class comparator {
    public:
        bool operator () (comparable_type value1, comparable_type value2) {
            return value1 < value2;
        }
};
// #define key_type int
// #define value_type int
// #define comparator_type comparator<int>
template<typename key_type, typename value_type, typename comparator_type = comparator<key_type>>
class btree_map {
    
    
    private:

        struct element {
                key_type key;
                value_type value;
                element(key_type key, value_type value) {
                    this->key = key;
                    this->value = value;
                }
                element(const element& original) {
                    this->key = original.key;
                    this->value = original.value;
                }
                friend std::ostream& operator << (std::ostream& os, const element& el) {
                    return os << "(" << std::to_string(el.key) << "," <<    std::to_string(el.value) << ")";                     
                }
        };
        
        struct node {
            std::deque<element> elements;
            std::deque<node*> children;
            int binary_search(key_type key) {
                comparator_type compare;
                int low = 0;
                int high = elements.size() - 1;
                while (low <= high) {
                    int mid = (low + high) / 2;
                    if (compare(elements[mid].key, key))
                        low = mid + 1;
                    else if (compare(key, elements[mid].key))
                        high = mid - 1;
                    else
                        return mid;
                }
                return low;
            }
            int insert(element new_element) {
                int index = binary_search(new_element.key);
                elements.insert(elements.begin() + index, new_element);
                children.insert(children.begin() + index, nullptr);
                return index;
            }
        };

        node* root;
        unsigned t;

        void divide_node(node* parent, node* filled_node) {
            int median_index = filled_node->elements.size() / 2 - 1;
            node* left_node =  new node;
            node* right_node = new node;
            for (int i = 0; i < median_index; i++) {
                left_node->elements.push_back(filled_node->elements[i]);
                left_node->children.push_back(filled_node->children[i]);
            }
            int left_node_index = parent->insert(filled_node->elements[median_index]);
            left_node->children.push_back(filled_node->children[median_index]);
            for (int i = median_index + 1; i < filled_node->elements.size(); i++) {
                right_node->elements.push_back(filled_node->elements[i]);
                right_node->children.push_back(filled_node->children[i]);
            }
            right_node->children.push_back(filled_node->children.back());
            parent->children[left_node_index] = left_node;
            parent->children[left_node_index+1] = right_node;
            delete filled_node;
        }

        void divide_root() {
            node* new_root = new node;
            new_root->children.push_back(root);
            divide_node(new_root, root);
            root = new_root;
        }

        void move(element& parent, node* node_to_incert, node* node_to_take, bool is_right_brother) {
            if (is_right_brother) {
                node_to_incert->elements.push_back(parent);
                parent = node_to_take->elements.front();
                node_to_take->elements.pop_front();
            }
            else {
                node_to_incert->elements.push_front(parent);
                parent = node_to_take->elements.back();
                node_to_take->elements.pop_back();
            }
        }

        void merge(node* parent, int parent_element_index) {
            node* left_brother = parent->children[parent_element_index];
            node* right_brother = parent->children[parent_element_index + 1];
            left_brother->elements.push_back(parent->elements[parent_element_index]);
            for (int i = 0; i < right_brother->elements.size(); i++)
                left_brother->elements.push_back(right_brother->elements[i]);
            for (int i = 0; i < right_brother->children.size(); i++)
                left_brother->children.push_back(right_brother->children[i]);
            delete right_brother;
            parent->elements.erase(parent->elements.begin() + parent_element_index);
            parent->children.erase(parent->children.begin() + (parent_element_index + 1));
            if (parent->elements.size() == 0) {
                delete root;
                root = left_brother;
            }
        }

        void copy_subtree(node*& new_node, node* original_node) {
            if (original_node == nullptr) return;
            new_node =  new node;
            new_node->elements = original_node->elements;
            for (int i = 0; i < original_node->children.size(); i++) {
                new_node->children.push_back(nullptr);
                copy_subtree(new_node->children.back(), original_node->children[i]);
            }
        }

        static void subtree_to_stream(std::ostream& os, node* current_node, int quan_of_tabs) {
            for (int i = 0; i < quan_of_tabs; i++)
                os << "\t";
            for (int i = 0; i < current_node->elements.size(); i++)
                os << current_node->elements[i] << " ";
            os << "\n";
            for (int i = 0; i < current_node->children.size(); i++)
                if (current_node->children[i] != nullptr) subtree_to_stream(os, current_node->children[i], quan_of_tabs + 1);
        }

    public:

        value_type& operator [] (key_type key) {
            comparator_type compare;
            node* current_node = root;
            while(current_node != nullptr) {
                int current_element_index = current_node->binary_search(key);
                if (current_element_index == current_node->elements.size())
                    current_node = current_node->children.back();
                else if (!((compare(key, current_node->elements[current_element_index].key))||(compare(current_node->elements[current_element_index].key, key)))) 
                    return current_node->elements[current_element_index].value;
                else
                    current_node = current_node->children[current_element_index];
            }
            throw std::out_of_range("There is no element with key " + std::to_string(key) + " in this btree");
        }

        value_type at(key_type key) {
            return (*this)[key];
        }

        void insert(key_type key, value_type value) {
            comparator_type compare;
            node* current_node = root;
            std::vector<node*> way;
            while(current_node != nullptr) {
                way.push_back(current_node);
                int current_element_index = current_node->binary_search(key);
                if (current_element_index == current_node->elements.size())
                    current_node = current_node->children.back();
                else if (!((compare(key, current_node->elements[current_element_index].key))||(compare(current_node->elements[current_element_index].key, key)))) {
                    current_node->elements[current_element_index].value = value;
                    return;
                }
                else
                    current_node = current_node->children[current_element_index];
            }
            way.back()->insert(element(key, value));
            for (int i = way.size() - 1; i > 0; i--)
                if (way[i]->elements.size() > 2 * t - 1)
                    divide_node(way[i-1], way[i]);
            if (root->elements.size() > 2 * t - 1)
                divide_root();
        }

        void erase(key_type key) {
            comparator_type compare;
            node* current_node = root;
            int current_element_index = current_node->binary_search(key);
            node* child_node = current_node->children[current_element_index];
            while(child_node != nullptr) {
                if (child_node->elements.size() == t-1) {
                    if (current_element_index != current_node->children.size() - 1) {
                        node* right_brother = current_node->children[current_element_index + 1];
                        if (right_brother->elements.size() > t-1)
                            move(current_node->elements[current_element_index], child_node, right_brother, true);
                        else
                            merge(current_node, current_element_index);
                    }
                    else {
                        node* left_brother = current_node->children[current_element_index - 1];
                        if (left_brother->elements.size() > t-1)
                            move(current_node->elements[current_element_index - 1], child_node, left_brother, false);
                        else {
                            merge(current_node, current_element_index - 1);
                            child_node = left_brother;
                        }
                    }
                }
                current_node = child_node;
                current_element_index = current_node->binary_search(key);
                child_node = current_node->children[current_element_index];
            }
            if (!((compare(key, current_node->elements[current_element_index].key))||(compare(current_node->elements[current_element_index].key, key)))) {
                current_node->elements.erase(current_node->elements.begin() + current_element_index);
                current_node->children.pop_back();
            }
        }

        btree_map(unsigned t = 2) {
            if (t < 2) throw std::invalid_argument("Minimal degree of node (parameter t) must be bigger or equal then 2");
            this->t = t;
            root = new node;
            root->children.push_back(nullptr);
        }

        void clear() {
            std::stack<node*> stack_of_nodes;
            stack_of_nodes.push(root);
            while (!stack_of_nodes.empty()) {
                node* current_node = stack_of_nodes.top();
                stack_of_nodes.pop();
                for (int i = 0; i < current_node->children.size(); i++)
                    if (current_node->children[i] != nullptr) stack_of_nodes.push(current_node->children[i]);
                delete current_node;
            }
            root = new node;
            root->children.push_back(nullptr);
        }

        btree_map(const btree_map& original) {
            t = original.t;
            copy_subtree(root, original.root);
        }

        bool empty() {
            return root->elements.empty();
        }

        ~btree_map() {
            clear();
            delete root;
            t = 0;
        }

        unsigned get_t() {
            return t;
        }

        bool contains(key_type key) {
            value_type value;
            try {
                value = (*this)[key];
            }
            catch (std::out_of_range& e) {
                return false;
            }
            return true;
        }

        class iterator : std::iterator<std::bidirectional_iterator_tag, value_type> {
            
            protected:
                node* root;
                std::stack<node*> way;
                std::stack<int> way_indexes;
                
            public:
                iterator(node* root, std::stack<node*> way, std::stack<int> way_indexes) {
                    this->root = root;
                    this->way = way;
                    this->way_indexes = way_indexes;
                }
                bool operator == (const iterator& it2) {
                    return (way.top() == it2.way.top())&&(way_indexes.top() == it2.way_indexes.top());
                }
                bool operator != (const iterator& it2) {
                    return (way.top() != it2.way.top())||(way_indexes.top() != it2.way_indexes.top());
                }
                iterator& operator ++ () {
                    way_indexes.top()++;
                    if (way_indexes.top() == way.top()->elements.size())
                        if (way.top()->children.front() != nullptr) {
                                way.push(way.top()->children.front());
                                way_indexes.top() = 0;
                                way_indexes.push(0);
                            }
                        else {
                            way_indexes.pop();
                            way.pop();
                            way_indexes.top()++;
                            while ((!way.empty())&&(way_indexes.top() == way.top()->children.size())) {
                                way_indexes.pop();
                                way.pop();
                                if (!way_indexes.empty()) way_indexes.top()++;
                            }
                            if (way.empty()) {
                                way.push(root);
                                way_indexes.top() = 0;
                                return *this;
                            }
                            way.push(way.top()->children[way_indexes.top()]);
                            way_indexes.push(0);
                        }
                    return *this;
                }
                value_type& operator * () {
                    return way.top()->elements[way_indexes.top()].value;
                }
                iterator(const iterator& original) {
                    this->root = original.root;
                    this->way = original.way;
                    this->way_indexes = original.way_indexes;
                }
                iterator& operator -- () {
                    way_indexes.top()--;
                    if (way_indexes.top() == -1) {
                        way.pop();
                        way_indexes.pop();
                        if (!way_indexes.empty()) way_indexes.top()--;
                        if (way.empty())
                            way.push(root);
                        else if (way_indexes.top() == -1) {
                            way_indexes.top() = way.top()->elements.size() - 1;
                            return *this;
                        }
                        else
                            way.push(way.top()->children[way_indexes.top()]);
                        while (way.top()->children.back() != nullptr) {
                            way_indexes.push(way.top()->children.size()-1);
                            way.push(way.top()->children.back());
                        }
                        way_indexes.push(way.top()->elements.size()-1);
                    }
                    return *this;
                }

                iterator& operator++ (int) {
                    return (++(*this));
                }

                iterator& operator-- (int) {
                    return (--(*this));
                }

                key_type getKey() {
                    return way.top()->elements[way_indexes.top()].key;
                }

                value_type getValue() {
                    return way.top()->elements[way_indexes.top()].value;
                }

                value_type& getValueRef() {
                    return way.top()->elements[way_indexes.top()].value;
                }

                value_type* operator -> () {
                    return &(way.top()->elements[way_indexes.top()].value);
                }
        };

        typedef iterator const_iterator;

        iterator find(key_type key) {
            std::stack<node*> way;
            std::stack<int> way_indexes;
            comparator_type compare;
            node* current_node = root;
            while(current_node != nullptr) {
                way.push(current_node);
                int current_element_index = current_node->binary_search(key);
                way_indexes.push(current_element_index);
                if (current_element_index == current_node->elements.size())
                    current_node = current_node->children.back();
                else if (!((compare(key, current_node->elements[current_element_index].key))||(compare(current_node->elements[current_element_index].key, key))))
                    return iterator(root, way, way_indexes);
                else
                    current_node = current_node->children[current_element_index];
            }
            throw std::out_of_range("There is no element with key " + std::to_string(key) + " in this btree");
        }

        iterator begin() {
            std::stack<node*> way;
            way.push(root);
            std::stack<int> way_indexes;
            way_indexes.push(0);
            return iterator(root, way, way_indexes);
        }

        iterator end() {
            return (begin()--);
        }

        const_iterator cbegin() {
            return const_iterator(begin());
        }

        const_iterator cend() {
            return const_iterator(end());
        }

        std::size_t size() {
            std::size_t size = 0;
            std::stack<node*> nodes;
            nodes.push(root);
            while (!nodes.empty()) {
                node* current_node = nodes.top();
                nodes.pop();
                size += current_node->elements.size();
                for (int i = 0; i < current_node->children.size(); i++)
                    if (current_node->children[i] != nullptr)
                        nodes.push(current_node->children[i]);
            }
            return size;
        }

        friend std::ostream& operator << (std::ostream& os, const btree_map& btree) {
            subtree_to_stream(os, btree.root, 0);
            return os;
        }

        void erase(iterator it) {
            erase(it.getKey());
        }
};

#endif
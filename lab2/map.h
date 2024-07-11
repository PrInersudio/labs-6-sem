#ifndef MAP
#define MAP

#include <stdexcept>
#include<ostream>

template<typename comparable_type>
class comparator {
    public:
        bool operator () (comparable_type value1, comparable_type value2) {
            return value1 < value2;
        }
};

template<typename Key, typename Value, typename Comparator = comparator<Key>>
class map {
    
    private:

        struct node_data {
            Key key;
            Value value;
            node_data(Key key, Value value) {
                this->key=key;
                this->value=value;
            }
            node_data(const node_data& original) {
                this->key=original.key;
                this->value=original.value;
            }
        };

        enum node_color {black, red};

        struct Node {
            node_data* data;
            node_color color;
            Node* parent;
            Node* left_child;
            Node* right_child;
            Node(node_data* data, node_color color, Node* parent, Node* left_child, Node* right_child) {
                this->data = data;
                this->color = color;
                this->parent = parent;
                this->left_child = left_child;
                this->right_child = right_child;
            }
            Node(const Node& original) {
                this->data = original.data == nullptr ? nullptr : new node_data(*original.data);
                this->color = original.color;
                this->parent = original.parent;
                this->left_child = original.left_child;
                this->right_child = original.right_child;
            }
            Node(Node* parent) {
                this->data = nullptr;
                this->color = black;
                this->parent = parent;
                this->left_child = nullptr;
                this->right_child = nullptr;
            }
            Node* grandparent() {
                return parent==nullptr ? nullptr : parent->parent;
            }
            Node* uncle() {
                return grandparent()==nullptr ? nullptr : (grandparent()->right_child==parent ? grandparent()->left_child : grandparent()->right_child);
            }
            Node* sibling() {
                return parent == nullptr ? nullptr : (parent->left_child == this ? parent->right_child : parent->left_child);
            }
            void exchangeData(Node* X) {
                node_data* temp = data;
                data = X->data;
                X->data = temp;
            }
            ~Node() {
                if (data != nullptr) delete data;
            }
        };

        Node* root;

        void left_rotation(Node* X) {
            Node*& hanging_point = X == root ? root : (X->parent->left_child == X ? X->parent->left_child : X->parent->right_child);
            Node* original_hanging_point = hanging_point;
            hanging_point = hanging_point->right_child;
            hanging_point->parent = original_hanging_point->parent;
            original_hanging_point->right_child = hanging_point->left_child;
            original_hanging_point->right_child->parent = original_hanging_point;
            hanging_point->left_child = original_hanging_point;
            original_hanging_point->parent = hanging_point;
        }

        void right_rotation(Node* X) {
            Node*& hanging_point = X == root ? root : (X->parent->left_child == X ? X->parent->left_child : X->parent->right_child);
            Node* original_hanging_point = hanging_point;
            hanging_point = hanging_point->left_child;
            hanging_point->parent = original_hanging_point->parent;
            original_hanging_point->left_child = hanging_point->right_child;
            original_hanging_point->left_child->parent = original_hanging_point;
            hanging_point->right_child = original_hanging_point;
            original_hanging_point->parent = hanging_point;
        }

        void add_balance(Node* X) {
            if (X == root) {
                X->color = black;
            }
            else if (X->parent->color == black) {
                return;
            }
            else {
                if ((X->uncle()->color == red)&&(X->parent->color == red)) {
                    X->uncle()->color = black;
                    X->parent->color = black;
                    X->grandparent()->color = red;
                    add_balance(X->grandparent());
                }
                else {
                    Node* original_grandparent = X->grandparent();
                    if ((X->grandparent()->left_child == X->parent)&&(X->parent->right_child == X)) {
                        left_rotation(X->parent);
                    }
                    else if ((X->grandparent()->right_child == X->parent)&&(X->parent->left_child == X)) {
                        right_rotation(X->parent);
                    }
                    if (X->parent->left_child==X) {
                        right_rotation(original_grandparent);
                    }
                    else {
                        left_rotation(original_grandparent);
                    }
                    original_grandparent->color = red;
                    original_grandparent->parent->color = black;
                }
            }
        }

        void erase_balance(Node* X) {
            if (X == root) return;
            if (X->sibling()->color == red) {
                X->sibling()->color = black;
                X->parent->color = red;
                X->parent->left_child == X ? left_rotation(X->parent) : right_rotation(X->parent);
            }
            else if ((X->parent->color == black)&&(X->sibling()->left_child->color == black)&&(X->sibling()->right_child->color == black)) {
                X->sibling()->color = red;
                erase_balance(X->parent);
                return;
            }
            if ((X->parent->color == red)&&(X->sibling()->left_child->color == black)&&(X->sibling()->right_child->color == black)) {
                X->sibling()->color = red;
                X->parent->color = black;
            }
            else {
                if (
                    (X == X->parent->left_child) &&
                    (X->sibling()->left_child->color == red) &&
                    (X->sibling()->right_child->color == black)
                ) {
                    X->sibling()->left_child->color = black;
                    X->sibling()->color = red;
                    left_rotation(X->sibling());
                }
                else if (
                    (X == X->parent->right_child) &&
                    (X->sibling()->right_child->color == red) &&
                    (X->sibling()->left_child->color == black)
                ) {
                    X->sibling()->right_child->color = black;
                    X->sibling()->color = red;
                    right_rotation(X->sibling());
                }
                X->sibling()->color = X->parent->color;
                X->parent->color = black;
                if (X == X->parent->left_child) {
                    X->sibling()->right_child->color = black;
                    left_rotation(X->parent);
                }
                else {
                    X->sibling()->left_child->color = black;
                    right_rotation(X->parent);
                }
            }
        }

        void copy_subtree(Node* parent, Node*& new_node, Node*& original_node) {
            new_node = new Node(*original_node);
            new_node->parent = parent;
            if (original_node->left_child != nullptr) copy_subtree(new_node, new_node->left_child, original_node->left_child);
            if (original_node->right_child != nullptr) copy_subtree(new_node, new_node->right_child, original_node->right_child);
        }

        void delete_subtree(Node* subtree_root) {
            if (subtree_root == nullptr) return;
            delete_subtree(subtree_root->left_child);
            delete_subtree(subtree_root->right_child);
            delete subtree_root;
        }

        Node* find_node(Key key) {
            Node* X = root;
            Comparator compare;
            while (X->data != nullptr) {
                if ((!compare(key, X->data->key))&&(!compare(X->data->key, key))) {
                    break;
                }
                else if (compare(key, X->data->key)) {
                    X = X->left_child;
                }
                else {
                    X = X->right_child;
                }
            }
            return X;
        }

        static Node* the_leftest_not_null_decendant(Node* X) {
            while (X->left_child->data != nullptr) X = X->left_child;
            return X;
        }

        static Node* the_rightest_not_null_decendant(Node* X) {
            while (X->right_child->data != nullptr) X = X->right_child;
            return X;
        }

        static void subtree_to_string(std::ostream& os, Node* node, unsigned num_of_tabs = 0, const char* node_pos = "root: ") {
            if (node->data == nullptr) return;
            for (unsigned i = 0; i < num_of_tabs; i++) os << "\t";
            os << node_pos << "(" << node->data->key << "," << node->data->value << "," << (node->color == red ? "red" : "black") << ")" << std::endl;
            subtree_to_string(os, node->left_child, num_of_tabs+1, "left: ");
            subtree_to_string(os, node->right_child, num_of_tabs+1, "right: ");
        }

        Node* add(Key key, Value value) {
            Node* X = find_node(key);
            if (X->data != nullptr) {
                X->data->value = value;
                return X;
            }
            X->data = new node_data(key, value);
            X->color = red;
            X->left_child = new Node(X);
            X->right_child = new Node(X);
            add_balance(X);
            return X;
        }

        std::size_t subtree_size(Node* node) {
            if (node->data == nullptr) return 0;
            return subtree_size(node->left_child) + subtree_size(node->right_child) + 1;
        }

    public:

        map() {
            root = new Node(nullptr);
        }

        map(map& original) {
            copy_subtree(nullptr, root, original.root);
        }

        ~map() {
            delete_subtree(root);
        }

        Value& at(Key key) {
            Node* node = find_node(key);
            if(node->data == nullptr) {
                throw std::out_of_range("There is no element with key " + std::to_string(key) + " in this map");
            }
            return node->data->value;
        }

        Value& operator [] (Key key) {
            return at(key);
        }

        void emplace(Key key, Value value) {
            add(key, value);
        }

       void erase(Key key) {
            Node* X = find_node(key);
            if (X->data == nullptr) return;
            while ((X->left_child->data != nullptr)&&(X->right_child->data != nullptr)) {
                Node* descendant = X->left_child;
                while (descendant->right_child->data != nullptr) descendant = descendant->right_child;
                X->exchangeData(descendant);
                X = descendant;
            }
            Node* parent = X->parent;
            if (X->color == red) {
                parent->left_child == X ? parent->left_child = new Node(parent) : parent->right_child = new Node(parent);
                delete_subtree(X);
            }
            else {
                Node* remaing_child;
                if (X->right_child->data == nullptr) {
                    remaing_child = X->left_child;
                    delete X->right_child;
                    delete X;
                }
                else {
                    remaing_child = X->right_child;
                    delete X->left_child;
                    delete X;
                }
                remaing_child->parent = parent;
                parent->left_child == X ? parent->left_child = remaing_child : parent->right_child = remaing_child;
                remaing_child->color = black;
                if (remaing_child->data == nullptr) erase_balance(remaing_child);
            }
       }

       bool empty() {
            if (root->data == nullptr) return true;
            return false;
       }

       void clear() {
            delete_subtree(root);
            root = new Node(nullptr);
       }

        class iterator : std::iterator<std::bidirectional_iterator_tag, Value> {
            
            private:
                Node* node;
                Node* leftest_node;
                Node* rightest_node;
                
            public:
                iterator(Node* node, Node* leftest_node, Node* rightest_node) {
                    this->node = node;
                    this->leftest_node = leftest_node;
                    this->rightest_node = rightest_node;
                }
                bool operator == (const iterator& it2) {
                    return this->node == it2.node;
                }
                bool operator != (const iterator& it2) {
                    return this->node != it2.node;
                }
                iterator& operator ++ () {
                    if (node == rightest_node) node = node->right_child;
                    else if (node->right_child->data != nullptr) node = the_leftest_not_null_decendant(node->right_child);
                    else if (node == node->parent->left_child) node = node->parent;
                    else if(node->parent == node->grandparent()->left_child) node = node->grandparent();
                    else node = node->grandparent()->parent;
                    return *this;
                }
                Value& operator * () {
                    return node->data->value;
                }
                iterator(const iterator& original) {
                    this->node = original.node;
                    this->leftest_node = original.leftest_node;
                    this->rightest_node = original.rightest_node;
                }
                iterator& operator -- () {
                    if (node->parent == rightest_node) node = rightest_node;
                    else if (node == leftest_node) node = rightest_node->right_child;
                    else if (node->left_child->data != nullptr) node = the_rightest_not_null_decendant(node->left_child);
                    else if (node == node->parent->right_child) node = node->parent;
                    else if(node->parent == node->grandparent()->right_child) node = node->grandparent();
                    else node = node->grandparent()->parent;
                    return *this;
                }

                iterator& operator++ (int) {
                    return (++(*this));
                }

                iterator& operator-- (int) {
                    return (--(*this));
                }

                Key getKey() {
                    return node->data->key;
                }

                Value& value() {
                    return node->data->value;
                }

                Value* operator -> () {
                    return &(node->data->value);
                }
        };

        typedef iterator const_iterator;

        friend std::ostream& operator<<(std::ostream& os, map Map) {
            subtree_to_string(os, Map.root);
            return os;
        }

        iterator begin() {
            Node* leftest_node = the_leftest_not_null_decendant(root);
            return iterator(leftest_node, leftest_node, the_rightest_not_null_decendant(root));
        }

        const_iterator cbegin() {
            return begin();
        }

        iterator end() {
            Node* rightest_node = the_rightest_not_null_decendant(root);
            return iterator(rightest_node->right_child, the_leftest_not_null_decendant(root), rightest_node);
        }

        const_iterator cend() {
            return end();
        }

        bool contains(Key key) {
            if (find_node(key)->data == nullptr) return false;
            return true;
        }

        iterator emplace_hint(Key key, Value value) {
            return iterator(add(key, value), the_leftest_not_null_decendant(root), the_rightest_not_null_decendant(root));
        }

        iterator find(Key key) {
            Node* node = find_node(key);
            if(node->data == nullptr) {
                throw std::out_of_range("There is no element with key " + std::to_string(key) + " in this map");
            }
            return iterator(node, the_leftest_not_null_decendant(root), the_rightest_not_null_decendant(root));
        }

        std::size_t size() {
            return subtree_size(root);
        }
};

#endif
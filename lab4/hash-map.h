#include<functional>
#include<vector>
#include<list>
#include<math.h>
#include<ostream>
#include<iterator>
// #define Key int
// #define Value int
// #define hash_func std::hash<Key>
template<typename Key, typename Value, typename hash_func = std::hash<Key>>
class hash_map {

private:
    struct Element {
        Key key;
        Value value;
        Element(Key key) {
            this->key = key;
        }
    };
    std::vector<std::list<Element>> hash_table;
    std::size_t elements_quantity;
    std::size_t lists_quantity;
    double load_level;
    std::size_t find_closest_bigger_prime(std::size_t number) {
        if (number <= 2) return 2;
        for (;;number++) {
            bool divider_found = false;
            for (int i = 2; i <= (std::size_t)sqrt(number); i++)
                if (number % i == 0) {
                    divider_found = true;
                    break;
                }
            if (!divider_found) break;
        }
        return number;
    }
    typename std::list<Element>::iterator find_element(Key& key) {
        hash_func hasher;
        std::size_t hash = hasher(key) % lists_quantity;
        auto it = hash_table[hash].begin();
        for (; it != hash_table[hash].end(); ++it)
            if (it->key == key) break;
        if (it == hash_table[hash].end()) {
            hash_table[hash].push_back(Element(key));
            elements_quantity++;
            if (load_factor() > load_level) {
                rehash(2 * lists_quantity + 1);
                hash = hasher(key) % lists_quantity;
            }
            it = --hash_table[hash].end();
        }
        return it;
    }
public:
    hash_map(double load_level = 2.0) {
        this->elements_quantity = 0;
        this->lists_quantity = 257;
        this->load_level = load_level;
        for (std::size_t i = 0; i < lists_quantity; i++)
            hash_table.push_back(std::list<Element>());
    }
    void rehash(std::size_t new_lists_quantity) {
        do {
            new_lists_quantity = find_closest_bigger_prime(new_lists_quantity);
            if(new_lists_quantity == lists_quantity) return;
            std::list<Element> all_elements;
            for (int i = 0; i < lists_quantity; i++)
                for (auto it = hash_table[i].begin(); it != hash_table[i].end(); ++it)
                    all_elements.push_back(*it);
            hash_table.clear();
            for (int i = 0; i < new_lists_quantity; i++)
                hash_table.push_back(std::list<Element>());
            hash_func hasher;
            for (auto it = all_elements.begin(); it != all_elements.end(); ++it)
                hash_table[hasher(it->key) % new_lists_quantity].push_back(*it);
            lists_quantity = new_lists_quantity++;
        } while (load_factor() > load_level);
    }
    void emplace(Key key, Value value) {
        find_element(key)->value = value;
    }
    void clear() {
        hash_table.clear();
        elements_quantity = 0;
        lists_quantity = 257;
        for (std::size_t i = 0; i < lists_quantity; i++)
            hash_table.push_back(std::list<Element>());
    }
    Value& operator[](Key& key) {
        return find_element(key)->value;
    }
    Value& at(Key& key) {
        return find_element(key)->value;
    }
    void erase(Key& key) {
        hash_func hasher;
        std::size_t hash = hasher(key) % lists_quantity;
        hash_table[hash].erase(find_element(key));
        elements_quantity--;
    }
    std::size_t size() {
        return elements_quantity;
    }
    double max_load_factor() {
        return load_level;
    }
    void max_load_factor(double new_load_level) {
        load_level = new_load_level;
        if (load_factor() > load_level)
                rehash(2 * lists_quantity + 1);
    }
    double load_factor() {
        return (double)elements_quantity / (double)lists_quantity;
    }
    class iterator : std::iterator<std::bidirectional_iterator_tag, Value> {
    
    private:
        typename std::list<Element>::iterator list_it;
        std::size_t hash;
        std::vector<std::list<Element>>* hash_table;
        std::size_t lists_quantity;
        
    public:
        iterator(typename std::list<Element>::iterator list_it, std::size_t hash,  std::vector<std::list<Element>>* hash_table, std::size_t lists_quantity) {
            this->list_it = list_it;
            this->hash = hash;
            this->hash_table = hash_table;
            this->lists_quantity = lists_quantity;
        }
        bool operator == (const iterator& it2) {
            return this->list_it == it2.list_it;
        }
        bool operator != (const iterator& it2) {
            return this->list_it != it2.list_it;
        }
        iterator& operator ++ () {
            if ((++list_it == (*hash_table)[hash].end())&&(hash != lists_quantity - 1)) {
                ++hash;
                while(((*hash_table)[hash].empty())&&(hash < lists_quantity - 1)) ++hash;
                list_it = (*hash_table)[hash].begin();
            }
            return *this;
        }
        Value& operator * () {
            return list_it->value;
        }
        iterator(const iterator& original) {
            this->list_it = original.list_it;
            this->hash = original.hash;
            this->hash_table = original.hash_table;
            this->lists_quantity = original.lists_quantity;
        }
        iterator& operator -- () {
            if (list_it == (*hash_table)[hash].begin()) {
                --hash;
                while(((*hash_table)[hash].empty())&&(hash > 0)) --hash;
                list_it = (*hash_table)[hash].end();
            }
            --list_it;
            return *this;
        }
        
        iterator operator++ (int) {
            iterator old_it = *this;
            ++(*this);
            return old_it;
        }
        
        iterator operator-- (int) {
            iterator old_it = *this;
            --(*this);
            return old_it;
        }
        
        Key key() {
            return list_it->key;
        }
        
        Value& value() {
            return list_it->value;
        }
        
        Value* operator -> () {
            return &(list_it->value);
        }
    };
    typedef iterator const_iterator;
    iterator begin() {
        return iterator(hash_table[0].begin(), 0, &hash_table, lists_quantity);
    }
    std::size_t bucket(Key& key) {
        hash_func hasher;
        return hasher(key) % lists_quantity;
    }
    std::size_t bucket_count() {
        return lists_quantity;
    }
    std::size_t bucket_size(size_t nbucket) {
        return hash_table[nbucket].size();
    }
    const_iterator cbegin() {
        return begin();
    }
    iterator end() {
        return iterator(hash_table.back().end(), lists_quantity - 1, &hash_table, lists_quantity);
    }
    const_iterator cend() {
        return end();
    }
    bool contains(Key& key) {
        hash_func hasher;
        std::size_t hash = hasher(key) % lists_quantity;
        for (auto it = hash_table[hash].begin(); it != hash_table[hash].end(); ++it)
            if (it->key == key) return true;
        return false;
    }
    bool empty() {
        return elements_quantity == 0;
    }
    hash_map(const hash_map& original) {
        this->hash_table = original.hash_table;
        this->elements_quantity = original.elements_quantity;
        this->lists_quantity = original.lists_quantity;
        this->load_level= original.load_level;
    }
    friend std::ostream& operator<<(std::ostream& os, hash_map& map) {
        for (int i = 0; i < map.lists_quantity; i++) {
            os << i << ":";
            for (auto it = map.hash_table[i].begin(); it != map.hash_table[i].end(); ++it)
                os << " (" << it->key << ", " << it->value << ")";
            os << std::endl;
        }
        return os;
    }
    iterator find(Key& key) {
        hash_func hasher;
        return iterator(find_element(key), hasher(key), &hash_table, lists_quantity);
    }
};
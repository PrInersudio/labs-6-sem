#include"substring.h"
#include "map.h"
#define max(a,b) (a < b ? b : a)

// по сути  тот же самый поиск перебором, но вместо сравнения подстроки и образца посимвольно считаем строки числами в системе счисления размерности, равной мощности алфавита и сравниваим их. Для эффективности берём числа по модулю простого числа.
std::vector<std::size_t> RabinKarp(std::string& String, std::string& Example) {
    std::vector<std::size_t> result;
    int d_m = 1;
    for (std::size_t i = 1; i < Example.length(); i++) d_m *= char_alphabet_size;
    d_m %= RabinKarp_module;
    int example_substring_hash, current_substring_hash;
    example_substring_hash = current_substring_hash = 0;
    for (std::size_t i = 0; i < Example.length(); i++) {
        example_substring_hash = char_alphabet_size * example_substring_hash + (unsigned)Example[i];
        current_substring_hash = char_alphabet_size * current_substring_hash + (unsigned)String[i];
    }
    example_substring_hash %= RabinKarp_module;
    current_substring_hash %= RabinKarp_module;
    std::size_t s;
    for (s = 0; s <= String.length() - Example.length(); s++) {
        if (example_substring_hash == current_substring_hash) {
            if (Example == String.substr(s, Example.length()))
                result.push_back(s);
        }
        current_substring_hash = (char_alphabet_size * (current_substring_hash - d_m * (int)String[s]) + (int)String[s+Example.length()])%RabinKarp_module;
        while (current_substring_hash < 0) current_substring_hash+= RabinKarp_module;
        
    }
    if (example_substring_hash == current_substring_hash)
            if (Example == String.substr(s, Example.length()))
                result.push_back(s);
    return result;
}

// равна длине максимального суффикса равного префиксу в подстроке [0б m]
std::size_t* prefix_function(std::string& String) {
    std::size_t* prefix_func = new std::size_t[String.length()];
    std::size_t k = prefix_func[0] = 0;
    for (std::size_t i = 1; i < String.length(); i++) {
        while((k > 0) && (String[k] != String[i])) k--;
        if (String[k] == String[i]) k++;
        prefix_func[i] = k;
    }
    return prefix_func;
}

// перевёрнутая prefix_function; по сути, если suffix_func[i] = j, то начиная с String.length() - 1 - i начинается повтор суффикса длины j
std::size_t* suffix_function(std::string& String) {
    std::size_t* suffix_func = new std::size_t[String.length()];
    std::size_t k = suffix_func[0] = 0;
    for (std::size_t i = String.length() - 2; i > 0; i--) {
        while((k > 0) && (String[String.length() - 1 - k] != String[i])) k--;
        if (String[String.length() - 1 - k] == String[i]) k++;
        suffix_func[String.length() - 1 - i] = k;
    }
    while((k > 0) && (String[String.length() - 1 - k] != String[0])) k--;
    if (String[String.length() - 1 - k] == String[0]) k++;
    suffix_func[String.length() - 1] = k;
    return suffix_func;
}

// считает для всех суффиксов смещение до ближайшего повтора, если повтора нет, то равна длине строки. Начинается с пустого суффикса, для которого значение считаем равным 1
std::size_t* count_suffix_table(std::string& String) {
    std::size_t* suffix_table = new std::size_t[String.length()+1];
    std::size_t* prefix_func = prefix_function(String);
    for (std::size_t i = 0; i < String.length() + 1; i++) suffix_table[i] = String.length() - prefix_func[String.length() - 1]; // верхняя оценка таблицы суффиксов
    delete[] prefix_func;
    std::size_t* suffix_func = suffix_function(String);
    for (int i = 0; i < String.length(); i++) {
        // index = String.length() - suffix_func[i]. По сути это означает то, что если index = j, то c String.length() - 1 - i начинается повтор суффикса, начиаещегося с j-го символа
        std::size_t index = String.length() - suffix_func[i];
        // shift[i] по сути является смещением начала повтора суффикса относительно конца строки, концом которого являтся i-ый символ
        std::size_t shift = i - suffix_func[i] + 1;
        // так как index является номером первого символа суффикса, у которого есть повтор, а shift смещением первого символа этого повтора, то методом ниже мы и получаем искомую таблицу
        if (suffix_table[index] > shift) suffix_table[index] = shift; 
    }
    delete[] suffix_func;
    return suffix_table;
}

// индекс последней встечи символа в строке
std::size_t* count_stop_table(std::string& String) {
    std::size_t* stop_table = new std::size_t[char_alphabet_size];
    for (int i = 0; i < char_alphabet_size; i++) stop_table[i] = 0;
    for (std::size_t i = 0; i < String.size(); i++) stop_table[(int)String[i] + char_alphabet_size / 2] = i;
    return stop_table;
}

// модификация обычного перебора, где мы смещаеся на max(j - stop_table[String[i+j], suffix_table[j+1]), где j -  номер первого не совпавшего символа; проходим справа-налево
std::vector<std::size_t> BoyerMoore(std::string& String, std::string& Example) {
    std::vector<std::size_t> result;
    std::size_t* suffix_table = count_suffix_table(Example);
    std::size_t* stop_table = count_stop_table(Example);
    for (std::size_t i = 0; i <= String.length() - Example.length() + 1;) {
        int j = Example.length() - 1;
        int delta_stop;
        while ((j>=0)&&(Example[j] == String[i+j])) j--; 
        if (j == -1) {
            result.push_back(i);
            delta_stop = 1;
        }
        else delta_stop = j - stop_table[(int)String[i+j] + char_alphabet_size / 2];
        int delta_suffix = (int)suffix_table[j+1];
        i += max(delta_stop, delta_suffix);
    }

    delete[] suffix_table;
    delete[] stop_table;

    return result;
}

// объединяем образец и строку, считаем для общей строки префиксную функцию; если значение совпало с длиной образца, добавляем в ответ
std::vector<std::size_t> KnuthMorrisPratt(std::string& String, std::string& Example) {
    std::vector<std::size_t> result;
    std::size_t* prefix_func = prefix_function(Example);
    std::size_t k = 0;
    for (std::size_t i = 0; i < String.length(); i++) {
        while((k > 0) && (String[i] != Example[k])) k = prefix_func[k-1];
        if (String[i] == Example[k]) k++;
        if (k == Example.length()) {
            result.push_back(i - Example.length() + 1);
            k = prefix_func[k-1];
        }
    }
    delete[] prefix_func;
    return result;
}

class SuffixAutomat {
    private:
        struct Node {
            map<char, Node*> children;
            Node* parent;
            char way_to_parent_marker;
            Node* suffix_link;
            Node* fine_suffix_link;
            int end_of_str;
            Node(Node* parent, char way_to_parent_marker) {
                this->parent = parent;
                this->way_to_parent_marker = way_to_parent_marker;
                this->suffix_link = nullptr;
                this->end_of_str = -1;
                this->fine_suffix_link = nullptr;
            }
        };
        Node* root;
        int str_quantity;
        std::vector<std::size_t> str_lengths;
        Node* getSuffixLink(Node* node) {
            if (node->suffix_link == nullptr)
                if ((node == root)||(node->parent == root))
                    node->suffix_link = root;
                else 
                    node->suffix_link = move(getSuffixLink(node->parent), node->way_to_parent_marker);
            return node->suffix_link;
        }
        Node* move(Node* node, char next_char) {
            if (node->children.contains(next_char)) return node->children[next_char];
            if (node == root) return root;
            return move(getSuffixLink(node), next_char);
        }
        Node* getFineSuffixLink(Node* node) {
            if (node->fine_suffix_link == nullptr) {
                Node* suffix_link = getSuffixLink(node);
                if (suffix_link == root)
                    node->fine_suffix_link = root;
                else
                    node->fine_suffix_link = node->end_of_str != -1 ? suffix_link : getSuffixLink(suffix_link);
            }
            return node->fine_suffix_link;
        }
        static void subtree_to_string(std::ostream& os, Node* node) {
            os << node->way_to_parent_marker << std::endl << node->children;
            for (auto it = node->children.begin(); it != node->children.end(); ++it) subtree_to_string(os, *it);
        }
    public:
        SuffixAutomat() {
            root = new Node(nullptr, '\0');
            str_quantity = 0;
        }
        void add(std::string str) {
            Node* node = root;
            for (int i = 0; i < str.length(); i++) {
                if (node->children.contains(str[i]))
                    node = node->children[str[i]];
                else {
                    Node* next_node = new Node(node, str[i]);
                    node->children.emplace(str[i], next_node);
                    node = next_node;
                }
            }
            node->end_of_str = str_quantity++;
            str_lengths.push_back(str.length());
        }
        std::vector<std::size_t>* findSubstringPositions(std::string str) {
            std::vector<std::size_t>* result = new std::vector<std::size_t>[str_quantity];
            Node* node = root;
            for (int i = 0; i < str.length(); i++) {
                node = move(node, str[i]);
                for (Node* j = node; j != root; j = getFineSuffixLink(j))
                    if (j->end_of_str != -1) result[j->end_of_str].push_back(i+1-str_lengths[j->end_of_str]);
            }
            return result;
        }
        ~SuffixAutomat() {
            std::vector<Node*> queue;
            queue.push_back(root);
            while(!queue.empty()) {
                Node* node = queue.back();
                queue.pop_back();
                for (auto it = node->children.begin(); it != node->children.end(); ++it)
                    queue.push_back(*it);
                delete node;
            }
        }
        friend std::ostream& operator<<(std::ostream& os, SuffixAutomat automat) {
            subtree_to_string(os, automat.root);
            return os;
        } 
};

std::vector<std::size_t>* find_substrings_based_on_automat(std::vector<std::string> examples, std::string String) {
    SuffixAutomat automat;
    for (int i = 0; i < examples.size(); i++)
        automat.add(examples[i]);
    return automat.findSubstringPositions(String);
}
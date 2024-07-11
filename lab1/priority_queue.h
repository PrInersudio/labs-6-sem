#ifndef __PRIORITY_QUEUE__
#define __PRIORITY_QUEUE__

#include<vector>
template<typename value_type, typename collection_type = std::vector<value_type>>
class priority_queue {
    
    
    private:

        collection_type collection;

        void SwapElements(int index1, int index2) {
            value_type temp = collection[index1];
            collection[index1] = collection[index2];
            collection[index2] = temp;
        }
        
        void SiftDown(int start) {
            while (true) {
                int left_child_index = 2 * start + 1;
                int right_child_index = 2 * start + 2;
                int biggest_index = start;
                if ((left_child_index < collection.size()) && (collection[biggest_index] < collection[left_child_index]))
                    biggest_index = left_child_index;
                if ((right_child_index <  collection.size()) && (collection[biggest_index] < collection[right_child_index]))
                    biggest_index = right_child_index;
                if (biggest_index == start) break;
                SwapElements(start, biggest_index);
                start = biggest_index;
            }
        }

        void RestoreTree() {
            for (int i = collection.size()/2 - 1; i >= 0; i--)
                SiftDown(i);
        }

    
    public:

        bool empty() {
            return collection.empty();
        }

        std::size_t size() {
            return collection.size();
        }

        void push(value_type value) {
            collection.push_back(value);
                RestoreTree();
        }

        void pop() {
            collection[0] = collection.back();
            collection.pop_back();
            RestoreTree();
        }

        value_type top() {
            return collection[0];
        }

};

#endif
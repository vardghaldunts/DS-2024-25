#include <iostream>
#include <vector>
#include <iterator>


template<typename RandomIt, typename Cmp = std::less<typename std::iterator_traits<RandomIt>::value_type> >
void heapifyUp(RandomIt begin, RandomIt it, Cmp cmp = Cmp()) {
    if (it == begin) return;

    auto parent = begin + (std::distance(begin, it) - 1) / 2;

    if (cmp(*parent, *it)) {
        std::swap(*parent, *it);
        heapifyUp(begin, parent, cmp);
    }
}

class MaxHeap {
    std::vector<int> m_heap;

public:
    MaxHeap() = default;

    static size_t getLeftIndex(size_t i) {
        return 2 * i + 1;
    }

    static size_t getRightIndex(size_t i) {
        return 2 * i + 2;
    }

    static size_t getParentIndex(size_t i) {
        return (i - 1) / 2;
    }

    void heapifyUp(size_t i) {
        if (i == 0) return;
        size_t parent = getParentIndex(i);
        if (m_heap[i] > m_heap[parent]) {
            std::swap(m_heap[i], m_heap[parent]);
            heapifyUp(parent);
        }
    }

    void heapifyDown(size_t i) {
        size_t left = getLeftIndex(i);
        size_t right = getRightIndex(i);
        size_t largest = i;

        if (left < m_heap.size() && m_heap[left] > m_heap[largest]) {
            largest = left;
        }
        if (right < m_heap.size() && m_heap[right] > m_heap[largest]) {
            largest = right;
        }
        if (largest != i) {
            std::swap(m_heap[i], m_heap[largest]);
            heapifyDown(largest);
        }
    }

    size_t size() const {
        return m_heap.size();
    }

    int getMax() const {
        if (!m_heap.empty()) {
            return m_heap[0];
        }
        throw std::runtime_error("MaxHeap is empty");
    }

    int extractMax() {
        if (m_heap.empty()) {
            throw std::runtime_error("MaxHeap is empty");
        }
        int maxVal = m_heap[0];
        m_heap[0] = m_heap.back();
        m_heap.pop_back();
        if (!m_heap.empty()) {
            heapifyDown(0);
        }
        return maxVal;
    }

    void insert(int key) {
        m_heap.push_back(key);
        heapifyUp(m_heap.size() - 1);
    }

    void erase(size_t i) {
        if (i >= m_heap.size()) {
            throw std::runtime_error("Index out of bounds");
        }
        m_heap[i] = m_heap.back();
        m_heap.pop_back();
        if (i < m_heap.size()) {
            heapifyDown(i);
            heapifyUp(i);
        }
    }

    void print() const {
        for (const auto &i: m_heap) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    MaxHeap heap;
    std::vector<int> data = {40, 20, 30, 10, 40, 60, 50, 90, 70, 20, 55, 80, 45, 100};


    for (int value: data) {
        heap.insert(value);
    }

    std::cout << "MaxHeap after insertions: ";
    heap.print();


    std::cout << "Extracting max: " << heap.extractMax() << std::endl;
    std::cout << "Heap after extracting max: ";
    heap.print();


    return 0;
}
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

template<typename T, typename Hash = std::hash<T>>
class CA_HashTable {
private:
    std::vector<std::list<T>> m_map;
    Hash h;
    size_t bucket;

public:

    CA_HashTable(size_t size) : bucket(size), m_map(size) {}


    bool insert(const T &key) {
        size_t index = h(key) % bucket;
        auto &bucket_list = m_map[index];

        if (std::find(bucket_list.begin(), bucket_list.end(), key) != bucket_list.end()) {
            return false;
        }

        bucket_list.push_back(key);
        return true;
    }

    bool search(const T &key) const {
        size_t index = h(key) % bucket;
        const auto &bucket_list = m_map[index];
        return std::find(bucket_list.begin(), bucket_list.end(), key) != bucket_list.end();
    }


    bool remove(const T &key) {
        size_t index = h(key) % bucket;
        auto &bucket_list = m_map[index];

        auto itr = std::find(bucket_list.begin(), bucket_list.end(), key);
        if (itr != bucket_list.end()) {
            bucket_list.erase(itr);
            return true;
        }
        return false;
    }


    void print() const {
        for (size_t i = 0; i < bucket; ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const auto &key : m_map[i]) {
                std::cout << key << " ";
            }
            std::cout << std::endl;
        }
    }
};

struct CharHash {
    size_t operator()(char key) const {
        return 5 * key;
    }
};

int main() {

    CA_HashTable<char, CharHash> hashTable(8);

    std::string name = "VardGhaldunts";
    for (char ch : name) {
        hashTable.insert(ch);
    }
    std::cout << "after insert:\n";
    hashTable.print();

    std::string removeChars = "Vard";
    for (char ch : removeChars) {
        hashTable.remove(ch);
    }

    std::cout << "\nafter remove:\n";
    hashTable.print();

    std::string reinsertChars = "Va";
    for (char ch : reinsertChars) {
        hashTable.insert(ch);
    }

    std::cout << "\nafter reinsert:\n";
    hashTable.print();

    size_t total = 0;
    for (size_t i = 0; i < 8; ++i) {
        total += hashTable.search(i);
    }

    double  l = static_cast<double>(total) / 8.0;
    double suc = 1 + l / 2;

    std::cout << "\nsuccessful searche: " << suc << std::endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <bitset>
#include <functional> // For std::hash

#define BLOOM_SIZE 1000 // Size of the Bloom filter bit array
#define HASH_COUNT 3     // Number of hash functions

class BloomFilter {
private:
    std::bitset<BLOOM_SIZE> bitArray; // Bit array

    // Hash function to generate multiple hash indices
    size_t hash(const std::string &key, int seed) const {
        std::hash<std::string> hasher;
        return (hasher(key) + seed * 31) % BLOOM_SIZE;
    }

public:
    // Insert an element into the Bloom filter
    void insert(const std::string &key) {
        for (int i = 0; i < HASH_COUNT; ++i) {
            bitArray.set(hash(key, i));
        }
    }

    // Check if an element is possibly in the set
    bool contains(const std::string &key) const {
        for (int i = 0; i < HASH_COUNT; ++i) {
            if (!bitArray.test(hash(key, i))) {
                return false; // Definitely not in the set
            }
        }
        return true; // Possibly in the set (false positives possible)
    }

    // Clear the Bloom filter
    void clear() {
        bitArray.reset();
    }
};

int main() {
    BloomFilter bf;

    bf.insert("hello");
    bf.insert("world");

    std::cout << "Contains 'hello'? " << (bf.contains("hello") ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'world'? " << (bf.contains("world") ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'test'? " << (bf.contains("test") ? "Yes" : "No") << std::endl;

    return 0;
}

#pragma once
#include <cstddef>
#include <vector>


// A compact open-addressing hash map for O(1) average lookup/insert
template<typename K, typename V, size_t Capacity = 1 << 20>
class FastHashMap {
struct Entry { K key = 0; V value = nullptr; };


std::vector<Entry> table_;
size_t mask_ = Capacity - 1;


size_t hash(K k) const { return (k ^ (k >> 32)) & mask_; }


public:
FastHashMap() : table_(Capacity) {}


void insert(K key, V val) {
size_t i = hash(key);
while (table_[i].key && table_[i].key != key)
i = (i + 1) & mask_;
table_[i].key = key;
table_[i].value = val;
}


V find(K key) const {
size_t i = hash(key);
while (table_[i].key) {
if (table_[i].key == key) return table_[i].value;
i = (i + 1) & mask_;
}
return nullptr;
}


void erase(K key) {
size_t i = hash(key);
while (table_[i].key) {
if (table_[i].key == key) {
table_[i].key = 0;
table_[i].value = nullptr;
return;
}
i = (i + 1) & mask_;
}
}
};
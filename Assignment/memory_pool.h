#pragma once
#include <vector>
#include <new>
#include <type_traits>


// Simple memory pool for fixed-size allocations
template<typename T, size_t BlockSize = 1024>
class MemoryPool {
struct Block {
typename std::aligned_storage<sizeof(T), alignof(T)>::type data[BlockSize];
};


std::vector<Block*> blocks_;
std::vector<T*> free_list_;
size_t index_ = 0;


public:
~MemoryPool() { for (auto b : blocks_) delete b; }


template<typename... Args>
T* construct(Args&&... args) {
T* ptr = allocate();
new (ptr) T(std::forward<Args>(args)...);
return ptr;
}


void destroy(T* ptr) {
if (ptr) {
ptr->~T();
free_list_.push_back(ptr);
}
}


private:
T* allocate() {
if (!free_list_.empty()) {
T* obj = free_list_.back();
free_list_.pop_back();
return obj;
}


if (blocks_.empty() || index_ >= BlockSize) {
blocks_.push_back(new Block());
index_ = 0;
}


return reinterpret_cast<T*>(&blocks_.back()->data[index_++]);
}
};
#pragma once
#include "types.h"
#include "memory_pool.h"
#include "fast_hash_map.h"
#include <vector>
#include <functional>
#include <iostream>


struct OrderNode {
Order order;
Limit* parent_limit = nullptr;
OrderNode* prev = nullptr;
OrderNode* next = nullptr;
};


class OrderBook {
public:
void add_order(const Order& order);
bool cancel_order(uint64_t order_id);
bool amend_order(uint64_t order_id, double new_price, uint64_t new_qty);
void get_snapshot(size_t depth, std::vector<PriceLevel>& bids, std::vector<PriceLevel>& asks) const;
void print_book(size_t depth = 10) const;


private:
std::vector<Limit*> bids_, asks_;
FastHashMap<uint64_t, OrderNode*> lookup_;
MemoryPool<OrderNode> order_pool_;
MemoryPool<Limit> limit_pool_;


void add_to_limit(OrderNode* node, Limit* limit);
void remove_from_limit(OrderNode* node);
};
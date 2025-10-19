#pragma once
#include <cstdint>
#include <vector>
#include <string>


struct OrderNode; // Forward declaration


using Price = int64_t; // Using fixed-point for price (4 decimal places)


inline constexpr Price to_fixed_price(double p) { return static_cast<Price>(p * 10000.0); }
inline constexpr double to_double_price(Price p) { return static_cast<double>(p) / 10000.0; }


// Represents one price level (aggregated volume at a single price)
struct Limit {
Price price;
uint64_t total_quantity;
OrderNode* head;
OrderNode* tail;
bool is_bid;


Limit(Price p, bool bid = true)
: price(p), total_quantity(0), head(nullptr), tail(nullptr), is_bid(bid) {}
};


// Basic order structure (given)
struct Order {
uint64_t order_id;
bool is_buy;
double price;
uint64_t quantity;
uint64_t timestamp_ns;
};


struct PriceLevel {
double price;
uint64_t total_quantity;
};
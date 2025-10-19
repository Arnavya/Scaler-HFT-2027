#include "order_book.h"


void OrderBook::add_to_limit(OrderNode* node, Limit* limit) {
node->parent_limit = limit;
if (limit->tail) {
limit->tail->next = node;
node->prev = limit->tail;
} else {
limit->head = node;
}
limit->tail = node;
limit->total_quantity += node->order.quantity;
}


void OrderBook::remove_from_limit(OrderNode* node) {
Limit* limit = node->parent_limit;
limit->total_quantity -= node->order.quantity;


if (node->prev) node->prev->next = node->next;
else limit->head = node->next;


if (node->next) node->next->prev = node->prev;
else limit->tail = node->prev;
}


void OrderBook::get_snapshot(size_t depth, std::vector<PriceLevel>& bids, std::vector<PriceLevel>& asks) const {
bids.clear(); asks.clear();
for (size_t i = 0; i < depth && i < bids_.size(); ++i)
bids.push_back({to_double_price(bids_[bids_.size() - 1 - i]->price), bids_[bids_.size() - 1 - i]->total_quantity});
for (size_t i = 0; i < depth && i < asks_.size(); ++i)
asks.push_back({to_double_price(asks_[i]->price), asks_[i]->total_quantity});
}


void OrderBook::print_book(size_t depth) const {
std::vector<PriceLevel> bids, asks;
get_snapshot(depth, bids, asks);


std::cout << std::string(50, '-') << "\n";
std::cout << "ORDER BOOK" << std::endl;
std::cout << std::string(50, '-') << "\n";


std::cout << std::setw(12) << "BID_PRICE" << std::setw(12) << "BID_QTY" << " | "
<< std::setw(12) << "ASK_PRICE" << std::setw(12) << "ASK_QTY" << "\n";
std::cout << std::string(50, '-') << "\n";


for (size_t i = 0; i < depth; ++i) {
if (i < bids.size()) std::cout << std::setw(12) << std::fixed << std::setprecision(2) << bids[i].price
<< std::setw(12) << bids[i].total_quantity;
else std::cout << std::setw(24) << " ";


std::cout << " | ";


if (i < asks.size()) std::cout << std::setw(12) << asks[i].price
<< std::setw(12) << asks[i].total_quantity;
else std::cout << std::setw(24) << " ";


std::cout << "\n";
}


std::cout << std::string(50, '-') << std::endl;
}
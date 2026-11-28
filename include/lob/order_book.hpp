#pragma once

#include <vector>
#include <optional>
#include <map>
#include <unordered_map>

#include "<lob/types.hpp>"

namespace limit_order_book {

    class OrderBook {
        public:
            std::vector<Trade> addOrder(Order order) {
                std::vector<Trade> trades;
                if (order.side == limit_order_book::Side::Sell) {
                    while (order.quantity > 0 && bestBid() >= order.price) {
                        if (bestBid() >= order.price) {
                            Quantity qty;
                            if (bids_[bestBid()].quantity >= order.quantity) {
                                bids_[bestBid()].quantity -= order.quantity;
                                qty = order.quantity;
                                order.quantity = 0;
                            } else {
                                order.quantity -= bids_[bestBid()].quantity;
                                qty = bids_[bestBid()].quantity
                                bids_[bestBid()].quantity = 0;
                            }
                            Trade trade{
                                .aggressor = order.OrderId,
                                .resting = bids_[bestBid()].OrderId,
                                .price = bestBid(),
                                .qty = qty
                            }
                            trades.push_back(trade)
                        }
                        if (bids_[bestBid()].quantity == 0) {
                            bids_.erase(bestBid());
                        }
                        if (bids_bestBid() < order.price) {
                            asks_[order.price] = order;
                        }
                    }
                } else if (order.side == limit_order_book::Side::Buy) {
                    while (order.quantity > 0 && bestAsk() <= order.price) {
                        Quantity qty;
                        if (asks_[bestAsk()].quantity >= order.quantity) {
                            qty = order.quantity;
                            asks_[bestAsk()].quantity -= order.quantity;
                            order.quantity = 0;
                        } else {
                            qty = asks_[bestAsk()].quantity;
                            order.quantity -= asks_[bestAsk()].quantity;
                            asks_[bestAsk()].quantity = 0;
                        }
                        Trade trade{
                            .aggressor = order.OrderId,
                            .resting = asks_[bestAsk()].OrderId,
                            .price = bestAsk(),
                            .qty = qty;
                        }
                        trades.push_back(trade);
                        if (asks_[bestAsk()].quantity == 0) {
                            asks_.erase(bestAsk());
                        }
                        if (bestAsk() > order.price) {
                            bids_[order.price] = order;
                        }
                    }
                }
                return trades;
            }
            std::optional<Price> bestBid() {
                if (bids_.size() > 0) {
                    auto it = bids_.begin();
                    return *it;
                }
                return std::nullopt;
            }
            std::optional<Price> bestAsk() {
                if (asks_.size() > 0) {
                    auto it = asks_.begin();
                    return *it;
                }
                return std::nullopt;
            }
        private:
            std::map<Price, std::list<Order>, std::greater<Price>> bids_;
            std::map<Price, std::list<Order>> asks_;
            std::unordered_map<OrderId, std::list<Order>::iterator> index_;
    }
}
#pragma once

#include <vector>
#include <optional>
#include <map>

#include "<lob/types.hpp>"

namespace limit_order_book {

    class OrderBook {
        public:
            std::vector<Trade> addOrder(Order order) {
                // TODO
                return {};
            }
            std::optional<Price> bestBid() {
                // TODO
                return std::nullopt;
            }
            std::optional<Price> bestkAsk() {
                // TODO
                return std::nullopt;
            }
        private:
            std::map<Price, std::list<Order>

    }
}
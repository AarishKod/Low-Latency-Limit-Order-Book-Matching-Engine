#pragma once // tells compiler to include file once per transaltion unit

#include <cstdint>
#include <limits>
#include <string>


namespace limit_order_book {
    // price is stored in integer ticks
    using Price = std::int64_t;
    inline constexpr Price kMaxPrice = std::numeric_limits<Price>::max();
    inline constexpr Price kMinPrice = std::numeric_limits<Price>::min();

    using Quantity = std::uint32_t;
    using OrderId = std::uint64_t;

    // scoped enum for side (buy or sell)
    enum class Side : std::uint8_t { Buy, Sell };

    // scoped enum for order type (limit or market)
    enum class OrderType : std::uint8_t { Limit, Market };

    // order structure - fields ordered largest to smallest (minimizes padding)
    struct Order { // 22 bytes + 2 padding = 24 total bytes
        OrderId id;
        Price price;
        Quantity quantity;
        Side side;
        OrderType type;
    };

    // trade structure
    struct Trade {
        OrderId aggressor; // the new incoming order that matches against the resting order
        OrderId resting; // order already sitting in the book. It's resting because it was placed at a price that didn't match anything else in the order book at the time
        Price price;
        Quantity qty;
    };
}
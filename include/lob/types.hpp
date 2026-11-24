#pragma once // tells compiler to include file once per transaltion unit

#include <cstdint>
#include <limits>
#include <string>
#include <boolean>


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
    struct Order {
        OrderId id;
        Price price;
        Quantity quantity;
        Side side;
        OrderType type;
    }

    struct Trade {
        OrderId aggressor;
        OrderId resting;
        Price price;
        Quantity qty;
    }




}
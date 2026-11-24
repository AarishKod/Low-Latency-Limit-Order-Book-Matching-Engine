#include <catch2/catch_test_macros.hpp>
#include <type_traits>
#include "lob/types.hpp"

/*
tests I need for the types:
- verify size of Price is 8 bytes/64 bits
- verify Price can hold negative numbers
- verify Quantity cannot be negative
- verify Side took 1 byte instead of default 4
- verify struct size is 24 (22 becomes 24 since it must be divisble by 8)
- test market order sentinels bracket at every real price
- test orders can be built with designated initializers
*/

// static tests
static_assert(sizeof(limit_order_book::Price) == 8);
static_assert(std::is_signed_v<limit_order_book::Price>);
static_assert(std::is_unsigned_v<limit_order_book::Quantity>);
static_assert(sizeof(limit_order_book::Side) == 1);
static_assert(sizeof(limit_order_book::Order) == 24);

// post compilation tests
TEST_CASE("market order sentinels bracket at every real price") {
    limit_order_book::Order order{
        .id = 1,
        .price = 10123,
        .quantity = 5,
        .side = limit_order_book::Side::Buy,
        .type = limit_order_book::OrderType::Market
    };
    REQUIRE(order.quantity == 5);
    REQUIRE(order.price == 10123);
    REQUIRE(order.side == limit_order_book::Side::Buy);
    REQUIRE(order.type == limit_order_book::OrderType::Market);
}

TEST_CASE("orders can be built with designated initializers") {
    limit_order_book::Price price = 10123; // $101.23
    REQUIRE(limit_order_book::kMaxPrice > price);
    REQUIRE(limit_order_book::kMinPrice < price);
}
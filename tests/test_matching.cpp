#include <catch2/catch_test_macros.hpp>
#include "lob/types.hpp"

using namespace limit_order_book;
TEST_CASE("have an order put for sale and and order bought at the same price") {
    OrderBook book;

    limit_order_book::Order sellOrder{
        .id = 1,
        .price = 10000,
        .quantity = 1,
        .side = limit_order_book::Side::Sell,
        .type = limit_order_book::OrderType::Limit
    };

    book.addOrder(sellOrder);

    REQUIRE(sizeof)

    limit_order_book::Order buyOrder{
        .id = 2,
        .price = 10000,
        .quantity = 1,
        .side = limit_order_book::Side::Buy,
        .type = limit_order_book::OrderType::Limit
    }

    book.addOrder(buyOrder)
}
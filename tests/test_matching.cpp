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

    auto t1 = book.addOrder(sellOrder);

    REQUIRE(sellOrder.empty());
    REQUIRE(book.bestAsk() == 10000);

    limit_order_book::Order buyOrder{
        .id = 2,
        .price = 10000,
        .quantity = 1,
        .side = limit_order_book::Side::Buy,
        .type = limit_order_book::OrderType::Limit
    }

    auto t2 = book.addOrder(buyOrder);

    REQUIRE(t2.size() == 1);
    REQUIRE(t2[0].aggressor == 2); // agressor is id of incoming order that mathches against resting order
    REQUIRE(t2[0].resting == 1);
    REQUIRE(t2[0].price == 10000);
    REQUIRE(t2[0].qty == 100);
}
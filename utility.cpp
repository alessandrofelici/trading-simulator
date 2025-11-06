#include "utility.hpp"
#include <iostream>
#include <string>

std::ostream &operator<<(std::ostream &os, const Order &order)
{
  return os << order.side << " " << order.amount << " " << order.asset << " at "
            << order.price << " USD by " << order.username;
}

bool operator==(const Order &order1, const Order &order2)
{
  if (order1.side != order2.side || order1.amount != order2.amount ||
      order1.price != order2.price)
  {
    return false;
  }
  return true;
}
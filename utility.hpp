#pragma once
#include <iostream>
#include <string>

struct Order
{
  std::string username;
  std::string side; // Can be "Buy" or "Sell"
  std::string asset;
  int amount;
  int price;
};

struct Trade
{
  std::string buyer_username;
  std::string seller_username;
  std::string asset;
  int amount;
  int price;
};

bool operator==(const Order &order1, const Order &order2);
std::ostream &operator<<(std::ostream &os, const Order &order);
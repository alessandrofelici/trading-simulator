#pragma once
#include <string>
#include <vector>
#include <map>
#include "utility.hpp"

class Useraccount
{
public:
  std::string name;
  std::vector<std::string> portfolio;
  std::map<std::string, int> assets;
  std::vector<Order> open_orders;
  std::vector<Order> filled_orders;
  Useraccount(const std::string &n) : name{n}, portfolio{}, assets{}, open_orders{}, filled_orders{} {}
  std::map<std::string, int>::iterator GetAssets(const std::string &asset_name);
  bool HasFunds(const std::string &asset_name, int amount);
  std::vector<Order>::iterator FindOrder(const Order &order);
};
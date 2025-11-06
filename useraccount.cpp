#include "useraccount.hpp"
#include <algorithm>
#include <iterator>
#include <string>

// Easy access to assets in a user
std::map<std::string, int>::iterator Useraccount::GetAssets(const std::string &asset_name)
{
  return std::find_if(assets.begin(), assets.end(), [&asset_name](const std::pair<std::string, int> &asset)
                      { return asset.first == asset_name; });
}

bool Useraccount::HasFunds(const std::string &asset_name, int amount)
{
  std::map<std::string, int>::iterator asset_location{GetAssets(asset_name)};
  return (asset_location != assets.end() && asset_location->second >= amount);
}

std::vector<Order>::iterator Useraccount::FindOrder(const Order &order)
{
  return std::find_if(open_orders.begin(), open_orders.end(), [&order](const Order &o)
                      { return o == order; });
}
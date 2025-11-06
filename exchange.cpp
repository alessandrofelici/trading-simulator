#include "exchange.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <cstdint>

// For easy access to specific user
std::vector<Useraccount>::iterator Exchange::GetUser(const std::string &username)
{
  return std::find_if(users.begin(), users.end(), [&username](const Useraccount &user)
                      { return user.name == username; });
}

void Exchange::AlphabetizeUsers()
{
  std::sort(users.begin(), users.end(), [](const Useraccount &a, const Useraccount &b)
            { return a.name < b.name; });
}

void Exchange::AlphabetizeAssets()
{
  std::sort(assets_list.begin(), assets_list.end(), [](const std::string &a, const std::string &b)
            { return a < b; });
}

void Exchange::MakeDeposit(const std::string &username, const std::string &asset,
                           int amount)
{
  std::vector<Useraccount>::iterator user{GetUser(username)};
  // Add user if new
  if (user == users.end())
  {
    users.push_back(Useraccount(username));
    user = GetUser(username);
  }
  if (user->GetAssets(asset) == user->assets.end())
  {
    user->assets.insert({asset, amount});
  }
  else
  {
    user->GetAssets(asset)->second += amount;
  }
  if (std::find(assets_list.begin(), assets_list.end(), asset) == assets_list.end())
  {
    if (asset != "USD")
    {
      assets_list.push_back(asset);
    }
  }
  AlphabetizeAssets();
  AlphabetizeUsers();
}

void Exchange::PrintUserPortfolios(std::ostream &os) const
{
  os << "User Portfolios (in alphabetical order):\n";
  for (const Useraccount &user : users)
  {
    os << user.name << "'s Portfolio: ";
    for (const auto &asset : user.assets)
    {
      os << asset.second << " " << asset.first << ", ";
    }
    os << "\n";
  }
}

bool Exchange::MakeWithdrawal(const std::string &username, const std::string &asset,
                              int amount)
{
  std::vector<Useraccount>::iterator user{GetUser(username)};
  if (user == users.end())
  {
    return false;
  }
  if (user->HasFunds(asset, amount))
  {
    std::map<std::string, int>::iterator asset_location{user->GetAssets(asset)};
    asset_location->second -= amount;
    if (asset_location->second <= 0)
    {
      user->assets.erase(asset_location);
    }
    return true;
  }
  return false;
}

bool Exchange::AddOrder(const Order &order)
{
  std::vector<Useraccount>::iterator user{GetUser(order.username)};
  std::vector<Useraccount>::iterator match_user;
  Order match_order;
  int amount_sold;
  int order_amount{order.amount};
  int order_leftover{order.amount};
  bool open_order_success{CreateOpenOrder(order, user)};
  while (order_leftover > 0 && FindMatch(order, match_order, match_user))
  {
    if (order.amount < match_order.amount)
    {
      amount_sold = order_amount;
    }
    else
    {
      amount_sold = match_order.amount;
    }
    if (order.side == "Sell")
    {

      CompleteTrade({match_order.username, order.username, order.asset, amount_sold, order.price}, match_order.amount, order_amount, match_order.price, order.price);
    }
    else if (order.side == "Buy")
    {
      CompleteTrade({order.username, match_order.username, order.asset, amount_sold, order.price}, order_amount, match_order.amount, order.price, match_order.price);
    }
    order_leftover -= match_order.amount; // change order.amount so can find order for
    order_amount -= amount_sold;
  }

  return open_order_success;
}

void Exchange::CompleteTrade(const Trade &trade, int buy_amount, int sell_amount, int buy_price, int sell_price)
{
  std::vector<Useraccount>::iterator buyer{GetUser(trade.buyer_username)};
  std::vector<Useraccount>::iterator seller{GetUser(trade.seller_username)};
  std::vector<Order>::iterator modify_buy{buyer->FindOrder({trade.buyer_username, "Buy", trade.asset, buy_amount, buy_price})};
  std::vector<Order>::iterator modify_sell{seller->FindOrder({trade.seller_username, "Sell", trade.asset, sell_amount, sell_price})};
  buyer->assets.insert({trade.asset, 0});
  seller->assets.insert({"USD", 0});
  std::map<std::string, int>::iterator bought_asset{buyer->GetAssets(trade.asset)};
  std::map<std::string, int>::iterator sold_profit{seller->GetAssets("USD")};
  bought_asset->second += trade.amount;
  sold_profit->second += (trade.amount * trade.price);
  modify_buy->amount -= trade.amount;
  modify_sell->amount -= trade.amount;
  buyer->filled_orders.push_back({trade.buyer_username, "Buy", trade.asset, trade.amount, trade.price});
  seller->filled_orders.push_back({trade.seller_username, "Sell", trade.asset, trade.amount, trade.price});
  RemoveZeroAssets();
  AddHistory(trade);
}

bool Exchange::FindMatch(const Order &order, Order &match_order, std::vector<Useraccount>::iterator &match_user)
{
  int lowest_price{INT32_MAX};
  int highest_price{0};
  for (std::vector<Useraccount>::iterator match_u{users.begin()}; match_u != users.end(); ++match_u)
  {
    for (const Order &match_o : match_u->open_orders)
    {
      if (order.side == "Buy")
      {
        if (order.price >= match_o.price && order.asset == match_o.asset && order.side != match_o.side && match_o.price < lowest_price)
        {
          match_user = match_u;
          match_order = match_o;
          lowest_price = match_o.price;
        }
      }
      else
      {
        if (order.price <= match_o.price && order.asset == match_o.asset && order.side != match_o.side && match_o.price > highest_price)
        {
          match_user = match_u;
          match_order = match_o;
          highest_price = match_o.price;
        }
      }
    }
  }
  return ((lowest_price != INT32_MAX) || (highest_price != 0));
}

bool Exchange::CreateOpenOrder(const Order &order, const std::vector<Useraccount>::iterator &user)
{
  if (order.side == "Sell")
  {
    if (user->HasFunds(order.asset, order.amount))
    {
      user->open_orders.push_back(order);
      std::map<std::string, int>::iterator asset_location{user->GetAssets(order.asset)};
      asset_location->second -= order.amount;
      return true;
    }
  }
  else if (order.side == "Buy")
  {
    if (user->HasFunds("USD", order.amount * order.price))
    {
      user->open_orders.push_back(order);
      std::map<std::string, int>::iterator asset_location{user->GetAssets("USD")};
      asset_location->second -= (order.amount * order.price);
      return true;
    }
  }
  return false;
}

void Exchange::RemoveZeroAssets()
{
  for (Useraccount &user : users)
  {
    for (Order &order : user.open_orders)
    {
      if (order.amount == 0)
      {
        user.open_orders.erase(user.FindOrder(order));
      }
    }
  }
}

void Exchange::PrintUsersOrders(std::ostream &os) const
{
  os << "Users Orders (in alphabetical order):\n";
  for (const Useraccount &user : users)
  {
    os << user.name << "'s Open Orders (in chronological order):\n";
    for (const Order &order : user.open_orders)
    {
      os << order << std::endl;
    }
    os << user.name << "'s Filled Orders (in chronological order):\n";
    for (const Order &order : user.filled_orders)
    {
      os << order << std::endl;
    }
  }
}

void Exchange::AddHistory(const Trade &trade)
{

  trade_history.push_back(trade.buyer_username + " Bought " + std::to_string(trade.amount) + " of " + trade.asset + " From " + trade.seller_username + " for " + std::to_string(trade.price) + " USD\n");
}

void Exchange::PrintTradeHistory(std::ostream &os) const
{
  os << "Trade History (in chronological order):\n";
  for (const std::string &history : trade_history)
  {
    os << history;
  }
}

// prints NA more than should
void Exchange::PrintBidAskSpread(std::ostream &os) const
{
  os << "Asset Bid Ask Spread (in alphabetical order):\n";
  int min{INT32_MAX}, max{-1};
  for (const std::string &asset : assets_list)
  {
    for (const Useraccount &user : users)
    {
      for (const Order &order : user.open_orders)
      {
        if (order.asset == asset)
        {
          if (order.price > max && order.side == "Buy")
          {
            max = order.price;
          }
          if (order.price < min && order.side == "Sell")
          {
            min = order.price;
          }
        }
      }
    }
    os << asset << ": Highest Open Buy = ";
    if (max == -1)
    {
      os << "NA";
    }
    else
    {
      os << max;
    }
    os << " USD and Lowest Open Sell = ";
    if (min == INT32_MAX)
    {
      os << "NA";
    }
    else
    {
      os << min;
    }
    os << " USD\n";
    min = INT32_MAX;
    max = -1;
  }
}
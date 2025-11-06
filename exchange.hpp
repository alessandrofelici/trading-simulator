#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "useraccount.hpp"
#include "utility.hpp"

class Exchange
{
public:
  // Data Members
  std::vector<Useraccount> users;
  std::vector<std::string> trade_history;
  std::vector<std::string> assets_list;
  // General helper methods
  std::vector<Useraccount>::iterator GetUser(const std::string &username);
  void AlphabetizeUsers();
  void AlphabetizeAssets();
  void RemoveZeroAssets();
  void AddHistory(const Trade &trade);
  // Functions to manipulate exchange
  void MakeDeposit(const std::string &username, const std::string &asset,
                   int amount);
  bool MakeWithdrawal(const std::string &username, const std::string &asset,
                      int amount);
  bool AddOrder(const Order &order);
  // AddOrder helper methods
  bool FindMatch(const Order &order, Order &match_order, std::vector<Useraccount>::iterator &match_user);
  bool CreateOpenOrder(const Order &order, const std::vector<Useraccount>::iterator &user);
  void CompleteTrade(const Trade &trade, int buy_amount, int sell_amount, int buy_price, int sell_price);
  // Print functions
  void PrintUserPortfolios(std::ostream &os) const;
  void PrintUsersOrders(std::ostream &os) const;
  void PrintTradeHistory(std::ostream &os) const;
  void PrintBidAskSpread(std::ostream &os) const;
};
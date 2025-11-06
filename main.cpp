#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "exchange.hpp"
#include "useraccount.hpp"
#include "utility.hpp"

int main()
{
  std::cout << "start" << std::endl;

  Exchange e;
  e.MakeDeposit("Nahum", "BTC", 10);
  e.MakeDeposit("Dolson", "USD", 5555);
  e.AddOrder({"Nahum", "Sell", "BTC", 5, 100});
  std::cout << "My Program:\n";
  e.PrintUserPortfolios(std::cout);
  std::cout << "\nKey:\nUser Portfolios (in alphabetical order):\nDolson's Portfolio: 5555 USD, \nNahum's Portfolio: 5 BTC, \n\n\n";
  std::cout << "My Program:\n";
  e.PrintUsersOrders(std::cout);
  std::cout << "\nKey:\nUsers Orders (in alphabetical order):\nDolson's Open Orders (in chronological order):\nDolson's Filled Orders (in chronological order):\nNahum's Open Orders (in chronological order):\nSell 5 BTC at 100 USD by Nahum\nNahum's Filled Orders (in chronological order):\n\n\n";
  std::cout << std::endl
            << std::endl;
  e.AddOrder({"Dolson", "Buy", "BTC", 7, 100});
  std::cout << "My Program:\n";
  e.PrintUserPortfolios(std::cout);
  std::cout << "\nKey:\nUser Portfolios (in alphabetical order):\nDolson's Portfolio: 5 BTC, 4855 USD, \nNahum's Portfolio: 5 BTC, 500 USD, \n\n\n";
  std::cout << "My Program:\n";
  e.PrintUsersOrders(std::cout);
  std::cout << "\nKey:\nUsers Orders (in alphabetical order):\nDolson's Open Orders (in chronological order):\nBuy 2 BTC at 100 USD by Dolson\nDolson's Filled Orders (in chronological order):\nBuy 5 BTC at 100 USD by Dolson\nNahum's Open Orders (in chronological order):\nNahum's Filled Orders (in chronological order):\nSell 5 BTC at 100 USD by Nahum\n\n\n";
  std::cout << std::endl
            << std::endl;
  e.AddOrder({"Nahum", "Sell", "BTC", 3, 100});
  std::cout << "My Program:\n";
  e.PrintUserPortfolios(std::cout);
  std::cout << "\nKey:\nUser Portfolios (in alphabetical order):\nDolson's Portfolio: 7 BTC, 4855 USD, \nNahum's Portfolio: 2 BTC, 700 USD, \n\n\n";
  std::cout << "My Program:\n";
  e.PrintUsersOrders(std::cout);
  std::cout << "\nKey:\nUsers Orders (in alphabetical order):\nDolson's Open Orders (in chronological order):\nDolson's Filled Orders (in chronological order):\nBuy 5 BTC at 100 USD by Dolson\nBuy 2 BTC at 100 USD by Dolson\nNahum's Open Orders (in chronological order):\nSell 1 BTC at 100 USD by Nahum\nNahum's Filled Orders (in chronological order):\nSell 5 BTC at 100 USD by Nahum\nSell 2 BTC at 100 USD by Nahum\n\n\n";

  // Exchange msu_base;
  // msu_base.MakeDeposit("Nahum", "USD", 1000);
  // msu_base.MakeDeposit("Nahum", "ETH", 400);
  // msu_base.MakeDeposit("Dolson", "BTC", 100);
  // msu_base.MakeDeposit("Dolson", "USD", 7000);
  // msu_base.MakeDeposit("Enbody", "USD", 7000);
  // msu_base.MakeDeposit("Ofria", "BCH", 9);
  // msu_base.MakeWithdrawal("Dolson", "BTC", 10);
  // msu_base.PrintUserPortfolios(std::cout);
  // std::cout << std::endl;
  // Order o_n{"Nahum", "Buy", "BTC", 2, 22};
  // Order o_d{"Dolson", "Sell", "BTC", 3, 17};
  // std::cout << "Before 1st add order" << std::endl;

  // msu_base.AddOrder(o_n);
  // std::cout << "After 1st add order" << std::endl;
  // msu_base.PrintUsersOrders(std::cout);

  // std::cout << std::endl;

  // std::cout << "Before 2nd add order" << std::endl;

  // msu_base.AddOrder(o_d);

  // std::cout << "After 2nd add order" << std::endl;

  // msu_base.PrintTradeHistory(std::cout);
  // std::cout << std::endl;
  // msu_base.PrintUserPortfolios(std::cout);
  // std::cout << std::endl;
  // msu_base.PrintUsersOrders(std::cout);
  // std::cout << std::endl;
  // msu_base.AddOrder({"Dolson", "Buy", "ETH", 10, 200});
  // msu_base.AddOrder({"Enbody", "Buy", "ETH", 15, 300});
  // msu_base.AddOrder({"Nahum", "Sell", "ETH", 20, 100});

  // msu_base.PrintTradeHistory(std::cout);
  // msu_base.PrintUsersOrders(std::cout);
  // msu_base.AddOrder({"Nahum", "Sell", "ETH", 20, 1000});
  // msu_base.AddOrder({"Dolson", "Sell", "ETH", 2, 250});
  // msu_base.AddOrder({"Enbody", "Buy", "BTC", 1, 10});
  // msu_base.PrintTradeHistory(std::cout);
  // msu_base.PrintUserPortfolios(std::cout);
  // std::cout << std::endl << std::endl;
  // msu_base.PrintUsersOrders(std::cout);
  // msu_base.AddOrder({"Enbody", "Buy", "LTC", 1, 10});
  // msu_base.AddOrder({"Ofria", "Sell", "BCH", 2, 55});
  // msu_base.PrintBidAskSpread(std::cout);

  return 0;
}
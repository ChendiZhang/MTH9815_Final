//
//  BondMarketDataService.hpp
//  MTH9815_final
//
//  Created by Chendi Zhang on 12/16/16.
//  Copyright © 2016 Chendi Zhang. All rights reserved.
//

#ifndef BondMarketDataService_hpp
#define BondMarketDataService_hpp
#include "marketdataservice.hpp" 
#include "products.hpp"
#include "GlobalFunction.hpp"
#include <map>
#include <string>
using namespace std;


class BondMarketDataService: public MarketDataService<Bond>
{
private:
   
public:
    map<string,OrderBook<Bond>> FullOrderBook;
    virtual OrderBook<Bond> AggregateDepth(string &productId)
    {
        return FullOrderBook[productId];
    }
    virtual BidOffer GetBestBidOffer(string &productId)
    {
        OrderBook<Bond> bond_order_book=AggregateDepth(productId);
        BidOffer best_order(bond_order_book.GetBidStack()[0],bond_order_book.GetOfferStack()[0]);
        return best_order;
        
    }
    virtual OrderBook<Bond> &GetData(string key)
    {
        return FullOrderBook[key];
    }
    virtual void OnMessage(OrderBook<Bond> &data)
    {
        string ID=data.GetProduct().GetProductId();
        FullOrderBook[ID]=data;
    }
    void PrintMarketData()
    {
        map<string,OrderBook<Bond>>::iterator iter=FullOrderBook.begin();
        while(iter!=FullOrderBook.end())
        {
            
            cout<<iter->first<<" "<<iter->second.GetBidStack()[0].GetPrice()<<endl;
            iter++;
        }
    }

    
    
};
class BondMarketDataConnector: MarketDataConnector<Bond>
{
private:
    ifstream marketdata_file;
    BondMarketDataService& _BondMarketDataService;
public:
    BondMarketDataConnector(string file_name, BondMarketDataService &BondServiceName):_BondMarketDataService(BondServiceName)
    {
        marketdata_file.open(file_name);
        string head;
    }
    
    
    //get OrderBook
    OrderBook<Bond> GetOrderBook()
    {
        
        if(!marketdata_file.eof())
        {
            string line;
            getline(marketdata_file,line);
//            cout<<line<<endl;
            stringstream ss(line);

            string cusip;
            vector<Order> bid_stack;
            vector<Order> ask_stack;
            for(int i=1; i<=5; i++)
            {
                //get product
                getline(ss, cusip,',');
                //get mid price
                string midprice;
                getline(ss,midprice,',');
                
                double mid_price=get_price(midprice);
                //get spread
                string spread;
                getline(ss,spread,',');
                double bid_ask_spread=get_spread(spread);
                //get quantity
                string quantity;
                getline(ss,quantity,',');
                long Quantity=stoi(quantity);
                
                double bid_price=mid_price-bid_ask_spread/2.0;
                double ask_price=mid_price+bid_ask_spread/2.0;
                
                //construct an Order
                Order bid_order(bid_price, Quantity, BID);
                Order ask_order(ask_price, Quantity, OFFER);
                
                bid_stack.push_back(bid_order);
                ask_stack.push_back(ask_order);
                
                
            }
            OrderBook<Bond> ans(Bond(cusip),bid_stack,ask_stack);
            return ans;
        }
        else
        {
            return OrderBook<Bond>(Bond(), vector<Order>(), vector<Order>());
        }
    }
    virtual void Publish()
    {
        OrderBook<Bond> data=GetOrderBook();
        _BondMarketDataService.OnMessage(data);
        
    }
    
};


#endif /* BondMarketDataService_h */

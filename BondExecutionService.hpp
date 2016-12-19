//
//  BondExecutionService.hpp
//  MTH9815_final
//
//  Created by Chendi Zhang on 12/16/16.
//  Copyright © 2016 Chendi Zhang. All rights reserved.
//

#ifndef BondExecutionService_hpp 
#define BondExecutionService_hpp
#include "executionservice.hpp"
#include "BondMarketDataService.hpp"
#include "marketdataservice.hpp"
#include "products.hpp"
#include <map>

class BondExecutionService: public ExecutionService<Bond>
{
private:
    BondMarketDataService &B_m_data_service;
    
    long ticker;

public:
    map<string,ExecutionOrder<Bond>> best_bid_order;
    map<string, ExecutionOrder<Bond>> best_offer_order;
    BondExecutionService(BondMarketDataService &service_0):B_m_data_service(service_0),ticker(0)
    {
    }
    virtual ExecutionOrder<Bond> &GetData(string key)
    {
        if(ticker%2)
        {
            return best_bid_order[key];
        }
        else
        {
            return best_offer_order[key];
        }
    }
    void AddExecutionOrder()
    {
        map<string,OrderBook<Bond>>::iterator iter=B_m_data_service.FullOrderBook.begin();
        ticker++;
        while(iter!=B_m_data_service.FullOrderBook.end())
        {
            string cusip=iter->first;

           Order  best_order_1= iter->second.GetBidStack()[0];
       
           Order      best_order_2= iter->second.GetOfferStack()[0];
            Bond B_0(cusip);
            ExecutionOrder<Bond> bid_order(B_0,best_order_1.GetSide(),to_string(ticker),MARKET,best_order_1.GetPrice(),best_order_1.GetQuantity(),0,"0",true);
            
            best_bid_order[cusip]=bid_order;
            ExecutionOrder<Bond> offer_order(B_0,best_order_2.GetSide(),to_string(ticker),MARKET,best_order_2.GetPrice(),best_order_2.GetQuantity(),0,"0",true);
            best_offer_order[cusip]=offer_order;
            iter++;
        }
    }
    long GetTicker()
    {
        return ticker;
    }
    void PrintBondExecutionService()
    {
        map<string, ExecutionOrder<Bond>>::iterator iter_1=best_bid_order.begin();
        map<string, ExecutionOrder<Bond>>::iterator iter_2=best_offer_order.begin();
        while(iter_1!=best_bid_order.end()&&iter_2!=best_offer_order.end())
        {
            cout<<iter_1->first<<" "<<"Bid"<<" " <<iter_1->second.GetPrice()<<endl;
            cout<<iter_2->first<<" "<<"Offer"<<" " <<iter_2->second.GetPrice()<<endl;
            iter_1++;
            iter_2++;
            
        }

        
    }
    
};

#endif /* BondExecutionService_h */

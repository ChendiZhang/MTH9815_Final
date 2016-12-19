//
//  BondPricingService.hpp
//  MTH9815_final
//
//  Created by Chendi Zhang on 12/16/16.
//  Copyright © 2016 Chendi Zhang. All rights reserved.
//



#ifndef BondPricingService_h
#define BondPricingService_h 
#include "pricingservice.hpp"
#include "products.hpp"
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

class BondPricingService : public PricingService<Bond>
{
public:
    map<string, Price<Bond>> price_record;
    
    virtual Price<Bond>& GetData(string key)
    {
        return price_record[key];
    }
    void NotifyListener(Price<Bond> &data)
    {
        for(int i=0;i<service_listener.size();i++)
        {
            service_listener[i]->ProcessAdd(data);
            
        }
    }
    
    virtual void OnMessage(Price<Bond>& data)
    {
        string ID=data.GetProduct().GetProductId();
        price_record.insert({ID,data});
        NotifyListener(data);
        
    }
    
};

class BondPricingServiceListener: public PricingServiceListener<Bond>
{
private:
    BondPricingService& Bond_PricingService;
public:
    BondPricingServiceListener(BondPricingService& service):Bond_PricingService(service){};
    void ProcessAdd(Price<Bond> &data)
    {
        Bond_PricingService.OnMessage(data);
    }
};

class BondPricingConnector: public PricingConnector<Bond>
{
private:
    ifstream price_file;
    BondPricingService& Bond_PricingService;
public:
    BondPricingConnector(string file_name, BondPricingService& B_service_0):Bond_PricingService(B_service_0)
    {
        price_file.open(file_name);
        //        string head;
        //        getline(price_file,head);
    }
    Price<Bond> GetPrice()
    {
        string line;
        if(!price_file.eof())
        {
            getline(price_file,line);
            stringstream ss(line);
            //get the cusip
            string cusip;
            getline(ss,cusip,',');
            //get mid
            string mid_price;
            getline(ss,mid_price,',');
            //get bid_ask_spread
            string bid_ask_spread;
            getline(ss,bid_ask_spread,',');
            
            //get the double_mid_price of the bond
            stringstream price_ss(mid_price);
            string first;
            getline(price_ss,first,'-');
            string second;
            getline(price_ss,second);
            if(second[2]=='+')
                second[2]='4';
            
            int temp=stoi(second);
            int first_two_digits=temp/10;
            int third_digits=temp%10;
            
            double mid=stoi(first)+first_two_digits/32.0+third_digits/256.0;
            //get the bid ask spread
            stringstream spread_ss(bid_ask_spread);
            string first1;
            getline(spread_ss,first1,'-');
            string second1;
            getline(spread_ss,second1);
            if(second1[2]=='+')
                second1[2]='4';
            
            int temp1=stoi(second);
            int first_two_digits1=temp1/10;
            int third_digits1=temp1%10;
            
            double spread=first_two_digits1/32.0+third_digits1/256.0;
            
            Bond Bond_0(cusip);
            Price<Bond> data(Bond_0,mid, spread);
            return data;
        }
        else
        {
            Bond Bond_0;
            Price<Bond> data(Bond_0,0,0);
            return data;
        }
    }
    virtual void Publish()
    {
        Price<Bond> data=GetPrice();
        Bond_PricingService.OnMessage(data);
    }
};
#endif /* BondPricingService_h */

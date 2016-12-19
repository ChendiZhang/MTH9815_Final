
//  MTH9815_final
//
//  Created by Chendi Zhang on 12/16/16.
//  Copyright © 2016 Chendi Zhang. All rights reserved. 
//

#ifndef BondTradeBookingService_h
#define BondTradeBookingService_h

#include "tradebookingservice.hpp"
#include <fstream>
#include <map>
#include "positionservice.hpp"
#include "products.hpp"
using namespace std;

class BondTradeBookingService : public TradeBookingService<Bond>
{
    
private:
   
public:
    // Book the trade
    map<string, Trade<Bond>> trade_record;
    virtual Trade<Bond> &GetData(string key)
    {
        return trade_record[key];
    };
    virtual void OnMessage( Trade<Bond> &data)
    {
        string ID=data.GetTradeId();
        trade_record[ID]=data;
    };
    //notify all the listener about the new update

    void PrintTradeRecord()
    {
        map<string,Trade<Bond>>::iterator iter=trade_record.begin();
        while(iter!=trade_record.end())
        {
            cout<<iter->first<<" "<<iter->second.GetQuantity()<<" "
            <<iter->second.GetBook()<<endl;
            iter++;
        }
    }

    
    
};

class BondTradeConnector: public TradeConnector<Bond>
{
private:
    ifstream trade_file;
    BondTradeBookingService &B_service;
public:
    
    BondTradeConnector(string file_name, BondTradeBookingService &service):B_service(service)
    {
        trade_file.open(file_name);
        string head;
         getline(trade_file,head);
    }
    Trade<Bond> GetTrade()
    {
        string line;
        if(!trade_file.eof())
        {
            getline(trade_file,line);
            stringstream ss(line);
            //get the cusip
            string cusip;
            getline(ss,cusip,',');
            //get the trade_id
            string trade_id;
            getline(ss,trade_id,',');
            //get the trade_book
            string trade_book;
            getline(ss,trade_book,',');
            //get the price string
            string price_str;
            getline(ss,price_str,',');
            
            //get the price of the bond
            stringstream price_ss(price_str);
            string first;
            getline(price_ss,first,'-');
            string second;
            getline(price_ss,second);
            if(second[2]=='+')
                second[2]='4';
            int temp=stoi(second);
            int first_two_digits=temp/10;
            int third_digits=temp%10;
        
            double price=stoi(first)+first_two_digits/32.0+third_digits/256.0;
        
            //get the quantity
            string quantity_str;
            getline(ss,quantity_str,',');
            long quantity=stol(quantity_str);
            
            
            //get the side
            string side_str;
            Side side;
            getline(ss,side_str);
            if(side_str=="SELL")
                side=SELL;
            if(side_str=="BUY")
                side=BUY;
            
            
            Bond Bond_0(cusip);
            Trade<Bond>  data(Bond_0,trade_id,trade_book,price,quantity,side);
            return  data;

        }
        else
        {
            Bond Bond_0;
            Trade<Bond> data(Bond_0,"","",0.0,0,SELL);
            return data;
        }
        
    }
    virtual void Publish()
    {
        Trade<Bond> data;
        data=GetTrade();
        B_service.OnMessage(data);
        
    };
};



#endif /* BondTradeBookingService_h */

// 
//  BondPositionService.hpp
//  MTH9815_final
//
//  Created by Chendi Zhang on 12/16/16.
//  Copyright © 2016 Chendi Zhang. All rights reserved.
//
#ifndef BondPositionService_h
#define BondPositionService_h
#include "products.hpp"
#include "soa.hpp" 
#include "BondTradeBookingService.hpp"

class BondPosition :public Position<Bond>
{
public:
    BondPosition(const Bond & _bond):Position(_bond)
    {
    }
    BondPosition():Position(){}
};


class BondPositionService:public PositionService<Bond>
{
private:
    BondTradeBookingService &B_service;
    
    
    
public:
    //position for all securities
    map<string,BondPosition> Position_list;
    BondPositionService(BondTradeBookingService &service_0):B_service(service_0)
    {
        
    }
    virtual BondPosition &GetData(string key)
    {
        return Position_list[key];
    };
    virtual void AddTrade()
    {
        map<string, Trade<Bond>>::iterator iter=B_service.trade_record.begin();
       for(;iter!=B_service.trade_record.end();iter++)
        {
            string Bond_id=iter->second.GetProduct().GetProductId();

            string book=iter->second.GetBook();
            if(Position_list.count(Bond_id))
            {
        
                if(Position_list[Bond_id].positions.count(book))
                    
                    Position_list[Bond_id].positions[book]+=iter->second.GetQuantity();
                else
                    Position_list[Bond_id].positions[book]=iter->second.GetQuantity();
            }
            else
            {
                BondPosition B_position(iter->second.GetProduct());
                Position_list[Bond_id]=  B_position;
                
            }
            
        }
        
    }
    void PrintPosition()
    {
        map<string,BondPosition>::iterator iter=Position_list.begin();
        while(iter!=Position_list.end())
        {
            cout<<iter->first<<" "<<iter->second.GetAggregatePosition()<<endl;
            iter++;
        }
    }
};

#endif /* BondPositionService_h */

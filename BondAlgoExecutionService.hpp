//
//  BondAlgoExecutionService.hpp
//  MTH9815_final 
//
//  Created by Chendi Zhang on 12/16/16.
//  Copyright © 2016 Chendi Zhang. All rights reserved.
//

#ifndef BondAlgoExecutionService_h
#define BondAlgoExecutionService_h

#include <map>
#include "BondExecutionService.hpp"
#include "products.hpp"

class BondAlgoExecutionService
{
private:
    BondExecutionService &B_execut_service;
    
public:
    map<string,ExecutionOrder<Bond>> execution_record;
    
    BondAlgoExecutionService(BondExecutionService &service_0):B_execut_service(service_0)
    {}
    void AlternativeStrategy()
    {
        long ticker=B_execut_service.GetTicker();
        if(ticker%2)
        {
            map<string,ExecutionOrder<Bond>>::iterator iter=B_execut_service.best_bid_order.begin();
            while(iter!=B_execut_service.best_bid_order.end())
            {
                execution_record[iter->first]=iter->second;
                iter++;
            }
        }
        else
        {
            map<string,ExecutionOrder<Bond>>::iterator iter=B_execut_service.best_offer_order.begin();
            while(iter!=B_execut_service.best_offer_order.end())
            {
                execution_record[iter->first]=iter->second;
                iter++;
            }
        }
    }
    void PrintAlogExecution()
    {
        map<string, ExecutionOrder<Bond>>::iterator iter=execution_record.begin();
        while(iter!=execution_record.end())
        {
            cout<<iter->first<<" "<<iter->second.GetPrice()<<endl;
            iter++;
            
        }
    }
};

#endif /* BondAlgoExecutionService_h */

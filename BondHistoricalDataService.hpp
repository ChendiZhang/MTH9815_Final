//
//  BondHistoricalDataService.hpp
//  MTH9815_final
//
//  Created by Chendi Zhang on 12/16/16.
//  Copyright © 2016 Chendi Zhang. All rights reserved.
//

#ifndef BondHistoricalDataService_h 
#define BondHistoricalDataService_h

#include "historicaldataservice.hpp"
#include <map>
#include "soa.hpp"
#include "products.hpp"
#include "BondRiskService.hpp"
#include "BondAlgoExecutionService.hpp"
#include "BondStreamingService.hpp"
#include <fstream>
#include <string>

class BondHistoricalDataService: public HistoricalDataService<Bond>
{
    
public:
    BondRiskService &risk_service;
    BondAlgoExecutionService &algo_service;
    BondStreamingService &stream_service;

    BondHistoricalDataService(BondRiskService &risk_0, BondAlgoExecutionService &algo_0,BondStreamingService &stream_0):risk_service(risk_0),algo_service(algo_0),stream_service(stream_0)
    {
        
    }
    virtual Bond &GetData(string key)
    {
        Bond B("");
        return B;
    }

    
    
    
};
class BondHistoricalDataConnector:public HistoricalDataConnector<Bond>
{
private:
    ofstream risk_file;
    ofstream algo_file;
    ofstream stream_file;
    BondHistoricalDataService &B_H_D_service;
public:
    BondHistoricalDataConnector(BondHistoricalDataService &service_0):B_H_D_service(service_0)
    {
        risk_file.open("risk.txt");
        algo_file.open("execution.txt");
        stream_file.open("stream.txt");
    }
    
    void PublishRisk()
    {
        map<string,PV01<Bond>>::iterator iter=B_H_D_service.risk_service.trade_risk_record.begin();
        while(iter!=B_H_D_service.risk_service.trade_risk_record.end())
        {
            risk_file<<iter->first<<","<<iter->second.GetPV01()<<endl;
            iter++;
        }
        
    }
    
    void PublishAlgo()
    {
        map<string, ExecutionOrder<Bond>>::iterator iter=B_H_D_service.algo_service.execution_record.begin();
        while(iter!=B_H_D_service.algo_service.execution_record.end())
        {
            algo_file<<iter->first<<","<<iter->second.GetOrderId()<<","<<iter->second.GetOrderType()<<","
            <<iter->second.GetVisibleQuantity()<<","<<iter->second.GetPricingSide()<<endl;
            iter++;
        }
        
    }
    void PublishStream()
    {
        map<string, PriceStream<Bond>>::iterator iter=B_H_D_service.stream_service.stream_record.begin();
        while(iter!=B_H_D_service.stream_service.stream_record.end())
        {
            stream_file<<iter->first<<","<<"Bid"<<","<<iter->second.GetBidOrder().GetPrice()<<","<<iter->second.GetBidOrder().GetVisibleQuantity()<<","<<"Offer"<<","<<iter->second.GetOfferOrder().GetPrice()<<","<<iter->second.GetOfferOrder().GetVisibleQuantity()<<endl;
            iter++;
        }
    }
    virtual void Publish()
    {
        
    }
    
};

#endif /* BondHistoricalDataService_h */

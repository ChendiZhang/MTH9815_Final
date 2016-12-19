//
//  BondRiskService.hpp
//  MTH9815_final
//
//  Created by Chendi Zhang on 12/16/16.
//  Copyright © 2016 Chendi Zhang. All rights reserved.
//

#ifndef BondRiskService_h
#define BondRiskService_h
#include "riskservice.hpp"
#include "products.hpp"
#include "BondPositionService.hpp"
#include <map>
#include <string>

  
class BondRiskService:public RiskService<Bond>
{
private:
    BondPositionService & B_pos_service;
     
public:
    map<string,double> risk_table;
    map<string,PV01<Bond>> trade_risk_record;
    BondRiskService(BondPositionService &service_0):B_pos_service(service_0)
    {
        risk_table["912828M72"]=0.01974732;
        risk_table["912828N22"]=0.029349458;
        risk_table["912828M98"]=0.047720509;
        risk_table["912828M80"]=0.06495714;
        risk_table["912828M56"]=0.089254107;
        risk_table["912810RP5"]=0.198018642;
        
        PV01<Bond> initial_value;
        trade_risk_record["912828M72"]=initial_value;
        trade_risk_record["912828N22"]=initial_value;
        trade_risk_record["912828M98"]=initial_value;
        trade_risk_record["912828M80"]=initial_value;
        trade_risk_record["912828M56"]=initial_value;
        trade_risk_record["912810RP5"]=initial_value;
        
    }
    
    virtual void AddPosition()
    {
        map<string,BondPosition>::iterator iter=B_pos_service.Position_list.begin();
        while(iter!=B_pos_service.Position_list.end())
        {
            double position_risk=iter->second.GetAggregatePosition()*risk_table[iter->first];
            
            PV01<Bond> position_pv(iter->second.GetProduct(),position_risk,iter->second.GetAggregatePosition());
        
            trade_risk_record[iter->first]=position_pv+trade_risk_record[iter->first];
            iter++;
            
        }
            
    }
    virtual PV01<Bond> & GetData(string key)
    {
        return trade_risk_record[key];
    }
    void PrintRisk()
    {
        map<string,PV01<Bond>>::iterator iter=trade_risk_record.begin();
        while(iter!=trade_risk_record.end())
        {
            cout<<iter->first<<" "<<iter->second.GetPV01()<<endl;
            iter++;
        }
    }
};


class BondRiskServiceListener :public RiskServiceListener<Bond>
{
private:
    BondRiskService &risk_service;
public:
    BondRiskServiceListener(BondRiskService &risk_0):risk_service(risk_0)
    {
        
    }
    virtual void ProcessAdd(PV01<Bond> &data)
    {
    
        string cusip=data.GetProduct().GetProductId();
        risk_service.trade_risk_record[cusip]=data+risk_service.trade_risk_record[cusip];
    }
    
};


#endif /* BondRiskService_h */

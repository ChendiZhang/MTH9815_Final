//
//  main.cpp
//  MTH9815_final
//
//  Created by Chendi Zhang on 12/16/16.
//  Copyright © 2016 Chendi Zhang. All rights reserved.
//

#include <iostream>
#include <fstream> 

#include "BondAlgoExecutionService.hpp"
#include "historicaldataservice.hpp"
#include "BondTradeBookingService.hpp"
#include "BondPositionService.hpp"
#include "BondStreamingService.hpp"
#include "BondMarketDataService.hpp" 
#include "BondRiskService.hpp"
#include "BondExecutionService.hpp"
#include "BondHistoricalDataService.hpp"




using namespace std;

int main(int argc, const char * argv[])
{
    BondTradeBookingService Y;
   
    
    //Trade Service
    BondTradeConnector x("trades.txt",Y);
    for(int i=0;i<60;i++)
        x.Publish();
    
    //Position Service
    BondPositionService position(Y);
    position.AddTrade();
    position.PrintPosition();
    
    //Risk Service
    BondRiskService risk(position);
    risk.AddPosition();
    risk.PrintRisk();
    
    //MarketData Service
    BondMarketDataService m_data_service;
    BondMarketDataConnector m_data_connector("marketdata.txt",m_data_service);
    for(int i=0;i<100;i++)
    {
        m_data_connector.Publish();
    }
    m_data_service.PrintMarketData();
    
    //Execution Service
    BondExecutionService   ex_service(m_data_service);
    ex_service.AddExecutionOrder();
    ex_service.PrintBondExecutionService();
    
    //Algo Service
    BondAlgoExecutionService algo_service(ex_service);
    algo_service.AlternativeStrategy();
    algo_service.PrintAlogExecution();
    
    //Price Service
    BondPricingService price_service;
    BondPricingConnector price_connector("prices.txt",price_service);
    for(int i=0;i<6;i++)
    price_connector.Publish();
    BondStreamingService stream_service(price_service);
    
    stream_service.PublishPrice();
    cout<<"stream stuff"<<endl;
    stream_service.PrintStream();
    
    
    //Historical Service
    BondHistoricalDataService h_service(risk,algo_service,stream_service);
    
    BondHistoricalDataConnector h_connector(h_service);
    //Output the file
    h_connector.PublishRisk();
    h_connector.PublishAlgo();
    h_connector.PublishStream();
    
    
    return 0;
}

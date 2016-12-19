
//  MTH9815_final
//
//  Created by Chendi Zhang on 12/16/16.
//  Copyright © 2016 Chendi Zhang. All rights reserved.
// 

#ifndef BondStreamingService_h
#define BondStreamingService_h
#include "streamingservice.hpp"
#include "products.hpp"
#include <unordered_map>
#include <fstream>
#include <string>
#include "BondPricingService.hpp"
using namespace std;

class BondStreamingService:public StreamingService<Bond>
{
private:
    
public:
    BondPricingService &_BondPricingService;
    map<string,PriceStream<Bond>> stream_record;
    
    BondStreamingService(BondPricingService &B_service):
    _BondPricingService(B_service){};
    
    
    
    PriceStream<Bond>& GetData(string cusip)
    {
        return stream_record[cusip];
    }
    
    //    BondStreamingService(){};
    PriceStream<Bond> GetBidOfferOrder(string cusip)
    {
        Bond bond(cusip);
        double midprice=_BondPricingService.GetData(cusip).GetMid();
        double spread=_BondPricingService.GetData(cusip).GetBidOfferSpread();
        long visible_quantity=1e+4;
        long hidden_quantity=1e+4;
        double bidprice=(midprice*2.0-spread)/2.0;
        double offerprice=midprice*2.0-bidprice;
        
        PriceStreamOrder bidorder(bidprice,visible_quantity,hidden_quantity,BID);
        PriceStreamOrder offerorder(offerprice,visible_quantity,hidden_quantity,OFFER);
        PriceStream<Bond> ans(bond, bidorder, offerorder);
        
        
        return ans;
        
    }
    virtual void OnMessage(PriceStream<Bond>& data)
    {
        string ID=data.GetProduct().GetProductId();
        stream_record.insert({ID,data});
        
    }
    void PublishPrice()
    {
        
        for(map<string,Price<Bond>>::iterator iter=_BondPricingService.price_record.begin(); iter!=_BondPricingService.price_record.end(); ++iter)
        {
            stream_record[iter->first]=GetBidOfferOrder(iter->first);
        }
        
    }
    void PrintStream()
    {
        map<string,PriceStream<Bond>>::iterator iter=stream_record.begin();
        while(iter!=stream_record.end())
        {
            cout<<iter->first<<" "<<iter->second.GetBidOrder().GetPrice()<<endl;
            iter++;
        }
    }
};

#endif /* BondStreamingService_h */

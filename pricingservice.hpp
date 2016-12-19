/**
 * pricingservice.hpp
 * Defines the data types and Service for internal prices.
 *
 * @author Breman Thuraisingham
 */
#ifndef PRICING_SERVICE_HPP
#define PRICING_SERVICE_HPP

#include <string>
#include "soa.hpp" 

/**
 * A price object consisting of mid and bid/offer spread.
 * Type T is the product type.
 */
template<typename T>
class Price
{
    
public:
    // ctor for a price
    Price(const T &_product, double _mid, double _bidOfferSpread);
    Price(const string cusip): product(T(cusip)){};
    Price():product(T("")){};
    Price<T>& operator=(Price<T>& source)
    {
        if(this==&source) return *this;
        //        product=source.product;
        return *this;
        
    }
    // Get the product
    const T& GetProduct() const;
    
    // Get the mid price
    double GetMid() const;
    
    // Get the bid/offer spread around the mid
    double GetBidOfferSpread() const;
    
    void PrintPrice()
    {
        cout<<GetProduct().GetProductId()<<" "<<GetMid()<<" "<<GetBidOfferSpread()<<endl;
    }
    
private:
    const T& product;
    double mid;
    double bidOfferSpread;
    
};

/**
 * Pricing Service managing mid prices and bid/offers.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class PricingService : public Service<string,Price <T> >
{
public:
    
};

template<typename T>
class PricingConnector: public Connector<Price<T>>
{
public:
    virtual void Publish(Price<T> &data)
    {};
    // Publish data to the Connector
    //    virtual void Publish(T &data) = 0;
};

template<typename T>
Price<T>::Price(const T &_product, double _mid, double _bidOfferSpread) :
product(_product)
{
    mid = _mid;
    bidOfferSpread = _bidOfferSpread;
}

template<typename T>
const T& Price<T>::GetProduct() const
{
    return product;
}

template<typename T>
double Price<T>::GetMid() const
{
    return mid;
}

template<typename T>
double Price<T>::GetBidOfferSpread() const
{
    return bidOfferSpread;
}
template <typename T>
class PricingServiceListener: public ServiceListener<Price<T>>
{
public:
    virtual void ProcessAdd(Price<T> &data){};
    
};



#endif

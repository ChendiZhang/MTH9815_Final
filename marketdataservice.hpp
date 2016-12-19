/**
 * marketdataservice.hpp
 * Defines the data types and Service for order book market data.
 *
 * @author Breman Thuraisingham
 */
#ifndef MARKET_DATA_SERVICE_HPP
#define MARKET_DATA_SERVICE_HPP

#include <string>
#include <vector> 
#include "soa.hpp"


using namespace std;

// Side for market data
enum PricingSide { BID, OFFER };

/**
 * A market data order with price, quantity, and side.
 */
class Order
{

public:

  // ctor for an order
    Order(double _price, long _quantity, PricingSide _side):price(_price),quantity(_quantity),side(_side){};
    Order(){};
    Order(const Order &copy)
    {
        price=copy.price;
        quantity=copy.quantity;
        side=copy.side;
    }
  // Get the price on the order
  double GetPrice() const
    {
        return price;
    }

  // Get the quantity on the order
  long GetQuantity() const
    {
        return quantity;
    }

  // Get the side on the order
  PricingSide GetSide() const
    {
        return side;
    }
    Order &operator=(const Order &source)
    {
        if(this==&source)
            return *this;
        else
        {
            price=source.price;
            quantity=source.quantity;
            side=source.side;
            return *this;
        }
        
    }

private:
  double price;
  long quantity;
  PricingSide side;

};

/**
 * Class representing a bid and offer order
 */
class BidOffer
{

public:

  // ctor for bid/offer
    BidOffer(const Order &_bidOrder, const Order &_offerOrder):bidOrder(_bidOrder), offerOrder(_offerOrder){};

  // Get the bid order
  const Order& GetBidOrder() const
    {
        return bidOrder;
    }

  // Get the offer order
  const Order& GetOfferOrder() const
    {
        return offerOrder;
    }

private:
  Order bidOrder;
  Order offerOrder;

};

/**
 * Order book with a bid and offer stack.
 * Type T is the product type.
 */
template<typename T>
class OrderBook
{

public:

  // ctor for the order book
    OrderBook(const T &_product, const vector<Order> &_bidStack, const vector<Order> &_offerStack):product(_product), bidStack(_bidStack), offerStack(_offerStack){};
    OrderBook(){};

  // Get the product
    const T& GetProduct() const
    {
        return product;
    }

  // Get the bid stack
    const vector<Order>& GetBidStack() const
    {
        return bidStack;
    }

  // Get the offer stack
    const vector<Order>& GetOfferStack() const
    {
        return offerStack;
    }

private:
  T product;
  vector<Order> bidStack;
  vector<Order> offerStack;

};

/**
 * Market Data Service which distributes market data
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class MarketDataService : public Service<string,OrderBook <T> >
{

public:
  
  // Get the best bid/offer order
    virtual BidOffer GetBestBidOffer(string &productId)=0;

  // Aggregate the order book
    virtual OrderBook<T> AggregateDepth(string &productId)=0;

};


template <typename T>
class MarketDataServiceListener: public ServiceListener<OrderBook<T>>
{
public:
    virtual void ProcessAdd(OrderBook<T> &data){};
    
};



template <typename T>
class MarketDataConnector: public Connector<OrderBook<T>>
{
    
};











#endif

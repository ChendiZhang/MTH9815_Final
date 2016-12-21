/**
 * positionservice.hpp
 * Defines the data types and Service for positions.
 *
 * @author Breman Thuraisingham
 */
#ifndef POSITION_SERVICE_HPP
#define POSITION_SERVICE_HPP

#include <string>
#include <map>
#include "soa.hpp" 
#include "tradebookingservice.hpp"

using namespace std;

/**
 * Position class in a particular book.
 * Type T is the product type.
 */
template<typename T>
class Position
{

public:

  // ctor for a position
  Position(const T &_product);
    Position(){};

  // Get the product
  const T& GetProduct() const;

 /* // Get the position quantity
  long GetPosition(string &book) const;
  */

  // Get the aggregate position
  long GetAggregatePosition();
  map<string,long> positions;
    
protected:
  T product;

};


/**
 * Position Service to manage positions across multiple books and secruties.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class PositionService : public Service<string,Position <T> >
{

public:

  
  // Add all trade to the service
    virtual void AddTrade()=0;
};

template<typename T>
Position<T>::Position(const T &_product) :
  product(_product)
{
}

template<typename T>
const T& Position<T>::GetProduct() const
{
  return product;
}

/*
template<typename T>
long Position<T>::GetPosition(string &book) const
{
  return positions[book];
}
*/

template<typename T>
long Position<T>::GetAggregatePosition()
{
    long position_sum=0;
    map<string,long>::iterator it=positions.begin();
    for(;it!=positions.end();it++)
    {
        position_sum+=it->second;
    }
  return position_sum;
}


#endif

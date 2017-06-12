#ifndef GW_CLASS_H
#define GW_CLASS_H

#include <iostream>
#include <vector>


using namespace std;

template < class Type>
class gw_automatic_vector
{
public:
    gw_automatic_vector();
    ~gw_automatic_vector() {}



   void add(Type item);
   Type read();


private:
    int index_iterator;
    std::vector<Type> items;

};


template <class Type >
gw_automatic_vector<Type>::gw_automatic_vector()
{
    index_iterator = 0;
}

template <class Type >
void gw_automatic_vector<Type>::add(Type item)
{
    items.push_back(item);
    index_iterator = items.size();

}

template <class Type >
Type gw_automatic_vector<Type>::read(){

   if(index_iterator < 0)
      index_iterator = items.size() - 1;
   return  items.at(index_iterator--);

 }





class gw_class
{
public:
    gw_class();
};






#endif // GW_CLASS_H

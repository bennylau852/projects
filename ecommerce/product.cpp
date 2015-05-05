#include <sstream>
#include <iomanip>
#include "product.h"

using namespace std;

Product::Product(const std::string category, const std::string name, double price, int qty) : 
  category_(category),
  name_(name),
  price_(price),
  qty_(qty)
{

}

Product::~Product()
{

}


double Product::getPrice() const
{
  return price_;
}

std::string Product::getName() const
{
  return name_;
}

void Product::subtractQty(int num)
{
  qty_ -= num;
}

int Product::getQty() const
{
  return qty_;
}

void Product::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}




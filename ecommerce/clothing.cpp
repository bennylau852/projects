#include <iomanip>
#include <sstream>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const string category, const string name, const string size, const string brand, double price, int qty) : Product (category, name, price, qty) 

/*

Inherits data members from Product class via initialization list because those data members are initialized first when Product constructor is called

*/

{
  size_ = size;
  brand_ = brand;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */ 

set<string> Clothing::keywords() const {

  set<string> type = parseStringToWords(name_);
  set<string> label = parseStringToWords(brand_);
  set<string> search_terms = setUnion(type, label);

  return search_terms;

}

string Clothing::displayString() const {

  stringstream ss;

  ss << price_;

  string cost = ss.str();

  stringstream ss2;

  ss2 << qty_;

  string quantity = ss2.str();

  string output = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + cost + " " + quantity + " left." + "\n";

  return output;

}

void Clothing::dump(ostream& os) const {

  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;

}




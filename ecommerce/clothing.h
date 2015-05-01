#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include "product.h"

class Clothing: public Product {
 public:
  Clothing(const std::string category, const std::string name, const std::string size, const std::string brand, double price, int qty); //Makes a Product object given product info as arguments for the constructor
 
  /**
   * Returns the appropriate keywords that this product should be associated with 
   */
  std::set<std::string> keywords() const;

  /**
   * Returns a string to display the product info for hits of the search. Call if user's keyword(s) mataches one belonging to this product 
   */
  std::string displayString() const;

  /**
   * Outputs the product info in the database format
   */
  void dump(std::ostream& os) const;
 
 private:
  std::string size_;
  std::string brand_;
};
#endif

#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Product{
 public:
  Product(const std::string category, const std::string name, double price, int qty); //Makes a Product object given product info as arguments for the constructor 
  virtual ~Product();

  /**
   * Returns the appropriate keywords that this product should be associated with 
   */
  virtual std::set<std::string> keywords() const = 0;

  /**
   * Returns a string to display the product info for hits of the search. Call if user's keyword(s) mataches one belonging to this product 
   */
  virtual std::string displayString() const = 0;

  /**
   * Outputs the product info in the database format
   */
  virtual void dump(std::ostream& os) const;

  /**
   * Accessors and mutators
   */

  double getPrice() const;
  std::string getName() const;
  int getQty() const;
  void subtractQty(int num);

  double average_rating;
 
 protected:
  std::string category_;
  std::string name_;
  double price_;
  int qty_;

};
#endif

#include <iomanip>
#include <sstream>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const string category, const string name, const string isbn, const string author, double price, int qty) : Product (category, name, price, qty) 

/*

Inherits data members from Product class via initialization list because those data members are initialized first when Product constructor is called

*/

{
  isbn_ = isbn;
  author_ = author;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */ 

set<string> Book::keywords() const {

  set<string> title = parseStringToWords(name_);
  set<string> writer = parseStringToWords(author_);
  set<string> search_terms = setUnion(title, writer); //Returns a combined set of both the book title and author to be used as keywords

  search_terms.insert(isbn_); //ISBN is given in product_parser.cpp so can be used verbatim 

  return search_terms;

}

string Book::displayString() const {

  stringstream ss;

  ss << price_;

  string cost = ss.str(); //Converts double to string

  stringstream ss2;

  ss2 << qty_;

  string quantity = ss2.str(); //Converts int to string

  string output = name_ + "\n" + "Author: " + author_ + " " + "ISBN: " + isbn_ + "\n" + cost + " " + quantity + " left." + "\n"; 

  return output;

}

void Book::dump(ostream& os) const {

  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl; 

}




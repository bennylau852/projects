#include <iomanip>
#include <sstream>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, const std::string genre, const std::string rating, double price, int qty) : Product (category, name, price, qty) //Gets data members from Product class via initialization list 

{
  genre_ = genre;
  rating_ = rating;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */ 

std::set<std::string> Movie::keywords() const {

  set<string> title = parseStringToWords(name_);
  set<string> type = parseStringToWords(genre_);
  set<string> search_terms = setUnion(title, type);
  return search_terms;

}

std::string Movie::displayString() const {

  stringstream ss;

  ss << price_;

  string cost = ss.str();

  stringstream ss2;

  ss2 << qty_;

  string quantity = ss2.str();

  string output = name_ + "\n" + "Genre: " + genre_ + " " + "Rating: " + rating_ + "\n" + cost + " " + quantity + " left." + "\n";

  return output;

}

void Movie::dump(std::ostream& os) const {

  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;

}



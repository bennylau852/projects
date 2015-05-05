#ifndef REVIEW_H
#define REVIEW_H
#include <string>
#include <sstream>

/**
 * Models a review for the product identified by prodName
 */
struct Review
{
  Review(); // :  prodName(), rating(), date(), reviewText() { }
  Review(std::string& prod, 
	 int& rate, 
   std::string user,
	 std::string& d, 
	 std::string& review_text); // : prodName(prod), rating(rate), date(d), reviewText(review_text) { }

  std::string displayString() const;

  void dump(std::ostream& os) const;
  
  std::string prodName;
  int rating;
  std::string username;
  std::string date;
  std::string reviewText;
};

#endif
#include "review.h"

using namespace std;

Review::Review() {


}

Review::Review (std::string& prod, int& rate, std::string user, std::string& d, std::string& review_text) : prodName(prod), rating(rate), username(user), date(d), reviewText(review_text) { 


}

string Review::displayString() const {

  stringstream ss;

  ss << rating;

  string score = ss.str(); //Converts int to string

  string output = prodName + "\n" + score + " " + username + " " + date + " " + reviewText + "\n"; 

  return output;

}

void Review::dump(ostream& os) const {

  	stringstream ss;

  	ss << rating;

  	string score = ss.str(); //Converts int to string

	os << prodName + "\n" + score + " " + username + " " + date + " " + reviewText + "\n"; 

}
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include <cctype>
#include "util.h"

using namespace std;

std::string convToLower(std::string src) 
{
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

/** Complete the code to convert a string containing a rawWord 
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWord) {

	string lower_case_raw_word = convToLower(rawWord); //Converts to lower case

	string temp;

	stringstream ss;

	ss << lower_case_raw_word; 

	set<string> key_words; //Dynamically allocated because needs to exist outside of function scope

	while (ss >> temp) {

		if (temp.size() > 1) {

        	for (unsigned int i = 0; i < temp.size(); i++) {

        		if (ispunct(temp[i])) { //Checks for punctuation 

        			string sub_str;

        			sub_str = temp.substr(0, i); //Creates a substring of the keyword before the punctuation 

        			if (sub_str.size() > 1) {

        				key_words.insert(sub_str); //Puts it into the set

        			}

        			temp.erase(0, i+1);

        			i = -1; //Starts from beginning of new curtailed string

        		}

        	}

        	if (temp.size() > 1) {

        		key_words.insert(temp); //Puts the word into the set of keywords

        	}

        }

	}

	return key_words; //Returns set of keywords 

}

/*

  std::string str = "We think in generalities, but we live in details.";
                                           // (quoting Alfred N. Whitehead)

  std::string str2 = str.substr (12,12);   // "generalities"

  std::size_t pos = str.find("live");      // position of "live" in str

  std::string str3 = str.substr (pos);     // get from "live" to the end

  std::cout << str2 << ' ' << str3 << '\n';

*/
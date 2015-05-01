#ifndef TAOBAO_H
#define TAOBAO_H
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include "user.h"
#include "product.h"
#include "datastore.h"

/** 
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 */
class TaoBao: public DataStore { //TaoBao is China's version of Amazon

 public:

  /**
   * Adds a product to the data store
   */
  void addProduct(Product* p); 
 
  /**
   * Adds a user to the data store
   */
  void addUser(User* u);


  void addReview(Review* r);

  /**
   * Performs a search of products whose keywords match the given "terms"
   *  type 0 = AND search (intersection of results for each term) while
   *  type 1 = OR search (union of results for each term)
   */
  std::vector<Product*> search(std::vector<std::string>& terms, int type);

  /**
   * Reproduce the database file from the current Products and User values
   */
  void dump(std::ostream& ofile);

  void add_to_cart(std::string username, int product_index, std::vector<Product*> goods); 

  void view_cart(std::string username); 

  void buy_cart(std::string username);

  std::map<const std::string, std::set<Product*> > word_bank; //Holds all keywords and a set of products that contain the keyword

  std::map<std::string, User*> customers; //Holds all customers in the database

  std::map<User*, std::queue<Product*> > users_cart; //Each customer has his/her own cart

  std::vector<Product*> all_products; //Holds all products in the database (for easier release allocation of memory)

  std::vector<Review*> all_reviews; //Holds all reviews in the database

  std::map<std::string, std::vector<Review*> > reviews_bank; //Holds a vector of Review* for each specific product THAT HAS a review(s)

};

#endif

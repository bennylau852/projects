#ifndef TAOBAO_H
#define TAOBAO_H
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include <sstream>
#include "user.h"
#include "product.h"
#include "datastore.h"
#include "util.h" //Set intersection
#include <cmath> //Absolute value
#include "heap.h"

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
   *  type 0 = AND search (intersection of results for each term) 
   *  type 1 = OR search (union of results for each term)
   */
  std::vector<Product*> search(std::vector<std::string>& terms, int type);

  void dump(std::ostream& ofile);

  void add_to_cart(std::string username, int product_index, std::vector<Product*> goods); 

  void view_cart(std::string username); 

  void buy_cart(std::string username);

  std::map<const std::string, std::set<Product*> > word_bank; //Holds all valid keywords and a set of products that contain the keyword

  std::map<std::string, User*> customers; //Holds all customers in the database

  std::map<User*, std::queue<Product*> > users_cart; //Each customer has his/her own cart

  std::vector<Product*> all_products; //Holds all products in the database

  std::vector<Review*> all_reviews; //Holds all reviews in the database

  std::map<std::string, std::vector<Review*> > reviews_bank; //Every product has its own vector of reviews 

  /*

  Additions

  */

  std::string hash_password(std::string password); //Hashes the password according to user input

  std::map<User*, std::set<Product*> > product_user_reviews; //Each customer has reviewed a set of products 

  double compute_similarity(User* A, User* B); //Calculates 1st degree similarity between two users

  void compute_similarity_for_all(); //Calculates 1st degree similarity for every user in database to every other user

  std::map<std::pair<std::string, std::string>, double> all_similarities; //Contains ith degree similarity for every user to every other user

  void dijkstra(User* login_account); //Calculates ith degree similarity from account holder to every other user

  Product* product_recommendation(User* account_holder); //Uses dijkstra to recommend product to user

  User* current_user; //Account holder (user who is logged in)

};

#endif

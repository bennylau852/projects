#include "taobao.h"
#include "util.h"
#include <cmath> //For password hash function

using namespace std;

void TaoBao::addProduct(Product* p) {

    set<string> search_terms = p->keywords(); //Finds all keywords that product contains

    for(set<string>::iterator it = search_terms.begin(); it != search_terms.end(); ++it) {

        if (word_bank.find(*it) == word_bank.end() ) { //If keyword doesn't currently exist in keyword database

            set<Product*> goods;

            goods.insert(p);

            word_bank.insert(make_pair(*it, goods)); //Insert keyword and corresponding product into the keyword database

        }

        else { //Keyword already exists in database and has a product or set of products that correspond to it

            string copy = *it; 

            map<string, set<Product*> >::iterator it = word_bank.find(copy);

            it->second.insert(p); //Adds given product to the set of products that keyword is paired with

        }

    }

    all_products.push_back(p); //Adds product into product database

}


void TaoBao::addUser(User* u) { 

    string username = u->getName();

    customers.insert(make_pair(username, u));

}

void TaoBao::addReview(Review* r) {

    string product_name = r->prodName;

    map<string, vector<Review*> >::iterator it = reviews_bank.find(product_name);

    if (it == reviews_bank.end()) { //Review for product currently does not exist

        vector<Review*> product_reviews;

        product_reviews.push_back(r);

        reviews_bank.insert(make_pair(product_name, product_reviews)); //Product now contains one review

    }

    else {

        it->second.push_back(r); //Added to the vector of reviews for corresponding product

    }

    all_reviews.push_back(r); //Adds review to review database

}

vector<Product*> TaoBao::search(vector<string>& terms, int type) {

    if (type == 0 || type == 1) {

        if (type == 0) { //AND search

            if (terms.size() == 1) { //Only 1 product corresponds to keywords

                string search_term = terms[0];

                map<string, set<Product*> >::iterator it = word_bank.find(search_term); //Attempts to find word in keyword database

                if (it == word_bank.end()) {

                    vector<Product*> empty;

                    return empty;

                }

                vector<Product*> products1((it->second).begin(), (it->second).end());

                return products1;

            }

            if (terms.size() > 1) { //More than 1 product corresponds to keywords

                string search_term1 = terms[0];

                string search_term2 = terms[1];

                map<string, set<Product*> >::iterator it1 = word_bank.find(search_term1);

                map<string, set<Product*> >::iterator it2 = word_bank.find(search_term2);

                if (it1 == word_bank.end() || it2 == word_bank.end()) { //Both keywords must be in keyword database

                    vector<Product*> empty;

                    return empty;

                }

                set<Product*> selected_products = setIntersection(it1->second, it2->second); //Products must contain both keywords

                vector<Product*> products2(selected_products.begin(), selected_products.end());

                if (terms.size() > 2) { //More than 2 products correspond to keywords

                    unsigned int counter = 2;

                    while (counter < terms.size()) {

                        string word = terms[counter];

                        map<string, set<Product*> >::iterator it = word_bank.find(word);

                        if (it == word_bank.end()) { //All keywords must belong in keyword database

                            vector<Product*> empty;

                            return empty;

                        }

                        set<Product*> added_set = it->second;

                        selected_products = setIntersection(selected_products, added_set);

                        counter++;

                    }

                    vector<Product*> products3(selected_products.begin(), selected_products.end());

                    return products3;

                }

                return products2;

            }

        }

        else if (type == 1) { //OR search

            if (terms.size() == 1) { //Only 1 product corresponds to keywords

                string search_term = terms[0];

                map<string, set<Product*> >::iterator it = word_bank.find(search_term); //Keyword must belong in keyword database

                if (it == word_bank.end()) {

                    vector<Product*> empty;

                    return empty;

                }

                vector<Product*> products1((it->second).begin(), (it->second).end());

                return products1;

            }

            if (terms.size() > 1) { //More than 1 product corresponds to keywords

                string search_term1 = terms[0];

                string search_term2 = terms[1];

                map<string, set<Product*> >::iterator it1 = word_bank.find(search_term1);

                map<string, set<Product*> >::iterator it2 = word_bank.find(search_term2);

                if (it1 == word_bank.end() && it2 == word_bank.end()) { //Products have to contain only one of the keywords

                    vector<Product*> empty;

                    return empty;

                }

                else if (it1 == word_bank.end()) { //Products only exist for second key term

                    if (terms.size() == 2) { 

                        vector<Product*> products2((it2->second).begin(), (it2->second).end());

                        return products2;

                    }

                    else {

                        set<Product*> combined_products = it2->second;

                    }

                }

                else if (it2 == word_bank.end()) { //Products only exist for first key term

                    if (terms.size() == 2) {

                        vector<Product*> products2((it1->second).begin(), (it1->second).end());

                        return products2;

                    }

                    else {

                        set<Product*> combined_products = it1->second;

                    }

                }

                else {

                    set<Product*> combined_products = setUnion(it1->second, it2->second);

                    vector<Product*> products2(combined_products.begin(), combined_products.end());

                    if (terms.size() > 2) {

                        unsigned int count = 2;

                        while (count < terms.size()) { //For however many keywords there are 

                            string word = terms[count];

                            map<string, set<Product*> >::iterator it = word_bank.find(word);

                            if (it != word_bank.end() ) { //Add products to vector only if the keyword exists in the database

                                set<Product*> added_set = it->second;

                                combined_products = setUnion(combined_products, added_set);

                            }

                            count++;

                        }

                        vector<Product*> products3(combined_products.begin(), combined_products.end());

                        return products3;

                    }

                    return products2;

                }

            }

            else {

                vector<Product*> empty;

                return empty;

            }

        }

    }

    vector<Product*> empty;

    return empty;

}

void TaoBao::dump(ostream& ofile) {

    ofile << "<products>" << endl;

    for (unsigned int i = 0; i < all_products.size(); i++) {

        all_products[i]->dump(ofile);

    }

    ofile << "</products>" << endl;

    ofile << "<users>" << endl;

    for (map<string, User*>::iterator it = customers.begin(); it != customers.end(); ++it) {

        it->second->dump(ofile);

    }

    ofile << "</users>" << endl;

    ofile << "<reviews>" << endl;

    for (map<string, vector<Review*> >::iterator it2 = reviews_bank.begin(); it2 != reviews_bank.end(); ++it2) {

        for (unsigned int i = 0; i < it2->second.size(); i++) {

            it2->second[i]->dump(ofile);

        }

    }

    ofile << "</reviews>" << endl;

}

void TaoBao::add_to_cart(string username, int product_index, vector<Product*> goods) {

    Product* item = goods[product_index-1];

    map<string, User*>::iterator it1 = customers.find(username);

    if (it1 != customers.end() ) {

        User* client = it1->second; 

        map<User*, queue<Product*> >::iterator it2 = users_cart.find(client);

        if (it2 == users_cart.end() ) { //User has an empty cart

            queue<Product*> cart;

            cart.push(item); //Puts product in the cart

            users_cart.insert(make_pair(client, cart)); //Makes a new cart

        }

        else { //User already has a cart

            it2->second.push(item); //Puts product in existing cart

        }

    }

}

void TaoBao::view_cart(string username) {

    map<string, User*>::iterator it1 = customers.find(username);

    if (it1 != customers.end() ) {

        User* client = it1->second;

        map<User*, queue<Product*> >::iterator it2 = users_cart.find(client);

        if (it2 != users_cart.end() ) {

            queue<Product*> temp_cart = it2->second; 

            int i = 1; //Hits must start at 1 and ascend

            while (temp_cart.size() > 0) { //Popping so refrain from for loops

                string product_info;

                Product* item;

                item = temp_cart.front();

                product_info = item->displayString();

                temp_cart.pop();

                i++;

            }

        }

    }

}

void TaoBao::buy_cart(string username) {

    vector<Product*> shopping_bag; //Helper data structure to maintain FIFO of cart queue

    map<string, User*>::iterator it1 = customers.find(username);

    if (it1 != customers.end() ) {

        User* client = it1->second;

        map<User*, queue<Product*> >::iterator it2 = users_cart.find(client);

        if (it2 != users_cart.end() ) {

            queue<Product*> temp_cart1 = it2->second; //Makes a copy of the customer's cart

            while(temp_cart1.size() > 0) {

                shopping_bag.push_back(temp_cart1.front()); //Fills bag with products in queue in the correct order

                temp_cart1.pop(); 

            }

            queue<Product*> temp_cart2 = it2->second;

            int counter = 0;

            while (temp_cart2.size() > 0) {

                Product* item = temp_cart2.front();

                    /*

                    Item is in stock and customer can pay for said item

                    */

                if (item->getQty() > 0 && client->getBalance() >= item->getPrice() ) {

                    double price = item->getPrice();

                    item->subtractQty(1);

                    client->deductAmount(price);

                    shopping_bag.erase(shopping_bag.begin() + counter); //Removes all purchased products from bag so only unpurchased products remain

                    counter--; //Maintains current count because all items after purchased item gets moves down one in bag

                }

                temp_cart2.pop();

                counter++;

            }

            map<User*, queue<Product*> >::iterator it3 = users_cart.find(client);

            while (it3->second.size() > 0) {

                it3->second.pop(); //Deletes everything from user's current cart

            }

            for (unsigned int i = 0; i < shopping_bag.size(); i++) {

                it3->second.push(shopping_bag[i]); //Fills user's cart with items unable to be purchased

            }

        }

    }

}

/*

Additions

*/

string TaoBao::hash_password(string password) {

    long long long_password = 0;

    int count = password.size()-1;

    for (unsigned int i = 0; i < password.size(); i++) {

        char character = password[i];

        int digit = (int)character;

        long long new_digit = digit * pow(128, count);

        long_password = long_password + new_digit;

        count--;

    }

    unsigned int array[4];

    for (int i = 0; i < 4; i++) {

        array[i] = 0;

    }

    int counter = 0;

    long long temp;

    int divisor = 65521;

    while (long_password != 0) {

        temp = long_password % divisor;

        array[counter] = temp;

        long_password = long_password/divisor;

        counter++;

    }

    int hashed_password = (45912 * array[3] + 35511 * array[2] + 65169 * array[1] + 4625 * array[0]) % 65521;

    stringstream ss;

    ss << hashed_password;

    string final_password;

    ss >> final_password;

    return final_password;

}

double TaoBao::compute_similarity(User* user_a, User* user_b) {

    vector<int> a_ratings;

    vector<int> b_ratings;

    vector<double> c_ratings;

    map<User*, std::set<Product*> >::iterator it1 = product_user_reviews.find(user_a); //Finds the set of products customer A has reviewed

    set<Product*> products_a;

    if (it1 != product_user_reviews.end()) {

        products_a = it1->second;

    }

    set<Product*>::iterator it_test;

    for (it_test = products_a.begin(); it_test != products_a.end(); it_test++) {

    }

    set<Product*> products_b;

    map<User*, std::set<Product*> >::iterator it2 = product_user_reviews.find(user_b); //Finds the set of products customer B has reviewed

    if (it2 != product_user_reviews.end()) {

        products_b = it2->second;

    }

    set<Product*>::iterator it_test2;

    for (it_test2 = products_b.begin(); it_test2 != products_b.end(); it_test2++) {

    }

    set<Product*> products_c = setIntersection(products_a, products_b); //Finds the set of products both customers have reviewed

    if (products_c.empty() ) {

        return 1.0;

    }

    set<Product*>::iterator it_test3;

    for (it_test3 = products_b.begin(); it_test3 != products_b.end(); it_test3++) {

    }

    vector<Product*> products_c_v(products_c.begin(), products_c.end()); //Copies the set of products over to a vector

    for (unsigned int i = 0; i < products_c_v.size(); i++) { //Goes through every product both customers have reviewed

        string current = products_c_v[i]->getName(); 

        map<string, vector<Review*> >::iterator it3 = reviews_bank.find(current); //Finds the reviews corresponding to the current product

        if (it3 != reviews_bank.end() ) {

            for (unsigned int j = 0; j < it3->second.size(); j++) { //Goes through every review for the current product

                if (it3->second[j]->username == user_a->getName() ) { //Customer A gave this review

                    a_ratings.push_back(it3->second[j]->rating);

                }

                if (it3->second[j]->username == user_b->getName() ) { //Customer B gave this review

                    b_ratings.push_back(it3->second[j]->rating);

                }

            }

            int a_current_rating = a_ratings.back();

            int b_current_rating = b_ratings.back();

            double simularity = (double) abs(a_current_rating - b_current_rating) / 4.0; 

            c_ratings.push_back(simularity);

            a_ratings.pop_back();

            b_ratings.pop_back();

        }

    }

    double total_simularity = 0.0;

    double counter = 0.0;

    double average_simularity = 1.0;

    while (c_ratings.size() > 0) {

        total_simularity = total_simularity + c_ratings.back();

        counter++;

        c_ratings.pop_back();

    }

    if (counter != 0.0) {

        average_simularity = total_simularity / counter;

    }

    if (average_simularity > 1.0) {

        return 1.0; //Minimum similarity

    }

    return average_simularity;

}

void TaoBao::compute_similarity_for_all() {

    for (map<string, User*>::iterator it_current_user = customers.begin(); it_current_user != customers.end(); ++it_current_user) { //For every user in database

        User* current_user = it_current_user->second;

        for (map<string, User*>::iterator it_current_neighbor = customers.begin(); it_current_neighbor != customers.end(); ++it_current_neighbor) { //For every neighbor of that user

            User* current_neighbor = it_current_neighbor->second;

            if (current_user != current_neighbor) { //Neighbor is not current user

                double similarity = compute_similarity(current_user, current_neighbor); //Computes 1st degree similarity

                pair<string, string> user_and_neighbor;

                user_and_neighbor = make_pair (current_user->getName(), current_neighbor->getName());

                all_similarities.insert(make_pair(user_and_neighbor, similarity));

            }

        }

    }

}

/*

All compatibilities between account holder and every other user are final after dijkstra

*/

void TaoBao::dijkstra(User* login_account) {

    compute_similarity_for_all(); //Computes the basic similarity between all users in the database

    min_heap min; //Minimum heap so the user with the best compatibility is prioritized

    pair<double, string> login_node; 

    string login_name = login_account->getName(); //Gets the name of the account holder

    login_node = make_pair(0.0, login_name); //Root node

    Heap<pair<double, string>, min_heap> priority_queue(2, min); //Creates a priority queue with a min heap as a comparator

    priority_queue.push(login_node); 

    set<string> closed_list; //Contains already processed nodes to avoid doubly processing

    /*

    Creates a basic similarity node between account holder and every other user in database and inserts it
    into the priority queue

    */

    for (map<string, User*>::iterator it_users = customers.begin(); it_users != customers.end(); ++it_users) {

        if (it_users->first != login_name) { 

            User* current_user = it_users->second;

            double similarity = compute_similarity(login_account, current_user);

            pair<double, string> new_node;

            new_node = make_pair (similarity, current_user->getName());

            priority_queue.push(new_node);

        }

    }

    while (!priority_queue.empty()) { //While there are still nodes to be processed

        pair<double, string> best_similarity_user = priority_queue.top(); //Top of priority queue is always the user with the best similarity

        double current_node_similarity = best_similarity_user.first; //Similarity score 

        string current_node_name = best_similarity_user.second; //Name of user

        closed_list.insert(current_node_name); //Marks node as processed 

        priority_queue.pop(); //Removes from queue

        /* 

        For every unprocessed user in the database (every user is connected to every other user to determine similarity)

        */

        for (map<string, User*>::iterator it_neighbors = customers.begin(); it_neighbors != customers.end(); ++it_neighbors) {

            set<string>::iterator it_closed = closed_list.find(it_neighbors->first); 

            if (it_closed == closed_list.end()) { //Not yet processed so valid user/neighbor

                string neighbor = it_neighbors->first; 

                /*

                Finds compatibility between current node and neighbor

                */

                map<pair<string, string>, double>::iterator it_current = all_similarities.find(make_pair(current_node_name, neighbor));

                double current_to_neighbor = it_current->second;

                /*

                Finds compatibility between login user and neighbor

                */

                map<pair<string, string>, double>::iterator it_login = all_similarities.find(make_pair(login_name, it_neighbors->first));

                double login_to_neighbor = it_login->second;

                /*

                If distance between current node and neighbor is closer than from login user to neighbor aka shorter path

                */

                if (current_node_similarity + current_to_neighbor < login_to_neighbor) {

                    double new_distance = current_node_similarity + current_to_neighbor;

                    set<pair<double, string> > temp_heap;

                    pair<double, string> updated_node;

                    updated_node = make_pair(new_distance, neighbor); //New neighbor node with an updated value (shorter path)

                    temp_heap.insert(updated_node); 

                    /*

                    Everything in priority queue is temporarily put into a set

                    */

                    while (!priority_queue.empty()) {

                        if (priority_queue.top().second != neighbor) {

                            temp_heap.insert(priority_queue.top());

                        }

                        priority_queue.pop();

                    }

                    set<pair<double, string> >::iterator it;

                    /*

                    Every node in the temporary set is put back into priority queue including the neighbor
                    recently processed 

                    */

                    for (it = temp_heap.begin(); it != temp_heap.end(); ++it) {

                        pair<double, string> new_node;

                        new_node = make_pair((*it).first, (*it).second);

                        priority_queue.push(new_node);

                        /*

                        Updates the compatibility value between login user and neighbor

                        */

                        map<pair<string, string>, double>::iterator it_account_holder = all_similarities.find(make_pair(login_name, it_neighbors->first));

                        it_account_holder->second = new_distance;

                        /*

                        Updates the compatibility value between neighbor and login user

                        */

                        map<pair<string, string>, double>::iterator it_updated_neighbor = all_similarities.find(make_pair(it_neighbors->first, login_name));

                        it_updated_neighbor->second = new_distance;

                    }

                }

            }

        }
    }

}

Product* TaoBao::product_recommendation(User* account_holder) { //Account holder is A

    dijkstra(account_holder);

    string account_name = account_holder->getName();

    /*

    Finds the set of products that the user has already reviewed

    */

    map<User*, set<Product*> >::iterator it_products = product_user_reviews.find(account_holder);

    vector<Product*> rec_products; //Stores the product with the highest interestingness

    double max_rec = 0.0; //Stores the interestingness score

    set<Product*> reviewed_products = it_products->second; //Products the user already reviewed

    unsigned int total_products = all_products.size(); //Gets total number of products in database

    if (reviewed_products.size() == total_products) { //User has reviewed (and bought) all products

        return NULL;

    }

    else {

        for (unsigned int i = 0; i < all_products.size(); i++) { //For all products in the database

            Product* current_product = all_products[i];

            double interestingness; //Score of how highly to recommend product to user

            double total_rec_for_product = 0.0; //Total ratings * Total similarity

            double total_similarity = 0.0; //Total similarity

            /*

            Checks if current product has been reviewed by user

            */

            set<Product*>::iterator it_reviewed_p = reviewed_products.find(current_product);

            if (it_reviewed_p == reviewed_products.end() ) { //Product has not been reviewed by user

                string product_name = current_product->getName(); //Gets the name of product

                /*

                Finds the reviews corresponding to the unreviewed (by user) product

                */

                map<string, vector<Review*> >::iterator it_reviews = reviews_bank.find(product_name);

                if (it_reviews != reviews_bank.end() ) { //Reviews for product exist

                    /*

                    //For every review for the product

                    */

                    for (unsigned int j = 0; j < it_reviews->second.size(); j++) {

                        string user = it_reviews->second[j]->username; //Gets username

                        int user_rating = it_reviews->second[j]->rating; //Gets rating

                        /*

                        Compares current user to another user

                        */

                        map<pair<string, string>, double>::iterator it_comp = all_similarities.find(make_pair(account_name, user));

                        double compatibility = it_comp->second; //The lower the better

                        double new_compatibility = 1.0 - compatibility; //The higher the better

                        double recommendation = (double) user_rating * new_compatibility; //Recommendation score from other user

                        total_rec_for_product = total_rec_for_product + recommendation; //Adds to total recommendation score

                        total_similarity = total_similarity + new_compatibility; //Adds to total similarity score

                    }

                }

                if (total_similarity == 0.0) {

                    interestingness = 0.0;

                }

                else {

                    interestingness = total_rec_for_product / total_similarity;

                }

                if (interestingness > max_rec) {

                    max_rec = interestingness;

                    if (rec_products.size() > 0) {

                        rec_products.pop_back();

                    }

                    rec_products.push_back(current_product);

                }

            }

        }

        if (rec_products.size() > 0) {

            return rec_products.back();

        }

        else {

            return NULL;

        }

    }

    return NULL;

}
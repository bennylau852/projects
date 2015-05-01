#include "taobao.h"
#include "util.h"

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

            string copy = *it; //Copy of the already existing keyword

            map<string, set<Product*> >::iterator it = word_bank.find(copy);

            it->second.insert(p); //Adds given product to the set of products that keyword is paired with

        }

    }

    all_products.push_back(p); //Adds product into database of all products

}


void TaoBao::addUser(User* u) { //Puts user in the user database with username as the key and pointer to user object as value

    string username = u->getName();

    customers.insert(make_pair(username, u));

}

void TaoBao::addReview(Review* r) {

    string product_name = r->prodName;

    map<string, vector<Review*> >::iterator it = reviews_bank.find(product_name);

    if (it == reviews_bank.end()) {

        vector<Review*> product_reviews;

        product_reviews.push_back(r);

        reviews_bank.insert(make_pair(product_name, product_reviews));

    }

    else {

        it->second.push_back(r);

    }

    all_reviews.push_back(r);

}

vector<Product*> TaoBao::search(vector<string>& terms, int type) {

    if (type == 0 || type == 1) {

        if (type == 0) { //AND

            if (terms.size() == 1) {

                string search_term = terms[0];

                map<string, set<Product*> >::iterator it = word_bank.find(search_term);

                if (it == word_bank.end()) {

                    vector<Product*> empty;

                    return empty;

                }

                vector<Product*> products1((it->second).begin(), (it->second).end());

                return products1;

            }

            if (terms.size() > 1) {

                string search_term1 = terms[0];

                string search_term2 = terms[1];

                map<string, set<Product*> >::iterator it1 = word_bank.find(search_term1);

                map<string, set<Product*> >::iterator it2 = word_bank.find(search_term2);

                if (it1 == word_bank.end() || it2 == word_bank.end()) {

                    vector<Product*> empty;

                    return empty;

                }

                set<Product*> selected_products = setIntersection(it1->second, it2->second);

                vector<Product*> products2(selected_products.begin(), selected_products.end());

                if (terms.size() > 2) {

                    unsigned int counter = 2;

                    while (counter < terms.size()) {

                        string word = terms[counter];

                        map<string, set<Product*> >::iterator it = word_bank.find(word);

                        if (it == word_bank.end()) {

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

        else if (type == 1) { //OR

            if (terms.size() == 1) {

                string search_term = terms[0];

                map<string, set<Product*> >::iterator it = word_bank.find(search_term);

                if (it == word_bank.end()) {

                    vector<Product*> empty;

                    return empty;

                }

                vector<Product*> products1((it->second).begin(), (it->second).end());

                return products1;

            }

            if (terms.size() > 1) {

                string search_term1 = terms[0];

                string search_term2 = terms[1];

                map<string, set<Product*> >::iterator it1 = word_bank.find(search_term1);

                map<string, set<Product*> >::iterator it2 = word_bank.find(search_term2);

                if (it1 == word_bank.end() && it2 == word_bank.end()) {

                    vector<Product*> empty;

                    return empty;

                }

                else if (it1 == word_bank.end()) {

                    if (terms.size() == 2) {

                        vector<Product*> products2((it2->second).begin(), (it2->second).end());

                        return products2;

                    }

                    else {

                        set<Product*> combined_products = it2->second;

                    }

                }

                else if (it2 == word_bank.end()) {

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

                        while (count < terms.size()) {

                            string word = terms[count];

                            map<string, set<Product*> >::iterator it = word_bank.find(word);

                            set<Product*> added_set = it->second;

                            combined_products = setUnion(combined_products, added_set);

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

    if (it1 != customers.end() ) { //Customer exists in database

        User* client = it1->second; //Gets customer info

        map<User*, queue<Product*> >::iterator it2 = users_cart.find(client);

        if (it2 == users_cart.end() ) {

            queue<Product*> cart;

            cart.push(item); //Puts product in the cart

            users_cart.insert(make_pair(client, cart)); //Makes a new cart for given customer

        }

        else { //User already has a cart

            it2->second.push(item); //Puts product in the cart

        }

    }

}

void TaoBao::view_cart(string username) {

    map<string, User*>::iterator it1 = customers.find(username);

    if (it1 != customers.end() ) {

        User* client = it1->second;

        map<User*, queue<Product*> >::iterator it2 = users_cart.find(client);

        if (it2 != users_cart.end() ) {

            queue<Product*> temp_cart = it2->second; //Makes a copy of the customer's cart

            int i = 1; //Hits must start at 1 and ascend

            while (temp_cart.size() > 0) { //Don't use for loops for queues (since you're poping)!

                string product_info;

                Product* item;

                cout << "Item" << " " << i << " " << endl;

                item = temp_cart.front();

                product_info = item->displayString();

                cout << product_info << endl;

                temp_cart.pop();

                i++;

            }

        }

    }

}

void TaoBao::buy_cart(string username) {

    vector<Product*> booty; //Helper data structure to help maintain FIFO of cart queue

    map<string, User*>::iterator it1 = customers.find(username);

    if (it1 != customers.end() ) {

        User* client = it1->second;

        map<User*, queue<Product*> >::iterator it2 = users_cart.find(client);

        if (it2 != users_cart.end() ) {

            queue<Product*> temp_cart1 = it2->second; //Makes a copy of the customer's cart

            while(temp_cart1.size() > 0) {

                booty.push_back(temp_cart1.front()); //Fills vector with Product* in queue in the correct order

                temp_cart1.pop(); //FIFO

            }

            queue<Product*> temp_cart2 = it2->second;

            int counter = 0;

            while (temp_cart2.size() > 0) {

                Product* item = temp_cart2.front();

                if (item->getQty() > 0 && client->getBalance() >= item->getPrice() ) {

                    /*

                    Item is in stock and customer can pay for said item

                    */

                    double price = item->getPrice();

                    item->subtractQty(1);

                    client->deductAmount(price);

                    booty.erase(booty.begin() + counter); //Erase all purchased items from the vector so only unpurchased items remain

                    counter--; //Maintains current count because all items after purchased item gets moved down one in the vector

                }

                temp_cart2.pop();

                counter++;

            }

            map<User*, queue<Product*> >::iterator it3 = users_cart.find(client);

            while (it3->second.size() > 0) {

                it3->second.pop(); //Deletes everything from user's current cart

            }

            for (unsigned int i = 0; i < booty.size(); i++) {

                it3->second.push(booty[i]); //Fills customer's cart with items he/she was not able to purchase (if any)

            }

        }

    }

}


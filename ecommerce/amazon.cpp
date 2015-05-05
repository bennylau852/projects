#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
/** Add other #includes here **/
#include "taobao.h"
#include <map>
#include "review.h"

#include "main_window.h"
#include <QApplication>

using namespace std;

void displayProducts(vector<Product*>& hits, TaoBao& ds);

int main(int argc, char* argv[]) {

    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
    }

    TaoBao ds; //TaoBao is China's version of Amazon


    // Instantiate the parser
    DBParser parser;

    // Instantiating the individual product parsers 
    parser.addProductParser(new ProductBookParser);
    parser.addProductParser(new ProductClothingParser);
    parser.addProductParser(new ProductMovieParser);

    if( parser.parse(argv[1], ds) ) {

        cerr << "Error parsing!" << endl;

        return 1;

    }

    /*

    1) Computes average rating for all products in database

    2) For each review, gets the customer name and adds it to a data structure keeping track of users
        and the products they reviewed

    */

    for (unsigned int i = 0; i < ds.all_products.size(); i++) { //For each product in the database

        string product_name = ds.all_products[i]->getName(); 

        double sum = 0.0;

        double counter = 0.0;

        double average_rating = 0.0; //By default is 0 if no reviews

        string name;

        string name2;

        map<string, vector<Review*> >::iterator it = ds.reviews_bank.find(product_name); 

        if (it != ds.reviews_bank.end()) { //If reviews for the current product exist

            for (unsigned int j = 0; j < it->second.size(); j++) { 

                sum += it->second[j]->rating; //Adds the rating from each review to a running sum

                counter++;

                name = it->second[j]->username; 

                map<string, User*>::iterator it11 = ds.customers.find(name); //Finds the user who wrote the review

                if (it11 != ds.customers.end() ) { 

                    User* current_user_for_review = it11->second; 

                    map<User*, set<Product*> >::iterator it12 = ds.product_user_reviews.find(current_user_for_review); //Finds the set of products that the user has reviewed

                    if (it12 == ds.product_user_reviews.end() ) { //If the set currently does not exist

                        set<Product*> cart; 

                        cart.insert(ds.all_products[i]); 

                        ds.product_user_reviews.insert(make_pair(current_user_for_review, cart)); //Makes a new set

                    }

                    else { 

                        it12->second.insert(ds.all_products[i]); //Puts product in user's existing product set

                    }

                }

            }

            if (sum != 0.0) {

                average_rating = sum/counter;  

            }

        }

        ds.all_products[i]->average_rating = average_rating; //Equals either the average of all ratings or 0

    }

    QApplication app(argc, argv);

    bool not_hacker = false;

    MainWindow mainwindow_login(ds, &not_hacker);

    mainwindow_login.show();

    app.exec();

    if (not_hacker == true) {

    MainWindow mainwindow(ds);

    mainwindow.show();

    app.exec();

    }

    /*

    //Deletes all users in the database

    for(map<string, User*>::iterator it = ds.customers.begin();
            it != ds.customers.end();
            ++it) {
        delete it->second;
    }

    //Deletes all products in the database

    for (unsigned int i = 0; i < ds.all_products.size(); i++) {

        delete ds.all_products[i];

    }

    //Deletes all reviews in the database

    for (unsigned int i = 0; i < ds.all_reviews.size(); i++) {

        delete ds.all_reviews[i];

    }

    */

    return 0;

}

void displayProducts(vector<Product*>& hits, TaoBao& ds) {

    int resultNo = 1;

    for(vector<Product*>::iterator it1 = hits.begin(); it1 != hits.end(); ++it1) {

        cout << "Hit " << setw(3) << resultNo << endl;

        cout << (*it1)->displayString() << endl;

        cout << endl;

        resultNo++;

        string product_name = (*it1)->getName();

        map<string, vector<Review*> >::iterator it2 = ds.reviews_bank.find(product_name);

        if (it2!= ds.reviews_bank.end()) {

            vector<Review*> product_reviews = it2->second;

            for (unsigned int i = 0; i < product_reviews.size(); i++) {

                cout << product_reviews[i]->displayString() << endl;

            }

        }

        else {

            cout << "No reviews yet" << endl;

        }

    }
}

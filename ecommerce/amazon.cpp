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

/* Prototypes */
void displayProducts(vector<Product*>& hits, TaoBao& ds);

int main(int argc, char* argv[]) {

    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    TaoBao ds; //TaoBao is China's version of Amazon


    // Instantiate the parser
    DBParser parser;

    // Instantiate the individual product parsers we want
    parser.addProductParser(new ProductBookParser);
    parser.addProductParser(new ProductClothingParser);
    parser.addProductParser(new ProductMovieParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {

        cerr << "Error parsing!" << endl;

        return 1;

    }

    //Computes and assigns the average rating of all products in the database

    for (unsigned int i = 0; i < ds.all_products.size(); i++) { 

        string product_name = ds.all_products[i]->getName(); 

        int sum = 0;

        int counter = 0;

        int average_rating = 0;

        map<string, vector<Review*> >::iterator it = ds.reviews_bank.find(product_name); //Finds the vector of reviews (if any) for the given product

        if (it != ds.reviews_bank.end()) {

            for (unsigned int j = 0; j < it->second.size(); j++) {

                sum += it->second[j]->rating; //Adds the rating from each review to the sum

                counter++;

            }

            average_rating = sum/counter;

        }

        ds.all_products[i]->average_rating = average_rating; //Equals either the average of all ratings or 0

    }

    QApplication app(argc, argv);

    MainWindow mainwindow(ds);

    mainwindow.show();

    app.exec();

    /*

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;

    bool done = false;
    while(!done) {
        cout << "\nEnter search terms: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                if (hits.size() == 0) {

                    cout << "Not found. Try Again" << endl;

                    continue;

                }
                displayProducts(hits, ds);
            } else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                if (hits.size() == 0) {

                    cout << "Not found. Try Again" << endl;

                    continue;

                }
                displayProducts(hits, ds);
            } else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }

            //ADD support for other command here

            else if ( cmd == "ADD") {
                string name;
                int index;
                ss >> name;
                ss >> index;
                ds.add_to_cart(name, index, hits);
            } else if ( cmd == "VIEWCART") {
                string name;
                ss >> name;
                ds.view_cart(name);
            }

            else if ( cmd == "BUYCART") {
                string name;
                ss >> name;
                ds.buy_cart(name);
            } else if ( cmd == "QUIT") {
                string filename;
                ss >> filename;
                ofstream ofile (filename.c_str());
                ds.dump(ofile);
                ofile.close();

                for (unsigned int i = 0; i < ds.all_products.size(); i++) {

                    delete ds.all_products[i];

                }

                for(map<string, User*>::iterator it = ds.customers.begin();
                        it != ds.customers.end();
                        ++it) {
                    delete it->second;
                }

                for (unsigned int i = 0; i < ds.all_reviews.size(); i++) {

                    delete ds.all_reviews[i];

                }

                return 0;

            }

            else {
                cout << "Unknown command" << endl;
            }
        }

    }

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

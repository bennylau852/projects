#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//QT libraries
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QTextEdit>
#include <QListWidget>
#include <QDesktopWidget>
#include <QDate>

//C++ libraries
#include <iostream>
#include <iomanip> 
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "taobao.h" //For instantianting data store and accessing data member functions
#include "product.h" //For accessing product member functions
#include "review.h" //For instantiating review objects
#include "mergesort.h" //To mergesort product and review matches
#include "user.h" //For accessing user member functions
#include <wctype.h>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow();
    MainWindow(TaoBao& datastore);
    MainWindow(TaoBao& passed_datastore, std::string user);
    MainWindow(TaoBao& datastore, bool* not_hacker);
    ~MainWindow();

private:

    //Datastore pointer 
    TaoBao* ds;

    //Overall layout of GUI
    QVBoxLayout* overall_layout;

    //Greeting layout
    QHBoxLayout* greeting_layout;
    QLabel* greeting;

    //Main layout for products and search
    QHBoxLayout* search_interface;

    //Product recommendation layout
    QVBoxLayout* product_rec_layout; 
    QLabel* product_rec_label;
    QListWidget* product_rec_list;
    QPushButton* product_rec_button;

    //Product information layout
    QVBoxLayout* product_layout;
    QLabel* display_product_info;

    //List of product matches layout
    QVBoxLayout* product_matches_layout; 
    QLabel* product_matches_label; 
    QListWidget* product_matches_list;

    //Main layout for search 
    QVBoxLayout* search_layout;

    //Search input layout
    QLineEdit* search_entries;
    QPushButton* search_button;

    //And/Or button layout 
    QHBoxLayout* and_or_layout;
    QRadioButton* and_button;
    QRadioButton* or_button;
    bool and_;
    bool or_;

    //Sort search layout
    QHBoxLayout* sort_search_layout;
    QLabel* sort_label;
    QPushButton* alphabet; 
    QPushButton* rating;

    //Cart layout
    QHBoxLayout* cart_options_layout;
    QPushButton* add_cart_button;
    QPushButton* view_cart_button;

    //Output to file
    QPushButton* save_database;
    QLineEdit* output_file;

    //Close QT window
    QHBoxLayout* exit_store_layout;
    QPushButton* exit_store_button;

    //Main layout for reviews
    QHBoxLayout* review_interface;

    //Selected review layout
    QVBoxLayout* selected_review_layout;
    QLabel* selected_review_label;
    QLabel* selected_review_info;

    //List of reviews found
    QListWidget* list_of_reviews; 

    //Overall form layout
    QVBoxLayout* overall_add_review_layout;

    //Form date layout
    QHBoxLayout* date_layout;
    QLabel* date_format;
    QLineEdit* date_input;

    //Form rating layout
    QHBoxLayout* rating_layout;
    QLabel* rating_format;
    QLineEdit* rating_input;

    //Form add review layout
    QHBoxLayout* review_text_layout;
    QLabel* review_text_label;
    QTextEdit* review_text_input;

    //Add new review
    QPushButton* add_review_button;

    //Stores search matches
    std::vector<Product*> product_matches;

    //Stores review matches
    std::vector<Review*> reviews_for_current_product;

    //User_Cart
    std::string customer_name;
    QLabel* customer_cart;
    QListWidget* list_of_cart_products;
    QPushButton* buy_cart_button;
    QPushButton* close_cart_window_button;
    QPushButton* remove_product_button;
    vector<Product*> cart_products;

    /*

    For login window

    */

    QVBoxLayout* login_layout;

    QHBoxLayout* login_greeting_layout;

    QHBoxLayout* request_layout;

    QLabel* login_greeting;

    QLabel* request;

    QHBoxLayout* user_input_layout;

    QVBoxLayout* user_layout;

    QLabel* user_label;

    QLineEdit* username;

    QVBoxLayout* password_layout;

    QLabel* password_label;

    QLineEdit* password;

    QHBoxLayout* buttons_layout;

    QPushButton* login_button;

    QPushButton* quit_button;

    //QPushButton* new_user_button;

    QLabel* incorrect;

    QHBoxLayout* incorrect_layout;

    //Determines whether or not to instantiate main window
    bool* not_hack;

    //Account holder 
    User* user;

    //Product to be recommended to the account holder
    Product* top_product;

public slots:

    void and_search();

    void or_search();

    void search_taobao();

    void display_product_information(int productIndex);

    void add_product_rec_to_cart();

    void add_user_cart();

    void view_user_cart();

    void buy_user_cart();

    void remove_from_user_cart();

    void sort_by_average_rating();

    void sort_alphabetically();

    void get_reviews_for_product();

    void display_selected_review(int reviewIndex);

    void add_new_review();

    void save_to_file();

    /*

    Additions

    */


    void verify_user();

};
#endif

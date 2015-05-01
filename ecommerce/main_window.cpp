#include "main_window.h" 
#include "util.h" //To access the convToLower member function

using namespace std;

MainWindow::MainWindow() {

}

MainWindow::MainWindow(TaoBao& datastore) { //For instantiating the main QT window

    ds = &datastore;

    is_main = true;

    //Gets reference to datastore object instantiated in main

    //Overall layout of GUI
    overall_layout = new QVBoxLayout();

    //Greeting layout 
    greeting_layout = new QHBoxLayout();
    overall_layout->addLayout(greeting_layout);

    //Greeting message
    greeting = new QLabel("Welcome to TaoBao, China's biggest ecommerce merchant");
    greeting_layout->addWidget(greeting);

    //Main products and search layout
    search_interface = new QHBoxLayout();
    overall_layout->addLayout(search_interface);

    //Customers layout
    customers_layout = new QVBoxLayout();
    search_interface->addLayout(customers_layout);

    //Customers label
    customers_label = new QLabel("Please select your account");
    customers_layout->addWidget(customers_label);

    //List of customers in database
    customers_list = new QListWidget();
    customers_layout->addWidget(customers_list);

    //Adds each customer in the database into the list

    for (map<string, User*>::iterator it = ds->customers.begin(); it != ds->customers.end(); ++it) {

        customers_list->addItem(QString::fromStdString(it->first));

    }

    //List of product matches layout
    product_matches_layout = new QVBoxLayout();
    search_interface->addLayout(product_matches_layout);

    //Product matches label
    product_matches_label = new QLabel("Your search returned");
    product_matches_layout->addWidget(product_matches_label);

    //List of product matches
    product_matches_list = new QListWidget();
    product_matches_layout->addWidget(product_matches_list);

    //Displays the information of the current product selected
    connect(product_matches_list, SIGNAL(currentRowChanged(int)), this, SLOT(display_product_information(int)));

    //Current product information layout
    product_layout = new QVBoxLayout();
    search_interface->addLayout(product_layout);

    //Current product information string
    display_product_info = new QLabel(" ");
    product_layout->addWidget(display_product_info);

    //Floats the string to the top
    product_layout->addStretch();

    //Main reviews layout
    review_interface = new QHBoxLayout();
    overall_layout->addLayout(review_interface);

    //Current review layout
    selected_review_layout = new QVBoxLayout();
    review_interface->addLayout(selected_review_layout);

    //Current review label
    selected_review_label = new QLabel("Review information");
    selected_review_layout->addWidget(selected_review_label);

    //List of reviews for current product
    list_of_reviews = new QListWidget();
    review_interface->addWidget(list_of_reviews);

    //Gets the reviews for the current product selected
    connect(product_matches_list, SIGNAL(currentRowChanged(int)), this, SLOT(get_reviews_for_product()));

    //Current review string
    selected_review_info = new QLabel("");
    selected_review_layout->addWidget(selected_review_info);

    //Floats the string to the top
    selected_review_layout->addStretch();

    //Displays the information of the current review selected
    connect(list_of_reviews, SIGNAL(currentRowChanged(int)), this, SLOT(display_selected_review(int)));

    //Add new review layout
    overall_add_review_layout = new QVBoxLayout();
    review_interface->addLayout(overall_add_review_layout);

    //Date input layout
    date_layout = new QHBoxLayout();
    overall_add_review_layout->addLayout(date_layout);

    //Date input label
    date_format = new QLabel("Enter date in format yyyy-mm-dd");
    date_layout->addWidget(date_format);

    //Date input box
    date_input = new QLineEdit();
    date_layout->addWidget(date_input);

    //Rating input layout
    rating_layout = new QHBoxLayout();
    overall_add_review_layout->addLayout(rating_layout);

    //Rating input label
    rating_format = new QLabel("Enter rating 1-5");
    rating_layout->addWidget(rating_format);

    //Rating input box
    rating_input = new QLineEdit();
    rating_layout->addWidget(rating_input);

    //Review text input layout
    review_text_layout = new QHBoxLayout();
    overall_add_review_layout->addLayout(review_text_layout);

    //Review text input label
    review_text_label = new QLabel("Enter review here");
    review_text_layout->addWidget(review_text_label);

    //Review text input box
    review_text_input = new QTextEdit();
    review_text_layout->addWidget(review_text_input);

    //Review button
    add_review_button = new QPushButton("Add new review");
    overall_add_review_layout->addWidget(add_review_button);

    //Adds a new review to the database
    connect(add_review_button, SIGNAL(clicked()), this, SLOT(add_new_review()));

    //Main search layout
    search_layout = new QVBoxLayout();
    search_interface->addLayout(search_layout);

    //Adds an empty dialog box for a more pleasing interface
    search_layout->addSpacing(50); 

    //Search words input box
    search_entries = new QLineEdit();
    search_layout->addWidget(search_entries);

    //Search words input button 
    search_button = new QPushButton("Search");
    search_layout->addWidget(search_button);

    //Searches through the TaoBao object for products that fulfill the search requirements
    connect(search_button, SIGNAL(clicked()), this, SLOT(search_taobao()));

    //And/Or buttons layout
    and_or_layout = new QHBoxLayout();
    search_layout->addLayout(and_or_layout);

    //And button 
    and_button = new QRadioButton("AND");
    and_or_layout->addWidget(and_button);

    //Adds the pre-requisite of the "and" keyword condition
    connect(and_button, SIGNAL(clicked()), this, SLOT(and_search()));

    //Or button
    or_button = new QRadioButton("OR");
    and_or_layout->addWidget(or_button);

    //Adds the pre-requisite of the "or" keyword condition
    connect(or_button, SIGNAL(clicked()), this, SLOT(or_search()));

    //Sorting searches results
    sort_search_layout = new QHBoxLayout();
    search_layout->addLayout(sort_search_layout);

    //Sorting searches label
    sort_label = new QLabel("Choose to sort:");
    sort_search_layout->addWidget(sort_label);

    //Sort searches by alphabet button
    alphabet = new QPushButton("Alphabetically");
    sort_search_layout->addWidget(alphabet);

    //Sorts current searches alphabetically
    connect(alphabet, SIGNAL(clicked()), this, SLOT(sort_alphabetically()));

    //Sort searches by rating button
    rating = new QPushButton("By rating (highest to lowest)");
    sort_search_layout->addWidget(rating);

    //Sorts current searches by average rating from highest to lowest
    connect(rating, SIGNAL(clicked()), this, SLOT(sort_by_average_rating()));

    //Cart button options layout
    cart_options_layout = new QHBoxLayout();
    search_layout->addLayout(cart_options_layout);

    //Add to user cart button 
    add_cart_button = new QPushButton("Add Cart");
    cart_options_layout->addWidget(add_cart_button);

    //Adds current product to the current user's cart
    connect(add_cart_button, SIGNAL(clicked()), this, SLOT(add_user_cart()));

    //View user cart button
    view_cart_button = new QPushButton("View Cart");
    cart_options_layout->addWidget(view_cart_button);

    //Instantiates a new QT main window for the view cart window
    connect(view_cart_button, SIGNAL(clicked()), this, SLOT(view_user_cart()));

    //Save to database button
    save_database = new QPushButton("Save database to file");
    search_layout->addWidget(save_database);

    //Saves the current database to the given output file
    connect(save_database, SIGNAL(clicked()), this, SLOT(save_to_file()));

    //Output file input box
    output_file = new QLineEdit();
    search_layout->addWidget(output_file);

    //Exit store layouts
    exit_store_layout = new QHBoxLayout();
    search_layout->addLayout(exit_store_layout);

    //Exit store button
    exit_store_button = new QPushButton("Exit Store");
    exit_store_layout->addWidget(exit_store_button);

    //Exits back to main where QT main window was first shown/executed
    connect(exit_store_button, SIGNAL(clicked()), this, SLOT(close()));

    //No search preferences to begin with (neither "and" nor "or")

    and_ = false;

    or_ = false;

    //Changes QT main window size

    resize(QDesktopWidget().availableGeometry(this).size() * 0.9);

    //Sets the overall layout of QT main window

    setLayout(overall_layout);

}

MainWindow::MainWindow(TaoBao& passed_datastore, string user) {

    ds = &passed_datastore;

    is_main = false;

    customer_name = user;

    overall_layout = new QVBoxLayout(); //Instantiates the overall layout for this QT window

    string customer = "This is " + customer_name + "'s cart";

    customer_cart = new QLabel(QString::fromStdString(customer));

    overall_layout->addWidget(customer_cart);

    list_of_cart_products = new QListWidget();

    overall_layout->addWidget(list_of_cart_products); //Adds the cart list to the overall layout

    buy_cart_button = new QPushButton("Buy cart");

    overall_layout->addWidget(buy_cart_button); //Adds the buy cart button to the overall layout

    connect(buy_cart_button, SIGNAL(clicked()), this, SLOT(buy_user_cart())); //Calls buy cart function when buy cart button is pressed

    close_cart_window_button = new QPushButton("Close");

    overall_layout->addWidget(close_cart_window_button); //Adds the exit cart button to the overall layout

    connect(close_cart_window_button, SIGNAL(clicked()), this, SLOT(close())); //Calls the close window function when the exit cart button is pressed

    remove_product_button = new QPushButton("Remove Item");

    overall_layout->addWidget(remove_product_button); //Adds the remove product button to the overall layout

    connect(remove_product_button, SIGNAL(clicked()), this, SLOT(remove_from_user_cart())); //Calls the remove from user cart function when remove product button is pressed

    //Instantiates a copy of the user's cart from the database to fill the list up with

    map<string, User*>::iterator it1 = passed_datastore.customers.find(customer_name); 

    if (it1 != passed_datastore.customers.end() ) {

        User* client = it1->second; //Finds corresponding User* for customer

        map<User*, queue<Product*> >::iterator it2 = passed_datastore.users_cart.find(client);

        if (it2 != passed_datastore.users_cart.end() ) { //One already exists for each customer who presses add cart

            queue<Product*> temp_cart = it2->second; //Makes a copy of the customer's cart

            while (temp_cart.size() > 0) { //Don't use for loops for queues (since you're poping)!

                string product_info2;

                Product* item;

                item = temp_cart.front(); 

                product_info2 = item->getName();

                list_of_cart_products->addItem(QString::fromStdString(product_info2)); //Adds item to list of user's cart

                cart_products.push_back(item); //Pushes product* into a new temp array;

                temp_cart.pop();

            }

        }

    }

    setLayout(overall_layout);

}

MainWindow::~MainWindow() {

}

void MainWindow::and_search() {

    and_ = true;

    or_ = false;
}

void MainWindow::or_search() {

    and_ = false;

    or_ = true;

}

void MainWindow::search_taobao() {

    string user_input = search_entries->text().toStdString(); //Gets a string version of the search input

    if (user_input.size() == 0) {

        return; //Returns if no words entered

    }

    if (product_matches.size() > 0) {

        while (product_matches.size() > 0) {

            product_matches.pop_back(); //Erases all products in product matches vector

        }

        product_matches_list->clear(); //Clears all items in list of product matches from search

        display_product_info->setText("");

    }

    if (reviews_for_current_product.size() > 0) {

        while (reviews_for_current_product.size() > 0) {

            reviews_for_current_product.pop_back(); //Erases all reviews in temporary review vector

        }

        list_of_reviews->clear(); //Clears all items in lis of review matches for previously selected product

        selected_review_info->setText("");

    }

    vector<string> all_search_terms; //To store a vector of the individual search terms

    vector<Product*> product_results; //Delete later; Use good only

    stringstream ss;

    ss << user_input;

    string temp;

    while (ss >> temp) {

        temp = convToLower(temp); //Makes search term case-insensitive

        all_search_terms.push_back(temp); //Pushes it to the vector of search terms

    }

    if (and_ == true && or_ == false) { //AND search

        int type = 0;

        product_results = ds->search(all_search_terms, type); //Returns all products that match the search requirements

        for (unsigned int i = 0; i < product_results.size(); i++) {

            product_matches.push_back(product_results[i]); //Adds product matches into separate vector for this class

            product_matches_list->addItem(QString::fromStdString(product_matches[i]->getName())); //Adds product name as an item to the product list

        }

    }

    if (and_ == false && or_ == true) { //OR search

        int type = 1;

        product_results = ds->search(all_search_terms, type); //Returns all products that match the search requirements

        for (unsigned int i = 0; i < product_results.size(); i++) {

            product_matches.push_back(product_results[i]); //Adds product matches into separate vector for this class

            product_matches_list->addItem(QString::fromStdString(product_results[i]->getName())); //Adds product name as an item to the product lis

        }

    }

    search_entries->setText(""); //Clears search entry input box to allow for next search

}

void MainWindow::display_product_information(int productIndex) {

    if (productIndex == -1) {

        return; //Return if no products in product list or no products currently selected

    }

    QString productText; //Instantiates a Qstring to hold the string of product information

    productText += QString::fromStdString(product_matches[productIndex]->displayString()); //Gets the product information from the vector of product matches

    display_product_info->setText(productText); //Sets the Qlabel to hold the product information QString

}

void MainWindow::get_reviews_for_product() { //Make something for no reviews

    if (product_matches_list->currentRow() == -1) {

        return; //Return if no products in product list or no products currently selected 

    }

    if (reviews_for_current_product.size() > 0) {

        while (reviews_for_current_product.size() > 0) {

            reviews_for_current_product.pop_back(); //Erases all reviews in temporary review vector

        }

        list_of_reviews->clear(); //Clears all items in lis of review matches for previously selected product

        selected_review_info->setText(""); //Clears the QLabel holding the string for the current review

    }

    QListWidgetItem* current_product = product_matches_list->currentItem(); //Gets the currently selected product item from product list

    string product = current_product->text().toStdString(); //Gets the name of product

    map<string, vector<Review*> >::iterator it = ds->reviews_bank.find(product); //Sets iterator to vector of reviews in the database for current product

    if (it != ds->reviews_bank.end()) {

        for (unsigned int i = 0; i < it->second.size(); i++) {

            reviews_for_current_product.push_back(it->second[i]);

        }


        ReviewDate comp1; //Instantiates a functor that sorts reviews by their date data member

        mergeSort(reviews_for_current_product, comp1, 0, reviews_for_current_product.size()-1); //Calls mergesort along with the review functor on the temporary review vector

        for (unsigned int j = 0; j < reviews_for_current_product.size(); j++) {

            list_of_reviews->addItem(QString::fromStdString(reviews_for_current_product[j]->date)); //Adds the reviews to the review list according by date (sorted from most to least recent)

        }


    }

}


void MainWindow::display_selected_review(int reviewIndex) {

    if (list_of_reviews->currentRow() == -1) {

        return; //Return if no reviews in review list or no reviews currently selected 

    }

    QString reviewText; //Instantiates a Qstring to hold the review string

    reviewText = QString::fromStdString(reviews_for_current_product[reviewIndex]->displayString()); //Gets the review from the vector of reviews for current product

    selected_review_info->setText(reviewText); //Sets the Qlabel to hold the review QString

}

void MainWindow::add_new_review() {

    if (date_input->text().isEmpty() || rating_input->text().isEmpty() || review_text_input->toPlainText().isEmpty()) {

        return; // Return if the date, rating, or text input field is left blank

    }

    if (product_matches_list->currentRow() == -1) {

        return; //Return if no product currently selected 

    }

    string date = date_input->text().toStdString(); //Retrieves string from date input box

    date_input->setText(""); 

    string rating = rating_input->text().toStdString(); //Retrieves rating from rating input box

    rating_input->setText(""); 

    int score;

    stringstream ss;

    ss << rating;

    ss >> score; //Converts the rating into an integer 

    string review = review_text_input->toPlainText().toStdString(); //Retrieves review text from review text input box

    review_text_input->setPlainText(""); 

    QListWidgetItem* current_product = product_matches_list->currentItem(); //Gets the currently selected product item

    string product = current_product->text().toStdString(); //Gets the name of product from the product item

    Review* fresh = new Review(product, score, date, review); //Dynamically allocates/instantiates a new review object

    ds->addReview(fresh); //Adds new review to the database

    ds->all_reviews.push_back(fresh); //Pushes the new review into the database's vector of all reviews

    get_reviews_for_product(); //Calls the function to add the review to the list of mergesorted reviews 

}

void MainWindow::add_user_cart() {

    if (product_matches_list->count() < 1) {

        return; //Returns if no products in the product list 

    }

    QListWidgetItem* current_buyer = customers_list->currentItem(); //Gets the user currently selected

    string user = current_buyer->text().toStdString(); //Gets the name of the user

    int current_row = product_matches_list->currentRow(); //Gets the index of the currently selected product 

    ds->add_to_cart(user, current_row+1, product_matches); //Adds the product to the user's cart

}

void MainWindow::view_user_cart() {

    QListWidgetItem* current_buyer = customers_list->currentItem(); //Gets user currently selected

    string user = current_buyer->text().toStdString(); //Gets the name of the user

    MainWindow* cart = new MainWindow(*ds, user); //Instantiates a new QT window for user's cart

    cart->show(); //Shows QT window

}

void MainWindow::buy_user_cart() {

    if (list_of_cart_products->count() < 1) {

        return; //Return if there is nothing in the user's cart

    }

    map<string, User*>::iterator it1 = ds->customers.find(customer_name); //Finds user's object in database

    ds->buy_cart(customer_name); //Buys cart for user

    while (cart_products.size() > 0) {

        cart_products.pop_back(); //Deletes all products in user's temporary cart 

    }

    list_of_cart_products->clear(); //Clears the product list of all items

    map<User*, queue<Product*> >::iterator it2 = ds->users_cart.find(it1->second); //Gets user's cart from database

    queue<Product*> temp2 = it2->second; //Copy of user's cart

    while (temp2.size() > 0) { 

        list_of_cart_products->addItem(QString::fromStdString(temp2.front()->getName())); //Adds products left in user's cart to the list of user's cart products

        cart_products.push_back(temp2.front()); //Pushes products to user's temporary cart

        temp2.pop(); 

    }

}

void MainWindow::remove_from_user_cart() {

    if (list_of_cart_products->currentRow() == -1) {

        return; //Return if nothing selected from list of user's cart products

    }

    int item = list_of_cart_products->currentRow(); //Gets the productIndex of item user wants to remove

    cart_products.erase(cart_products.begin() + item); //Removes the product from the user's temporary cart

    map<string, User*>::iterator it1 = ds->customers.find(customer_name); 

    if (it1 != ds->customers.end() ) {

        User* client = it1->second;

        map<User*, queue<Product*> >::iterator it2 = ds->users_cart.find(client);

        if (it2 != ds->users_cart.end() ) {

            while (it2->second.size() > 0) {

                it2->second.pop(); //Deletes everything from user's cart

            }

            for (unsigned int i = 0; i < cart_products.size(); i++) {

                it2->second.push(cart_products[i]); //Adds everything back to user's cart except for the removed product 

            }

        }

    }

    delete list_of_cart_products->currentItem(); //Removes item from the list of user's cart products

}

void MainWindow::sort_by_average_rating() {

        vector<Product*> temp_product_matches; 

        temp_product_matches = product_matches; //Copies products that match the search requirements

        PointerProductRating comp1; //Instantiates a functor that sorts products by their average rating

        mergeSort(temp_product_matches, comp1, 0, temp_product_matches.size()-1); //Calls mergesort on the temporary product vector

        product_matches_list->clear(); //Clears all items from the list of product matches

        product_matches = temp_product_matches; //Assigns mergesorted vector to vector holding product matches

        for (unsigned int i = 0; i < product_matches.size(); i++) {

            product_matches_list->addItem(QString::fromStdString(product_matches[i]->getName())); //Adds (in order) product to the list of product matches

        }

}

void MainWindow::sort_alphabetically() {

        vector<Product*> temp_product_matches; 

        temp_product_matches = product_matches; //Copies products that match the search requirements

        PointerProductABC comp1; //Instantiates a functor that sorts products alphabetically by their name

        mergeSort(temp_product_matches, comp1, 0, temp_product_matches.size()-1); //Calls mergesort on the temporary product vector

        product_matches_list->clear(); //Clears all items from the list of product matches

        product_matches = temp_product_matches; //Assigns mergesorted vector to vector holding product matches

        for (unsigned int i = 0; i < product_matches.size(); i++) {

            product_matches_list->addItem(QString::fromStdString(product_matches[i]->getName())); //Adds (in order) product to the list of product matches

        }

}

void MainWindow::save_to_file() { //Do error checking for ofile

    if (output_file->text().isEmpty()) {

        return; //Returns if output file input box is empty

    }

    string file = output_file->text().toStdString(); 

    ofstream ofile (file.c_str()); //Instantiates an output file stream

    if( ofile.fail() ) { //Cannot open output file

        cout << "Couldn't open file" << endl;

        return;

    }

    ds->dump(ofile); //Dumps database into output file

    ofile.close(); //Closes output file

}
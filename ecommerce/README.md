COMPILE INSTRUCTIONS: To compile, type "qmake -project" in the command prompt, type "qmake" in the command prompt, type "make" in the command prompt, then type "./ecommerce <database input file>" to run/execute the program

A sample database file has been included. To run it, you would type "qmake -project" in the command prompt, type "qmake" in the command prompt, type "make" in the command prompt, then type "./ecommerce database_sample.txt" to run/execute the program. You are welcome to use a database file of your choosing provided you match the same format as in the sample database file. A seperate text file containing the (non-hashed) passwords of all the users is in a document titled "user_passwords.txt"

This program simulates TaoBao, an online marketplace/ecommerce platform. A database of users, products, and product reviews are read into the program. 



User information contains name, age, credit balance, and a hashed password (more on this later). 

Product information contains product name, price, and quantity available and miscellaneous information depending on the type of product. For example, a book would contain additional information such as author name and ISBN. As of now, the 3 main categories of products are books, movies, and clothing. 

Product review information contains the product name, rating, name of the user who reviewed the product, the date the product was reviewed and user comments regarding the product. 



Login

When the program first opens, the user is promopted for his or her login information. The username and hashed password can be found in the database. The program then checks to see if the username matches the given username in the database then uses a hash function to hash the password input the user gave and see if it matches the hashed password corresponding to the same user in the database. For simplicity sake, there is a separate text file titled "user_passwords.txt" containing the non-hashed password of each user in the database. 



Hash function (for password encryption)

The password string is translated into a long long where each integer is casted as an integer. Using the following formula:
p8 + 128 * p7 + 128^2 * p6 + ... + 128^7 * p1 where p1 is the leading character

The long long int is then converted to base-65521. To do this, the modulus operator is used on the long long to get the last significant digit. The number is then divided by 65521 to get the next digit. The process is repeated until 4 digits, w1, w2, w3, w4, are generatedd where w1 is the most significant. 

The password is then encrypted with the following formula: 

(45912 * w1 + 35511 * w2 + 65169 * w3 + 4625 * w4) % 65521



Verifying Passwords

To check whether a user enters the correct password, hash their password and make sure it matches what is recorded in the database. If it does not match display a dialog box with some kind of error message and once the user clicks OK, just wait for them to enter the username and password again.



Product Recommendation

Once the user information can be verified, the user is taken to the main window of the program. All GUI componenents instantaited in this program uses the Qt library. In the main window, the user is recommended a product he/she has not reviewed (and presumably haven't bought) based on his/her product similarity with those of other users as well as the product rating given by those users. For any given user, there may be 1st degree similarities which means that a User A has reviewed and rated the same product as has the account holder (user logged into the program). However, there may be 2nd degree similarities which means that a User B has reviewed and rated the same product as has User A who holds a 1st degree similarity with the account holder. There is less of a connection between User B and the account holder so understandably less of a weight is placed on this connection/similarity. By weighing each ith degree similarity accordingly as well as taking the product rating of the given user into account and summing this result for all users across all products, a product recommendation is determined. The shortest path to the ith degree recommendation is developed using, in part, Dijkstra's algorithm (shortest path from one User to the next to determine the ith degree similarity).



Search

The search interface allows the user to search for a product using keywords. All products that contain a keyword (no less than 2 characters) of the search with are found. The user has the option between choosing an "AND" search, meaning that all products found contain all of the keywords searched, and an "OR" search, meaning that all products found contain at least one of the keywords searched. This function is implemented by using a series of Set operations on Sets containing keywords corresponding to each particular product. The search results can be organized alphabetically or by average rating. This organization is provided for by a hard-coded (not included in library) Mergesort function. Given the list of product results, the user has the option to add the product to his/her cart and at any time view the cart and purchase or remove products accordingly. 



Reviews

By clicking on any product, a list of reviews corresponding to that product will show up. The reviews are sorted in order of date. In addition, the user has the option of adding a review for any given product. For the new review, the date must be in the yyyy-mm-dd format. mm must be between 1 and 12. dd must be between 1 and 31. The rating has to be between 1 to 5. Lastly, the comment or actual review section cannot be left blank. 



Updated Database

The user has the option to save an updated database to a file of his/her choosing by entering the file name above the "Save Database" button. The file will be found in the same directly as this document.



Exit Store

Quits the program










#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "taobao.h"
#include "product.h"
#include "review.h"

using namespace std;

 struct AlphaStrComp {
    bool operator()(const string& lhs, const string& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs < rhs; 
    }
  };

 struct LengthStrComp {
    bool operator()(const string& lhs, const string& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs.size() < rhs.size(); 
    }
  };

  struct PointerStrComp {
    bool operator()(const string* lhs, const string* rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return *lhs < *rhs; 
    }
  };

  struct PointerProductABC {

    bool operator()(Product* lhs, Product* rhs) {

        string left = lhs->getName();

        string right = rhs->getName();

        cout << left << " " << right << endl;

        return left < right;

    }

  };

  struct PointerProductRating {

    bool operator()(Product* lhs, Product* rhs) {

        double left = lhs->average_rating;

        double right = rhs->average_rating;

        return left > right;

    }

  };

  struct ReviewDate {

    bool operator()(Review* lhs, Review* rhs) {

        string left = lhs->date;

        string right = rhs->date;

        stringstream ss;

        int lhs_year;

        int lhs_month;

        int lhs_day;

        char lhs_temp;

        ss << left;

        ss >> lhs_year;

        ss >> lhs_temp;

        ss >> lhs_month;

        ss >> lhs_temp;

        ss >> lhs_day;

        stringstream ss2;

        int rhs_year;

        int rhs_month;

        int rhs_day;

        char rhs_temp;

        ss2 << right;

        ss2 >> rhs_year;

        ss2 >> rhs_temp;

        ss2 >> rhs_month;

        ss2 >> rhs_temp;

        ss2 >> rhs_day;

        if (lhs_year == rhs_year) {

            if (lhs_month == rhs_month) {

                return lhs_day > rhs_day;

            }

            else {

                return lhs_month > rhs_month;

            }

        }

        else {

            return lhs_year > rhs_year;

        }

    }

  };

  

template <class T, class Comparator>
void merge(vector<T>&, Comparator, int, int, int);

template <class T, class Comparator>
void mergeSort (vector<T>& myArray, Comparator comp, int low, int high) {

    int mid;

    if (low < high) { //More than just one element in the given array

        mid=(low+high)/2; 

        mergeSort(myArray, comp, low, mid);

        mergeSort(myArray, comp, mid+1, high);

        merge(myArray, comp, low, high, mid);
    }

    return;
}

template <class T, class Comparator>
void merge(vector<T>& myArray, Comparator comp, int low, int high, int mid) {

    int i, j, k;

    vector<T> myTempArray(high+1);

    /*
    i is the indice indicating a given element in the right array
    j is the indice indicating a given element in the left array
    k is the indice indicating a given element in the new array
    myTempArray is the new array statically allocated to store copies of the current elements being processed
    */

    i = low; //Beginning of right array
    k = low; //For however many elements in both right and left array
    j = mid + 1; //Beginning of left array
    while (i <= mid && j <= high) { //For the length of the right array and the left array
        if (comp(myArray[i], myArray[j])) { //If specified element in right array is less than specified element in left array
            myTempArray[k] = myArray[i]; //Puts specified element in right array in new array
            k++;
            i++; //Increments i to point at next element in the right array
        } else { //Specified element in left array is less than specified element in right array
            myTempArray[k] = myArray[j]; //Puts specified element in left array in new array
            k++;
            j++; //Increments j to point at next element in the left array
        }
    }
    while (i <= mid) { //If right array still has elements not in new array
        myTempArray[k] = myArray[i];
        k++;
        i++;
    }
    while (j <= high) { //If left array still has elements not in new array
        myTempArray[k] = myArray[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++) { //Uses k as size because thats how many elements the new array contains

        myArray[i] = myTempArray[i];
    }
}

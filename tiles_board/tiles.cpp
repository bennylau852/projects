#include "rbbst.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>
#include <iomanip>

using namespace std;

struct Rectangle {
    int ID;
    int length;
    int height;
};

RedBlackTree<int, Rectangle> rbt_rects;

RedBlackTree<int, pair<int, int> > rbt_coords;

int** canvas;

//void print_board(int height, int length);

void print_board(int height, int length, ostream& out);

bool change_board(int row, int col, int length, int height, int operation, int ID);

bool search(int floor_height, int floor_length, int ID, Rectangle rect);

bool change_board(int coord_row, int coord_col, int length, int height, int board_height, int board_length, int operation, int ID) {

    if (coord_row + height > board_height || coord_col + length > board_length) {

        return false;

    }

    if (operation == 0) {

        bool clear;

        for (int row = coord_row; row < coord_row + height; row++) {

            for (int col = coord_col; col < coord_col + length; col++) {

                if (canvas[row][col] != 0) {

                    clear = false;

                    return clear;

                }

            }

        }

        clear = true;

        return clear;

    }

    if (operation == -1) {

        for (int row = coord_row; row < coord_row + height; row++) {

            for (int col = coord_col; col < coord_col + length; col++) {

                canvas[row][col] = 0;


            }

        }

    }

    if (operation == 1) {

        for (int row = coord_row; row < coord_row + height; row++) {

            for (int col = coord_col; col < coord_col + length; col++) {

                canvas[row][col] = ID;

            }
        }

    }

    return true;

}

int main(int argc, char* argv[]) {

    if (argc < 3) {

        cout << "Missing files" << endl;
    }

    ifstream myfile(argv[1]);

    if (myfile.fail()) {

        cout << "Failed to read input file" << endl;

        return -1;

    }

    string myline_first;

    getline(myfile, myline_first);

    stringstream ss1(myline_first);

    int surface_length;

    ss1 >> surface_length;

    int surface_height;

    ss1 >> surface_height;

    int number_of_tiles;

    ss1 >> number_of_tiles;

    string myline_second;

    while( getline(myfile, myline_second) ) {

        stringstream ss2(myline_second);

        int _ID;

        ss2 >> _ID;

        int _length;

        ss2 >> _length;

        int _height;

        ss2 >> _height;

        Rectangle temp;

        temp.ID = _ID;

        temp.length = _length;

        temp.height = _height;

        pair<int, Rectangle> item;

        item = make_pair(_ID, temp);

        rbt_rects.insert(item);

    }

    canvas = new int*[surface_height];

    for(int i=0; i < surface_height; i++) {

        canvas[i] = new int[surface_length];

        for(int j = 0; j < surface_length; j++) {

            canvas[i][j] = 0;

        }

    }

    RedBlackTree<int, Rectangle>::iterator it1 = rbt_rects.begin();

    int ID = (*it1).first;

    Rectangle first_rect = (*it1).second;

    ofstream ofile(argv[2]);

    if (ofile.fail()) {

        cout << "Failed to read output file" << endl;

        return -1;

    }


    if ( !search(surface_height, surface_length, ID, first_rect) ) {

        ofile << "No solution!" << endl;

    }

    else {

        for (RedBlackTree<int, pair<int, int> >::iterator it2 = rbt_coords.begin(); it2 != rbt_coords.end(); ++it2) {

            RedBlackTree<int, Rectangle>::iterator it3 = rbt_rects.find((*it2).first);

            if (it3 == NULL) {

                ofile << "No solution" << endl;

                break;

            }

            else {

                ofile << (*it2).first << " " << (*it2).second.second << " " <<  (*it2).second.first << " " << (*it3).second.length << " " << (*it3).second.height << endl;

            }

        }

        print_board(surface_height, surface_length, ofile);

    }

    myfile.close();

    ofile.close();

    for(int i = 0; i < surface_height; i++) {

        delete [] canvas[i];

    }

    delete canvas;

    return 0;
}

void printBanner(int length) {

    if(length == 0) return;
    cout << '+';
    for(int i=0; i < length; i++) {
        cout << "--+";
    }
    cout << endl;
}

void printBanner(int length, ostream& out) {

    if(length == 0) return;
    out << '+';
    for(int i=0; i < length; i++) {
        out << "--+";
    }
    out << endl;
}

/*

void print_board(int height, int length) {

    cout << "Solved" << endl;

    for (int i = height-1; i > -1; i--) { //Double for loops to print row, col

        printBanner(length);

        for (int j = 0; j < length; j++) {

            cout << "|";

            if (canvas[i][j] < 10) {

                cout << " " << canvas[i][j];

            }

            else {

                cout << canvas[i][j];

            }

        }

        cout << "|" << endl;

    }

    printBanner(length);

    cout << endl;

}

*/

void print_board(int height, int length, ostream& out) {

    out << "Solved" << endl;

    for (int i = height-1; i > -1; i--) { //Double for loops to print row, col

        printBanner(length, out);

        for (int j = 0; j < length; j++) {

            out << "|";

            if (canvas[i][j] < 10) {

                out << " " << canvas[i][j];

            }

            else {

                out << canvas[i][j];

            }

        }

        out << "|" << endl;

    }

    printBanner(length, out);

    out << endl;

}

bool search(int floor_height, int floor_length, int ID, Rectangle rect) {

    RedBlackTree<int, Rectangle>::iterator it1 = rbt_rects.find(ID); 

    if (it1 == rbt_rects.end()) { //No more tiles to insert

        //print_board(floor_height, floor_length);

        return true;

    }

    else {

        int length = rect.length;

        int height = rect.height;

        for(int row = 0; row < floor_height; row++) {

            for (int col = 0; col < floor_length; col++) {

                if (canvas[row][col] == 0) {

                    if (change_board(row, col, length, height, floor_height, floor_length, 0, ID)) { //Make sure is valid

                        bool success = change_board(row, col, length, height, floor_height, floor_length, 1, ID); //Fills board with ID of tile

                        pair<int, int> coord; //Coordinate Int pair

                        coord = make_pair(row, col);

                        pair<int, pair<int, int> > full_coords;

                        full_coords = make_pair(ID, coord);

                        RedBlackTree<int, pair<int, int> >::iterator it4 = rbt_coords.find(ID);

                        if (it4 != rbt_coords.end()) {

                            ((*it4).second).first = row;

                            ((*it4).second).second = col;

                        }

                        else {

                            rbt_coords.insert(full_coords);

                        }

                        RedBlackTree<int, Rectangle>::iterator it2 = rbt_rects.find(ID);

                        ++it2; //Go on to next rectangle

                        if (it2 == rbt_rects.end()) {

                            //print_board(floor_height, floor_length);

                            return true;

                        }

                        int new_ID = (*it2).first;

                        Rectangle new_rect = (*it2).second;

                        bool status = search(floor_height, floor_length, new_ID, new_rect);

                        if (status) {

                            return true;

                        }

                        /*

                        Assume fails if it reaches here

                        */

                        bool fail = change_board(row, col, length, height, floor_height, floor_length, -1, ID);

                        RedBlackTree<int, pair<int, int> >::iterator it3 = rbt_coords.find(ID);

                        ((*it3).second).first = -1;

                        ((*it3).second).second = -1;

                    }

                    else if (change_board(row, col, height, length, floor_height, floor_length, 0, ID)) {

                        bool success = change_board(row, col, height, length, floor_height, floor_length, 1, ID);

                        pair<int, int> coord;

                        coord = make_pair(row, col);

                        pair<int, pair<int, int> > full_coords;

                        full_coords = make_pair(ID, coord);

                        RedBlackTree<int, pair<int, int> >::iterator it4 = rbt_coords.find(ID);

                        if (it4 != rbt_coords.end()) {

                            ((*it4).second).first = row;

                            ((*it4).second).second = col;

                        }

                        else {

                            rbt_coords.insert(full_coords);

                        }

                        RedBlackTree<int, Rectangle>::iterator it2 = rbt_rects.find(ID);

                        int temp_length = ((*it2).second).length;

                        ((*it2).second).length = height;

                        ((*it2).second).height = temp_length;

                        ++it2; //Go on to next rectangle

                        if (it2 == rbt_rects.end()) {

                            //print_board(floor_height, floor_length);

                            return true;

                        }

                        int new_ID = (*it2).first;

                        Rectangle new_rect = (*it2).second;

                        bool status = search(floor_height, floor_length, new_ID, new_rect);

                        if (status) {

                            return true;

                        }

                        bool fail = change_board(row, col, length, height, floor_height, floor_length, -1, ID);

                        RedBlackTree<int, pair<int, int> >::iterator it3 = rbt_coords.find(ID);

                        ((*it3).second).first = -1;

                        ((*it3).second).second = -1;

                    }

                }

            }

        }

        return false;

    }

}
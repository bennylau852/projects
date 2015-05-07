#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType> {
public:
    RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
        : Node<KeyType, ValueType> (k, v, p) {
        color = red;
    }

    virtual ~RedBlackNode () {}

    Color getColor () const {
        return color;
    }

    void setColor (Color c) {
        color = c;
    }

    virtual RedBlackNode<KeyType, ValueType> *getParent () const {
        return (RedBlackNode<KeyType,ValueType>*) this->_parent;
    }

    virtual RedBlackNode<KeyType, ValueType> *getLeft () const {
        return (RedBlackNode<KeyType,ValueType>*) this->_left;
    }

    virtual RedBlackNode<KeyType, ValueType> *getRight () const {
        return (RedBlackNode<KeyType,ValueType>*) this->_right;
    }

protected:
    Color color;
};

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType> {

public:

    void insert (const std::pair<const KeyType, ValueType>& new_item) {

        RedBlackNode<KeyType, ValueType>* new_node = new RedBlackNode<KeyType, ValueType>(new_item.first, new_item.second, NULL);

        if (this->root == NULL) { 

            this->root = new_node;

        }

        else if (this->root != NULL) {

            RedBlackNode<KeyType,ValueType>* root_temp = (RedBlackNode<KeyType,ValueType>*) this->root;

            while (1) {

                RedBlackNode<KeyType, ValueType>* temp;

                if (this->internalFind(new_item.first) != NULL) { //Key exists in RBT

                    temp = (RedBlackNode<KeyType,ValueType>*) this->internalFind(new_item.first); 

                    temp->setValue(new_item.second); //Overwrite old value

                }

                else if (new_item.first <  root_temp->getKey()) { //Key or new node less than current

                    if (root_temp->getLeft() == NULL) {

                        root_temp->_left = new_node;

                        break;

                    }

                    else {

                        root_temp = root_temp->getLeft(); //Compared node is now old compared's left child

                    }

                }

                else { //Key of new node greater than current

                    if (root_temp->getRight() == NULL) { //No right child

                        root_temp->_right = new_node; //Make it the right child

                        break;

                    }

                    else {

                        root_temp = root_temp->getRight(); //Compared node is now old compared's right child

                    }
                }
            }

            new_node->_parent = root_temp; //Parent of inserted node is compared node

        }

        fixtree_step1(new_node); //Inserts depending on current condition of the rbt (goes through every case)

    }

private:

    RedBlackNode<KeyType, ValueType>* findMyGrandparents(RedBlackNode<KeyType, ValueType> *n) {

        if (n->getParent()->getParent() != NULL) {

            return n->getParent()->getParent();

        }

        return NULL;

    }

    RedBlackNode<KeyType, ValueType>* findMyUncle(RedBlackNode<KeyType, ValueType> *n) {

        if (findMyGrandparents(n) != NULL) {

            if (findMyGrandparents(n)->getLeft() != n->getParent() ) {

                return findMyGrandparents(n)->getLeft();

            }

            else {

                return findMyGrandparents(n)->getRight();

            }

        }

        return NULL;

    }

    /*
     * Inserting Case 1
     */
    void fixtree_step1(RedBlackNode<KeyType, ValueType> *n) {

        if (n->getParent() == NULL) { //Only the root node

            n->setColor(black); //RECOLOR: Root must be black

        }

        else {

            fixtree_step2(n); //Not the root node
        }
    }

    /*
     * Inserting Case 2
     */
    void fixtree_step2(RedBlackNode<KeyType, ValueType> *n) {

        if (n->getParent()->getColor() == black) //If the color of its parent is black

            return; //Correct because itd be a 3 or 4 node in 2-3-4 tree

        else {

            fixtree_step3(n); //Color of its parent is red (2 consecutive red nodes)

        }

    }

    /*
     * Inserting Case 3
     */
    void fixtree_step3(RedBlackNode<KeyType, ValueType> *n) {

        if (findMyUncle(n) != NULL && findMyUncle(n)->getColor() == red) { //If uncle is red

            n->getParent()->setColor(black); //RECOLOR: Make parent black

            if (findMyUncle(n) != NULL) {

            findMyUncle(n)->setColor(black); //RECOLOR: Make uncle black

            }

            findMyGrandparents(n)->setColor(red); //RECOLOR: Make grandparent red

            fixtree_step1(findMyGrandparents(n)); //Run through cases again (in case rbt properties not maintained)

        }

        else {

            fixtree_step4(n); //Uncle is black

        }
    }

    /*
     * Inserting Case 4
     */

    void fixtree_step4(RedBlackNode<KeyType, ValueType> *n) {

        if (n == n->getParent()->getRight() && n->getParent() == findMyGrandparents(n)->getLeft()) { //Current is a right child and parent is a left child

            rotate_left(n->getParent()); //ROTATE: Rotate left on parent

            n = n->getLeft(); //Left child is now current

        }

        else if (n == n->getParent()->getLeft() && n->getParent() == findMyGrandparents(n)->getRight()) { //Current is a left child and parent is a right child

            rotate_right(n->getParent()); //ROTATE: Rotate right on parent

            n = n->getRight(); //Right child is now current
        }

        fixtree_step5(n); //Continue to case 5 regardless

    }

     /*
     * Inserting Case 5
     */

    void fixtree_step5(RedBlackNode<KeyType, ValueType> *n) {

        n->getParent()->setColor(black); //RECOLOR: Parent is now black

        findMyGrandparents(n)->setColor(red); //RECOLOR: Grandparent is red

        if (n == n->getParent()->getLeft() && n->getParent() == findMyGrandparents(n)->getLeft()) { //Current is a left child and parent is a left child

            rotate_right(findMyGrandparents(n)); //ROTATE: Rotate right on grandparent

        }

        else {

            if (n == n->getParent()->getRight() && n->getParent() == findMyGrandparents(n)->getRight()) { //Current is a right child and parent is a right child

                rotate_left(findMyGrandparents(n)); //ROTATE: Rotate left on grandparent

            }

        }

    }

    void rotate_right(RedBlackNode<KeyType, ValueType>* n) {

        RedBlackNode<KeyType, ValueType>* left = n->getLeft(); //Chooses the left child of the old parent to be the new parent

        rotate_helper(n, left); //Replaces the old parent with the new parent

        n->_left = left->getRight(); //Moves right child of new parent to be left child of old parent

        if (left->getRight() != NULL) { //If new parent has a right child

            left->getRight()->_parent = n; //Set its parent to be the old parent

        }

        left->_right = n; //Sets the old parent to be the right child of the new parent

        n->_parent = left; //Sets the parent of the old parent to be the new parent

    }

    void rotate_left(RedBlackNode<KeyType, ValueType>* n) {

        RedBlackNode<KeyType, ValueType>* right = n->getRight(); //Chooses the right child of the old parent to be the new parent

        rotate_helper(n, right); //Replaces the old parent with the new parent

        n->_right = right->getLeft(); //Moves left child of new parent to be right child of old parent

        if (right->getLeft() != NULL) { //If new parent has a left child

            right->getLeft()->_parent = n; //Set its parent to be the old parent
        }

        right->_left = n; //Sets the old parent to be the left child of the new parent

        n->_parent = right; //Sets the parent of the old parent to be the new parent

    }

    void rotate_helper(RedBlackNode<KeyType, ValueType>* old_parent, RedBlackNode<KeyType, ValueType>* new_parent) {

        if (old_parent->getParent() == NULL) { //Old parent doesn't have a parent (root node only)

            this->root = new_parent; //Root of rbt is now new parent
        }

        else {

            if (old_parent == old_parent->getParent()->getLeft()) { //Old parent is its parent's left child

                old_parent->getParent()->_left = new_parent; //Old parent's parent now has new parent as its left child

            }

            else {

                old_parent->getParent()->_right = new_parent; //Old parent's parent now has new parent as its right child
            }

        }

        if (new_parent != NULL) {

            new_parent->_parent = old_parent->getParent(); //Parent of new parent is now old parent's parent

        }
    }

};




#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <string>

template <class KeyType, class ValueType>
class Node {
public:
    Node (const KeyType & k, const ValueType & v, Node<KeyType, ValueType> *p)
        : _item(k, v) //New nodes created are leaves

    {
        _parent = p;
        _left = _right = NULL;

    }

    virtual ~Node() {
    }

    std::pair<const KeyType, ValueType> const & getItem () const {
        return _item;
    }

    std::pair<const KeyType, ValueType> & getItem () {
        return _item;
    }

    const KeyType & getKey () const {
        return _item.first;
    }

    const ValueType & getValue () const {
        return _item.second;
    }

    virtual Node<KeyType, ValueType> *getParent () const {
        return _parent;
    }

    virtual Node<KeyType, ValueType> *getLeft () const {
        return _left;
    }

    virtual Node<KeyType, ValueType> *getRight () const {
        return _right;
    }


    void setParent (Node<KeyType, ValueType> *p) {
        _parent = p;
    }

    void setLeft (Node<KeyType, ValueType> *l) {
        _left = l;
    }

    void setRight (Node<KeyType, ValueType> *r) {
        _right = r;
    }

    void setValue (const ValueType &v) {
        _item.second = v;
    }

//protected:
    std::pair<const KeyType, ValueType> _item;
    Node <KeyType, ValueType> *_left, *_right, *_parent;

};

template <class KeyType, class ValueType>
class BinarySearchTree {

protected:
    Node<KeyType, ValueType> *root;

public:
    /**
     * Constructor
     */
    BinarySearchTree () {
        root = NULL;
    }

    /**
     * Destructor
     */
    ~BinarySearchTree () {
        deleteAll (root);
    }

    void print () const {
        printRoot (root);
        std::cout << "\n";
    }

    Node<KeyType, ValueType>* igotchu() {

        return root;

    }

    class iterator {

    public:

        iterator(Node<KeyType,ValueType>* ptr) : curr(ptr) { //Initialize Node pointer with argument


        }

        std::pair<const KeyType,ValueType>& operator*() {

            return curr->getItem();

        }

        std::pair<const KeyType,ValueType>* operator->() {

            return &(curr->getItem());

        }

        bool operator==(const iterator& rhs) const {

            return curr == rhs.curr;

        }

        bool operator!=(const iterator& rhs) const {

            return curr != rhs.curr;

        }

        iterator& operator++() {

            if (curr->getRight() == NULL) {

              Node<KeyType, ValueType>* temp;

              if (curr->getParent() != NULL) {

                temp = curr->getParent();

                  while (temp->getParent() != NULL) {

                    temp = temp->getParent(); //Becomes copy of root node

                  }

              }

              else {

                temp = curr;

              }

              while (temp->getRight()) {

                temp = temp->getRight();

              }

              if (temp == curr) {

                curr = NULL;

                return *this;

              }

            }

            if (curr->getRight() != NULL) {

                curr = curr->getRight();

                while (curr->getLeft() != NULL) {

                    curr = curr->getLeft();

                }

            }

            else {

                while (curr->getParent() != NULL) {

                    if (curr->getParent()->getKey() > curr->getKey()) {

                        curr = curr->getParent();

                        break;

                    }

                    curr = curr->getParent();

                }

                return *this;

            }

            return *this;

        }

        const ValueType & return_value() {

            return curr->getKey();

        }

    protected:

        Node<KeyType, ValueType>* curr;


    };

    typename BinarySearchTree<KeyType, ValueType>::iterator begin() {

        Node<KeyType, ValueType>* root = igotchu();

        if (root == NULL) {

            BinarySearchTree<KeyType, ValueType>::iterator it_null(NULL);

            return it_null;

        }

        Node<KeyType, ValueType>* temp;

        temp = root;

        while (temp->getLeft()) {

            temp = temp->getLeft();

        }

        BinarySearchTree<KeyType, ValueType>::iterator it(temp);

        return it;

    }

    typename BinarySearchTree<KeyType, ValueType>::iterator end() {

        BinarySearchTree<KeyType, ValueType>::iterator it(NULL);

        return it;

    }

    iterator find (const KeyType & k) const {
        Node<KeyType, ValueType> *curr = internalFind(k);
        iterator it(curr);
        return it;
    }

protected:

    Node<KeyType, ValueType>* internalFind(const KeyType& k) const {
        Node<KeyType, ValueType> *curr = root;
        while (curr) {
            if (curr->getKey() == k) {
                return curr;
            } else if (k < curr->getKey()) {
                curr = curr->getLeft();
            } else {
                curr = curr->getRight();
            }
        }
        return NULL;
    }

    void printRoot (Node<KeyType, ValueType> *r) const {
        if (r != NULL) {
            std::cout << "[";
            printRoot (r->getLeft());
            std::cout << " (" << r->getKey() << ", " << r->getValue() << ") ";
            printRoot (r->getRight());
            std::cout << "]";
        }
    }

    void deleteAll (Node<KeyType, ValueType> *r) {
        if (r != NULL) {
            deleteAll (r->getLeft());
            deleteAll (r->getRight());
            delete r;
        }
    }

};


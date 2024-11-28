#include <iostream>

enum Color {
    RED,
    BLACK
};

struct RBNode {
    int data;
    RBNode *left;
    RBNode *right;
    RBNode *parent;
    Color color;

    RBNode(int d, RBNode *l = nullptr, RBNode *r = nullptr, RBNode *p = nullptr, Color c = RED)
        : data(d), left(l), right(r), parent(p), color(c) {
    }

    void print() {
        std::cout << data << " ";
        std::cout << (color == RED ? "RED" : "BLACK") << std::endl;
    }

    void ReColor() {
        color = (color == RED) ? BLACK : RED;
    }
};

class RBTree {
    RBNode *root = nullptr;

public:
    RBTree(RBNode *r = nullptr) : root(r) {
    }

    RBNode *search(int elem) {
        RBNode *cur = root;
        while (cur != nullptr) {
            if (cur->data == elem) {
                return cur;
            }
            cur = (cur->data > elem) ? cur->left : cur->right;
        }
        return nullptr;
    }

    void bstInsert(int elem) {
        RBNode *parent = nullptr;
        RBNode *cur = root;

        while (cur != nullptr) {
            parent = cur;
            cur = (elem < cur->data) ? cur->left : cur->right;
        }

        RBNode *newNode = new RBNode(elem, nullptr, nullptr, parent);

        if (parent == nullptr) {
            root = newNode;
        } else if (elem < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    void insert(int elem) {
        RBNode *x = new RBNode(elem);

        if (root == nullptr) {
            x->color = BLACK;
            root = x;
            return;
        }

        bstInsert(elem);
        insertFixup(x);
    }

    void insertFixup(RBNode *node) {
        while (node->parent != nullptr && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                RBNode *uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            } else {
                RBNode *uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void leftRotate(RBNode *node) {
        RBNode *y = node->right;
        node->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = node;
        }
        y->parent = node->parent;
        if (node->parent == nullptr) {
            root = y;
        } else if (node == node->parent->left) {
            node->parent->left = y;
        } else {
            node->parent->right = y;
        }
        y->left = node;
        node->parent = y;
    }

    void rightRotate(RBNode *node) {
        RBNode *y = node->left;
        node->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = node;
        }
        y->parent = node->parent;
        if (node->parent == nullptr) {
            root = y;
        } else if (node == node->parent->right) {
            node->parent->right = y;
        } else {
            node->parent->left = y;
        }
        y->right = node;
        node->parent = y;
    }


    void printTree() {
        printT(root);
        std::cout << std::endl;
    }

    void printT(RBNode *node) {
        if (node == nullptr) {
            return;
        }
        printT(node->left);
        node->print();
        printT(node->right);
    }
};


int main() {
    RBTree tree;

    tree.insert(40);
    std::cout << "After insert(40):\n";
    tree.printTree();

    tree.insert(20);
    std::cout << "After insert(20):\n";
    tree.printTree();

    tree.insert(10);
    std::cout << "After insert(10):\n";
    tree.printTree();

    tree.insert(30);
    std::cout << "After insert(30):\n";
    tree.printTree();

    tree.insert(50);
    std::cout << "After insert(50):\n";
    tree.printTree();

    tree.insert(60);
    std::cout << "After insert(60):\n";
    tree.printTree();

    tree.insert(90);
    std::cout << "After insert(90):\n";
    tree.printTree();

    tree.insert(70);
    std::cout << "After insert(70):\n";
    tree.printTree();

    tree.insert(55);
    std::cout << "After insert(55):\n";
    tree.printTree();

    tree.insert(15);
    std::cout << "After insert(15):\n";
    tree.printTree();

    tree.insert(35);
    std::cout << "After insert(35):\n";
    tree.printTree();

    tree.insert(45);
    std::cout << "After insert(45):\n";
    tree.printTree();

    return 0;
}

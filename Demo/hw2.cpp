#include <iostream>

template<class T>
class Node {
public:
    T data;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;

    Node(T d, Node<T> *l = nullptr, Node<T> *r = nullptr, Node<T> *p = nullptr) : data(d), left(l), right(r),
        parent(p) {
    }

    T operator*() {
        return data;
    }

    bool operator<(const Node<T> &other) {
        return data < other.data;
    }
};

template<class U>
class AbstractBinaryTree {
public:
    virtual Node<U> *search(U val) = 0;

    virtual void insert(Node<U> *val) = 0;

    virtual void remove(Node<U> *val) = 0;
};

template<class T>
class BinarySearchTree : public AbstractBinaryTree<T> {
private:
    Node<T> *head = nullptr;

public:
    Node<T> *search(T val) override {
        Node<T> *tmp = head;

        while (tmp != nullptr) {
            if (tmp->data == val) {
                return tmp;
            } else if (val < tmp->data) {
                tmp = tmp->left;
            } else {
                tmp = tmp->right;
            }
        }
        return nullptr;
    }

    void insert(Node<T> *newNode) override {
        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node<T> *tmp = head;
        Node<T> *parent = nullptr;

        while (tmp != nullptr) {
            parent = tmp;

            if (newNode->data > tmp->data) {
                tmp = tmp->right;
            } else if (newNode->data < tmp->data) {
                tmp = tmp->left;
            } else {
                return;
            }
        }

        if (parent->data > newNode->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        newNode->parent = parent;
    }

    void insert(T newVal) {
        Node<T> *newNode = new Node<T>(newVal);
        insert(newNode);
    }

    void remove(Node<T> *needToDelete) override {
        if (needToDelete == nullptr) {
            return;
        }

        // case 1 -  տերև է
        if (needToDelete->left == nullptr && needToDelete->right == nullptr) {
            if (needToDelete->parent != nullptr) {
                if (needToDelete->parent->left == needToDelete) {
                    needToDelete->parent->left = nullptr;
                } else {
                    needToDelete->parent->right = nullptr;
                }
            } else {
                head = nullptr;
            }
            delete needToDelete;
        }
        // case 2 - ունի մեկ որդի
        else if (needToDelete->left == nullptr || needToDelete->right == nullptr) {
            Node<T> *child = (needToDelete->left != nullptr) ? needToDelete->left : needToDelete->right;

            if (needToDelete->parent != nullptr) {
                if (needToDelete->parent->left == needToDelete) {
                    needToDelete->parent->left = child;
                } else {
                    needToDelete->parent->right = child;
                }
            } else {
                head = child;
            }

            if (child != nullptr) {
                child->parent = needToDelete->parent;
            }
            delete needToDelete;
        }
        // case 3 - ունի երկու որդի
        else {
            Node<T> *s_Node = needToDelete->right;
            Node<T> *s_Parent = needToDelete;

            while (s_Node->left != nullptr) {
                s_Parent = s_Node;
                s_Node = s_Node->left;
            }

            needToDelete->data = s_Node->data;

            if (s_Parent->left == s_Node) {
                s_Parent->left = s_Node->right;
            } else {
                s_Parent->right = s_Node->right;
            }

            if (s_Node->right != nullptr) {
                s_Node->right->parent = s_Parent;
            }

            delete s_Node;
        }
    }

    void remove(const T &elem) {
        if (Node<T> *removedNode = search(elem)) {
            remove(removedNode);
        } else {
            return;
        }
    }

    Node<T> *successor(Node<T> *node) {
        if (node->right != nullptr) {
            return treeMin(node->right);
        }
        Node<T> *parent = node->parent;
        while (parent != nullptr && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    T min() const {
        if (head == nullptr) {
            std::cout << "Empty Tree" << std::endl;
        }
        return treeMin(head)->data;
    }

    Node<T> *treeMin(Node<T> *node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void inorderTreeWalk(Node<T> *x) const {
        if (x != nullptr) {
            inorderTreeWalk(x->left);
            std::cout << x->data << " ";
            inorderTreeWalk(x->right);
        }
    }

    void printTree() const {
        inorderTreeWalk(head);
        std::cout << std::endl;
    }

    ~BinarySearchTree() {
        deleteTree(head);
    }

    void deleteTree(Node<T> *root) {
        if (root != nullptr) {
            deleteTree(root->left);
            deleteTree(root->right);
            delete root;
        }
    }
};

int main() {
    BinarySearchTree<int> bst;

    bst.insert(40);
    bst.insert(20);
    bst.insert(10);
    bst.insert(30);
    bst.insert(50);
    bst.insert(60);
    bst.insert(40);
    bst.insert(70);
    bst.insert(55);

    std::cout << "Tree after insertions: ";
    bst.printTree();

    bst.remove(bst.search(70));
    std::cout << "\nTree after removing 70: ";
    bst.printTree();

    bst.remove(bst.search(60));
    std::cout << "\nTree after removing 60: ";
    bst.printTree();

    bst.remove(bst.search(40));
    std::cout << "\nTree after removing 40: ";
    bst.printTree();

    return 0;
}

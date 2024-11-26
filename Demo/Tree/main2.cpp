#include <iostream>

class TreeNode {
public:
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    char data;

    TreeNode(char d = 0, TreeNode *p = nullptr, TreeNode *l = nullptr, TreeNode *r = nullptr)
        : data(d), parent(p), left(l), right(r) {
    }
};

void task2(TreeNode *root) {
    if (!root) return;

    TreeNode *cur = root;
    TreeNode *tmp = nullptr;

    while (cur->left) {
        cur = cur->left;
    }

    while (cur) {
        if (!cur->right || cur->right == tmp) {
            std::cout << cur->data << " ";
            tmp = cur;
            cur = cur->parent;
        } else {
            cur = cur->right;
            while (cur->left) {
                cur = cur->left;
            }
        }
    }
}


int main() {
    TreeNode *root = new TreeNode('a');
    root->left = new TreeNode('b', root);
    root->right = new TreeNode('c', root);
    root->left->left = new TreeNode('d', root->left);
    root->right->left = new TreeNode('e', root->right);
    root->right->right = new TreeNode('f', root->right);
    root->right->left->right = new TreeNode('g', root->right->left);
    root->right->right->left = new TreeNode('h', root->right->right);
    root->right->right->right = new TreeNode('i', root->right->right);

    std::cout << "Task 2: ";
    task2(root);
    std::cout << std::endl;


    return 0;
}

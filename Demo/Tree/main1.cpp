#include <iostream>
#include<stack>
class TreeNode {
public:
    TreeNode* left;
    TreeNode* right;
    char data;

    TreeNode(int d = 0, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : left(l), right(r), data(d) {}
};

void task1(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    std::stack<TreeNode*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        TreeNode* node = s1.top();
        s1.pop();
        s2.push(node);

        if (node->left != nullptr) {
            s1.push(node->left);
        }
        if (node->right != nullptr) {
            s1.push(node->right);
        }
    }

    while (!s2.empty()) {
        std::cout << s2.top()->data << " ";
        s2.pop();
    }
}

int main() {
    TreeNode* root = new TreeNode('a');
    root->left = new TreeNode('b');
    root->right = new TreeNode('c');
    root->left->left = new TreeNode('d');
    root->right->left = new TreeNode('e');
    root->right->right = new TreeNode('f');
    root->right->left->right = new TreeNode('g');
    root->right->right->left = new TreeNode('h');
    root->right->right->right = new TreeNode('i');

    std::cout << "Task 1: ";
    task1(root);
    std::cout << std::endl;


    return 0;
}
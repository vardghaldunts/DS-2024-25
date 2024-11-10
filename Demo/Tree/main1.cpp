#include <iostream>
#include<stack>
class TreeNode {
public:
    TreeNode* left;
    TreeNode* right;
    int data;

    TreeNode(int d = 0, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : left(l), right(r), data(d) {}
};

void task1(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    std::stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();

        std::cout << node->data << " ";
        if (node->right != nullptr) {

            s.push(node->right);
        }
        if (node->left != nullptr) {
            s.push(node->left);
        }


    }
}


int main() {

    TreeNode* root = new TreeNode(1);//a
    root->left = new TreeNode(2);//b
    root->right = new TreeNode(3);//c
    root->left->left = new TreeNode(4);//d
    root->right->left = new TreeNode(5);//e
    root->right->right = new TreeNode(6);//f
    root->right->left->right = new TreeNode(7);//g
    root->right->right->left = new TreeNode(8);//h
    root->right->right->right= new TreeNode(9);//i

    std::cout << "Task 1: ";
    task1(root);
    std::cout << std::endl;


    return 0;
}
#include <iostream>

class TreeNode {
public:
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    int data;

    TreeNode(int d= 0 , TreeNode* p=nullptr  ,TreeNode* l=nullptr,TreeNode* r =nullptr)
        : data(d), parent(p), left(l), right(r) {}
};
void task2( TreeNode* root) {



    if(root!=nullptr){


        task2(root->parent);
        task2(root->left);
        task2(root->right);

        std::cout<<root->data<<" ";
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

    std::cout << "Task 2: ";
    task2(root);
    std::cout << std::endl;


    return 0;
}
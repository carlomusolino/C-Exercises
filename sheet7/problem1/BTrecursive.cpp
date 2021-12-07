#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

struct Node
{
    Node* parent;
    bool isleftchild;
    Node* left;              // left child (pointer to)
    Node* right;             // right child
    int   myDepth;           // layer/depth
    void*   myData;            // any data

    Node(Node* parent_init = NULL, bool isleftchild_init = false, Node* left_init = NULL, Node* right_init = NULL, void* myData_init = NULL) : 
    parent(parent_init),
    isleftchild(isleftchild_init),
    left(left_init),
    right(right_init),
    myData(myData_init)
    {
        if (parent)
            myDepth = parent->myDepth + 1;
        else
            myDepth = 0;
    }
};

Node* generateTree(int depth, Node* parent = NULL, bool isleftchild = false)
{
    Node* myTree = new Node(parent, isleftchild);
    if (depth > 1){
        myTree->left = generateTree(depth - 1, myTree, true);
        myTree->right = generateTree(depth - 1, myTree, false);
    }
    return myTree;
}

void removeTree(Node* root)
{
    if (root){
        if (root->parent){
            if (root->isleftchild)
                root->parent->left = NULL;
            else
                root->parent->right = NULL;}
        removeTree(root->left);
        removeTree(root->right);
        delete root;
    }
}

int countNodes(Node* root)
{
    if (root){
        int count = 1;
        count += countNodes(root->left);
        count += countNodes(root->right);
        return count;
    }
    else
        return 0;
}

Node* seekRandomBottomNode(Node* root)
{
    srand(time(NULL));
    int path = rand();
    for (int depth = 1; true; depth <<= 1){
        if (root->left)
            if (root->right && (path & depth))
                root = root->right;
            else
                root = root->left;
        else if (root->right)
            root = root->right;
        else
            return root;
    }
}

Node* findRoot(Node* child)
{
    if (child){
        if (child->parent)
            return findRoot(child->parent);
        else
            return child;
    }
    return NULL;
}

int main()
{
    Node* tree10 = generateTree(10);
    cout << "Number of nodes in a binary tree with depth 10: " << countNodes(tree10) << "\n";
    removeTree(tree10->left);
    cout << "Number of nodes after removing the left child tree: " << countNodes(tree10) << "\n";
    Node* randomBottomNode = seekRandomBottomNode(tree10);
    if (tree10 == findRoot(randomBottomNode))
        cout << "Succeed!\n";
    else
        cout << "Fail!\n";
}

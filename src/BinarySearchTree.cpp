#include "BinarySearchTree.h"
#include <iostream>
#include <vector>

BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
   // root->left = root->right = nullptr;

}

struct BinarySearchTree::Node* BinarySearchTree::newNode(std::string newNodeWord)
{
    BinarySearchTree::Node* temp = new BinarySearchTree::Node;
    temp->value = newNodeWord;
    temp->count += 1;
    temp->left = temp->right = nullptr;
    return temp;
}

//implementation of word insert
void BinarySearchTree::insertNode(std::string wordToInsert)
{
    BinarySearchTree::Node *nodeToInsert = newNode(wordToInsert);
    BinarySearchTree::Node *curr;
    BinarySearchTree::Node *temp;

    if (root == nullptr)
    {
        root = nodeToInsert;
        //root->left = nullptr;
        //root->right = nullptr;
        root->count = 1;
        sizeOfTree++;
    }

    else
    {
        curr = root;

        //traverse until we the first empty pointer to the left or right
        while (curr != nullptr)
        {
            temp = curr;
            if (nodeToInsert->value == curr->value)
            {
                curr->count++;
                return;
            }
            if (nodeToInsert->value > curr->value)
                curr = curr->right;
            else
                curr = curr->left;
        }

        //
        if (nodeToInsert->value > temp->value)
        {
            temp->right = nodeToInsert;
            sizeOfTree++;
            //temp->count += 1;
        }
        else if (nodeToInsert->value < temp->value)
        {
            temp->left = nodeToInsert;
            sizeOfTree++;
            //temp->count += 1;
        }
        //delete nodeToInsert;
        return;
    }
}

void BinarySearchTree::deleteNode(Node *root, std::string wordToDelete)
{
    BinarySearchTree::Node* curr;
    BinarySearchTree::Node* parent;
    BinarySearchTree::Node* temp;

    curr = root;
    if (curr == nullptr)
        return;

    //traverse tree looking for node
    while (curr->value != wordToDelete) {
        parent = curr;

        if (wordToDelete > curr->value) {
            if (curr->right == nullptr)
                return;
            curr = curr->right;
        }

        else if(wordToDelete < curr->value) {
            if (curr->left == nullptr)
                return;
            curr = curr->left;
        }
    }

    if (curr->count > 1)
    {
        curr->count -= 1;
        return;
    }
    //find node and now make the next greatest node the top
    //so I go farthest right from the node as possible. If there is no right to it then just take first left

    //if it has no children just delete it
    if (curr->right == nullptr && curr->left == nullptr)
    {
        if (parent->left == curr)
            parent->left = nullptr;

        else if (parent->right == curr)
            parent->right = nullptr;

        delete curr;
        return;
    }


    //if it has only a left child, make left child parent and delete
    else if (curr->right == nullptr) {
        if (parent->value < curr->left->value)
            parent->right = curr->left;
        else if (parent->value > curr->left->value)
            parent->left = curr->left;
        curr->left = nullptr;
        delete curr;
        return;

    }

    //if it has only a right child, make right child parent and delete
    else if (curr->left == nullptr) {
        if (parent->value < curr->right->value)
            parent->right = curr->right;
        else if (parent->value > curr->right->value)
            parent->left = curr->right;
        curr->left = nullptr;
        delete curr;
        return;
    }

    //if it has two children then have temp hold the current spot (to be deleted), then
    //have curr go to the replacement node and initialize currparent so we can track
    //the parent of the replacement node and reattach at the correct locations.
    else {
        BinarySearchTree::Node* currparent;
        temp = curr;
        curr = curr->right;

        while (curr->left != nullptr) {
            currparent = curr;
            curr = curr->left;
        }

        if (currparent->value != "")
            currparent->left = curr->right;

        curr->left = temp->left;

        if (temp->right != curr)
            curr->right = temp->right;


        //enter if the replacement will be on the left
        if (parent->value > temp->value)
        {

            parent->left = curr;
            temp->right = nullptr;
            temp->left = nullptr;
            delete temp;
            return;

        }
        //enter if the replacement will be on the right
        else if (parent->value < temp->value)
        {

            parent->right = curr;
            temp->right = nullptr;
            temp->left = nullptr;
            delete temp;
            return;
        }
    }

}

void BinarySearchTree::printInOrder(Node *root)
{
    if (root == nullptr)
        return;

    printInOrder(root->left);

    std::cout << root->value << std::endl;

    printInOrder(root->right);
}

void BinarySearchTree::rangeSearch(Node* root, std::string keyA, std::string keyB)
{

    if (root == nullptr)
        return;

    rangeSearch(root->left, keyA, keyB);

    if (root->value >= keyA && root->value <= keyB)
        std::cout << root->value << std::endl;

    rangeSearch(root->right, keyA, keyB);


}

BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::deleteTree(root);
}

void BinarySearchTree::deleteTree(Node* root) {

    if (root == nullptr)
        return;

    deleteTree(root->left);

    root->left = nullptr;
    delete root;

    deleteTree(root->right);
    root->right = nullptr;

}

bool BinarySearchTree::searchTree(std::string wordToSearch) {

    Node* curr = root;
    while (curr != nullptr)
    {
        int compare = wordToSearch.compare(curr->value);
        if (compare == 0) {
//            std::cout << "The word was found.\n";
            return true;
        }
        else if (compare < 0)
            curr = curr->left;
        else
            curr = curr->right;
    }
//    std::cout << "The word was not found.\n";
    return false;
    }

//std::vector<std::string> BinarySearchTree::sortedBSTVec(BinarySearchTree::Node *root) {
//
//    std::vector<std::string> sortedVec;
//
//    if (root == nullptr)
//        return sortedVec;
//
//    sortedBSTVec(root->left);
//
//    sortedBSTVec(root->right);
//}

void BinarySearchTree::printInOrderSort(BinarySearchTree::Node *root) {
    if (root == nullptr)
        return;

    printInOrderSort(root->left);

    sortedVec.push_back(root->value);

    printInOrderSort(root->right);
}


//
// Created by Roderic Deichler on 2/5/18.
//


//
// Created by Roderic Deichler on 2/5/18.
//

#ifndef CS130APROJ1_BINARYSEARCHTREE_H
#define CS130APROJ1_BINARYSEARCHTREE_H

#include <string>
#include <vector>

class BinarySearchTree
{
public:
    struct Node
    {
        std::string value = "";
        Node* left;
        Node* right;
        int count = 0;
    };

private:
    Node* root;
    int sizeOfTree = 0;
    std::vector<std::string> sortedVec;

public:
    BinarySearchTree();                             //default constructor
    struct Node* newNode(std::string newNodeWord);            //creating a new node
    void insertNode(std::string wordToInsert);                 //function to insert word
    void static deleteNode(Node* root, std::string wordToDelete);                 //function to delete word
    void static printInOrder(Node* root);
    void printInOrderSort(Node* root);
    Node* getRoot() {return root;};
    bool searchTree(std::string wordToSearch);
    //std::vector<std::string> sortedBSTVec(Node* root);

    //void sortWords(BinarySearchTree b);           //function to sort words
    void static rangeSearch(Node* root, std::string keyA, std::string keyB);       //function to find all words between
    ~BinarySearchTree();                          //destructor
    void deleteTree(Node* root);
    int getSize() {return sizeOfTree;};
};



#endif //CS130APROJ1_BINARYSEARCHTREE_H

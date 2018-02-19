//
// Created by Roderic Deichler on 2/9/18.
//

#ifndef CS130APROJ1_HASHTABLE_H
#define CS130APROJ1_HASHTABLE_H
#include <string>
#include <vector>
class HashTable {
public:
    struct Node
    {
        std::string value = "";
        int count = 0;
    };
private:
    int sizeOfTable = 0;

public:
    HashTable();
    HashTable(int tableSize);
    struct Node newNode(std::string newNodeWord);
    int getSizeOfTable() {return sizeOfTable;};
    int hashFunction(std::string wordToHash);
    void insertToHashTable(std::string wordToInsert);
    void deleteWord(std::string wordToRemove);
    Node* HashTableArray;
    void rangeSearch(std::string keyA, std::string keyB);
    bool wordSearch(std::string wordToSearch);
    std::vector<std::string> hashSort();
};


#endif //CS130APROJ1_HASHTABLE_H

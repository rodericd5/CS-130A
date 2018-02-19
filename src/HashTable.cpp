//
// Created by Roderic Deichler on 2/9/18.
//
#include "HashTable.h"
#include <string>
#include <iostream>

HashTable::HashTable()
{
    sizeOfTable = 5003;
    HashTableArray = new HashTable::Node[sizeOfTable];
}

HashTable::HashTable(int tableSize)
{
    sizeOfTable = tableSize;
    HashTableArray = new HashTable::Node[sizeOfTable];
}

HashTable::Node HashTable::newNode(std::string newNodeWord) {
    HashTable::Node temp;
    temp.value = newNodeWord;
    temp.count = 1;
    return temp;
}

int HashTable::hashFunction(std::string wordToHash) {

    unsigned int hash = 13;
    int hashMultFactor = 193;

    for (int i = 0; i < wordToHash.length(); i++)
    {
        hash = (hash*hashMultFactor) + wordToHash[i];
    }

    return hash % sizeOfTable;
}

void HashTable::insertToHashTable(std::string wordToInsert) {

    int insertIndex = hashFunction(wordToInsert);
    HashTable::Node tempNode = newNode(wordToInsert);
    int tempIndex = insertIndex;

    if (tempIndex == (this->sizeOfTable - 1))
        tempIndex = 0;
    else
        ++tempIndex;

    //if not in use, insert
    if (HashTableArray[insertIndex].value == "")
        HashTableArray[insertIndex] = tempNode;
    else if (HashTableArray[insertIndex].value == wordToInsert){
        HashTableArray[insertIndex].count += 1;
    }
    //collision probing (Linear probing)
    else
    {
        while (tempIndex != insertIndex) {

            if (HashTableArray[tempIndex].value == "") {
                HashTableArray[tempIndex].value = wordToInsert;
                HashTableArray[tempIndex].count += 1;
                return;
            }else if (HashTableArray[tempIndex].value == wordToInsert) {
                HashTableArray[tempIndex].count += 1;
                return;
            }

            tempIndex++;

            if (tempIndex == (this->sizeOfTable - 1) && tempIndex != insertIndex)
                tempIndex = 0;

        }
    }
}

void HashTable::deleteWord(std::string wordToRemove) {
    int indexToCheck = hashFunction(wordToRemove);
    int tempIndex = indexToCheck;

    if (tempIndex == (this->sizeOfTable - 1))
        tempIndex = 0;
    else
        ++tempIndex;

    //to be overhauled. Will incorporate deleting of nodes
    if (HashTableArray[indexToCheck].value == wordToRemove)
        HashTableArray[indexToCheck].value = "";


    else {
        while (tempIndex != indexToCheck) {

            if (HashTableArray[tempIndex].value == wordToRemove) {
                if (HashTableArray[tempIndex].count == 1) {
                    HashTableArray[tempIndex].count -= 1;
                    HashTableArray[tempIndex].value = "";
                    return;
                }
                else {
                    HashTableArray[tempIndex].count -= 1;
                    return;
                }
            }

            tempIndex++;

            if (tempIndex == (this->sizeOfTable - 1) && tempIndex != indexToCheck)
                tempIndex = 0;

        }

    }
}

void HashTable::rangeSearch(std::string keyA, std::string keyB) {
    for (int i = 0; i < this->sizeOfTable; i++) {
        if (HashTableArray[i].value >= keyA && HashTableArray[i].value <= keyB)
            std::cout << HashTableArray[i].value <<"\n";
    }
}

std::vector<std::string> HashTable::hashSort() {
    std::vector<std::string> hashTableSortedVector;
    for (int i = 0; i < this->sizeOfTable; i++)
        hashTableSortedVector.push_back(HashTableArray[i].value);

    std::sort(hashTableSortedVector.begin(), hashTableSortedVector.end());
    return hashTableSortedVector;
}

bool HashTable::wordSearch(std::string wordToSearch) {
    int insertIndex = hashFunction(wordToSearch);
    int tempIndex = insertIndex;

    if (tempIndex == (this->sizeOfTable - 1))
        tempIndex = 0;
    else
        ++tempIndex;

    //if exists
    if (HashTableArray[insertIndex].value == wordToSearch) {
//        std::cout << "The word was found.\n";
        return true;
    }

        //collision probing (Linear probing)
    else
    {
        while (tempIndex != insertIndex) {

            if (HashTableArray[tempIndex].value == wordToSearch) {
//                std::cout << "The word was found.\n";
                return true;
            }

            tempIndex++;

            if (tempIndex == (this->sizeOfTable) && tempIndex != insertIndex)
                tempIndex = 0;

        }
        return false;
    }
}



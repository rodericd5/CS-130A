#include <iostream>
#include "BinarySearchTree.h"
#include "HashTable.h"
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <chrono>

const std::string SORT_OUTPUT_FILEPATH = "../sort.txt";

const std::string DATA_PATH = "../hotels-small/";

const double NANO = 1000000000.0;


std::vector<std::string> open(std::string path = ".") {
    DIR*    dir;
    dirent* pdir;
    std::vector<std::string> files;

    const char *path_c = path.c_str();
    dir = opendir(path_c);

    while ((pdir = readdir(dir)))
        files.push_back(pdir->d_name);

    return files;
}

void buildHashTableFromBST(HashTable* hashtable, BinarySearchTree::Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    buildHashTableFromBST(hashtable, node->left);
    HashTable::Node tempHashNode = hashtable->newNode(node->value);
    tempHashNode.count = node->count;
    hashtable->insertToHashTable(tempHashNode.value);
    buildHashTableFromBST(hashtable, node->right);
}

HashTable* buildHashTableFromBST(BinarySearchTree* bst)
{
    int size = 3 * bst->getSize() * .5;
    HashTable* hashtable = new HashTable(size);
    BinarySearchTree::Node* node = bst->getRoot();
    buildHashTableFromBST(hashtable, node);
    return hashtable;
}



int main()
{

    BinarySearchTree* bst = new BinarySearchTree();

//    std::vector<std::string> testFiles = open();
    std::vector<std::string> beijingFiles = open(DATA_PATH + "beijing");
    std::vector<std::string> chicagoFiles = open(DATA_PATH + "chicago");
    std::vector<std::string> dubaiFiles = open(DATA_PATH + "dubai");
    std::vector<std::string> lasvegasFiles = open(DATA_PATH + "las-vegas");
    std::vector<std::string> londonFiles = open(DATA_PATH + "london");
    std::vector<std::string> montrealFiles = open(DATA_PATH + "montreal");
    std::vector<std::string> newdelhiFiles = open(DATA_PATH + "new-delhi");
    std::vector<std::string> nycFiles = open(DATA_PATH + "new-york-city");
    std::vector<std::string> sfFiles = open(DATA_PATH + "san-francisco");
    std::vector<std::string> shanghaiFiles = open(DATA_PATH + "shanghai");

    std::vector<std::vector<std::string>> allFiles;

    allFiles.push_back(beijingFiles);
    allFiles.push_back(chicagoFiles);
    allFiles.push_back(dubaiFiles);
    allFiles.push_back(lasvegasFiles);
    allFiles.push_back(londonFiles);
    allFiles.push_back(montrealFiles);
    allFiles.push_back(newdelhiFiles);
    allFiles.push_back(nycFiles);
    allFiles.push_back(sfFiles);
    allFiles.push_back(shanghaiFiles);

    std::vector<std::string> folderNames;

    folderNames.push_back("beijing/");
    folderNames.push_back("chicago/");
    folderNames.push_back("dubai/");
    folderNames.push_back("las-vegas/");
    folderNames.push_back("london/");
    folderNames.push_back("montreal/");
    folderNames.push_back("new-delhi/");
    folderNames.push_back("new-york-city/");
    folderNames.push_back("san-francisco/");
    folderNames.push_back("shanghai/");

    std::string stopWords[127] = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours",
                                  "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers",
                                  "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves",
                                  "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are",
                                  "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does",
                                  "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until",
                                  "while", "of", "at", "by", "for", "with", "about", "against", "between", "into",
                                  "through", "during", "before", "after", "above", "below", "to", "from", "up", "down",
                                  "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here",
                                  "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more",
                                  "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so",
                                  "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now"};

    HashTable* stopWordHashTable = new HashTable(127);
    for (int i = 0; i < 127; i++)
    {
        stopWordHashTable->insertToHashTable(stopWords[i]);
    }

    std::string rgxToken;
    std::string word;
    std::regex rgx("[a-z]+[a-z_'-]*");

    auto start = std::chrono::high_resolution_clock::now();



    for (int i = 0; i < allFiles.size(); i++)
    {
        for (int j = 2; j < allFiles[i].size(); j++)
        {
            std::ifstream file;
            file.open(DATA_PATH + folderNames[i] + allFiles[i][j]);
            while (file >> rgxToken)
            {
                std::transform(rgxToken.begin(), rgxToken.end(), rgxToken.begin(), ::tolower);
                for (std::sregex_iterator it(rgxToken.begin(), rgxToken.end(), rgx), it_end; it != it_end; ++it)
                {
                    word = it->str();
                    if (!(stopWordHashTable->wordSearch(word)))
                        bst->insertNode(word);
                }
            }
            std::cout << bst->getSize() << std::endl;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - start;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
    std::cout << ns / 1000000000.0 <<  " s\n"  << std::endl;

    HashTable* hashTable = buildHashTableFromBST(bst);

    int choice;
    std::string startWord, endWord;
    double seconds;
    double secondsHash;
    std::ofstream sortFile;
    std::vector<std::string> bstSorted, hashSorted;

    std::cout.precision(17);
    std::cout << std::boolalpha;

    while(true)
    {
        std::cout << "Enter a number to execute an action.\n1 (rangeSearch), 2 (insertToHashTable), 3 (delete), 4 (sort), 5 (range rangeSearch).\n";
        std::cin >> choice;

        switch (choice)
        {
            case 1:
                std::cout << "Enter word to rangeSearch:\n";
                std::cin >> word;
                bool found;

                start = std::chrono::high_resolution_clock::now();
                found = bst->searchTree(word);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << found << std::endl;
                std::cout << std::fixed << "BST: " << seconds <<  " s"  << std::endl;

                start = std::chrono::high_resolution_clock::now();
                found = hashTable->wordSearch(word);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << std::fixed << "Hash: " << seconds <<  " s\n"  << std::endl;
                break;

            case 2:
                std::cout << "Enter word to insertToHashTable:\n";
                std::cin >> word;

                start = std::chrono::high_resolution_clock::now();
                bst->insertNode(word);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << std::fixed << "BST: " << seconds <<  " s"  << std::endl;

                start = std::chrono::high_resolution_clock::now();
                hashTable->insertToHashTable(word);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << std::fixed << "Hash: " << seconds <<  " s\n"  << std::endl;
                break;

            case 3:
                std::cout << "Enter word to delete:\n";
                std::cin >> word;

                start = std::chrono::high_resolution_clock::now();
                bst->deleteNode(bst->getRoot(), word);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << "BST: " << std::fixed << seconds <<  " s"  << std::endl;

                start = std::chrono::high_resolution_clock::now();
                hashTable->deleteWord(word);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << std::fixed << "Hash: " << seconds <<  " s\n"  << std::endl;
                break;

            case 4:
                std::cout << SORT_OUTPUT_FILEPATH << std::endl;

                start = std::chrono::high_resolution_clock::now();
                bst->printInOrderSort(bst->getRoot());
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << "BST: " << std::fixed << seconds <<  " s"  << std::endl;

                start = std::chrono::high_resolution_clock::now();
                hashSorted = hashTable->hashSort();
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << "Hash: " << std::fixed << seconds <<  " s\n"  << std::endl;

                sortFile.open(SORT_OUTPUT_FILEPATH);
                for (auto word : bstSorted)
                    sortFile << word + "\n";
                sortFile << "\n";
                for (auto word : hashSorted)
                    sortFile << word + "\n";
                sortFile.close();
                break;

            case 5:
                std::cout << "Enter the start word\n";
                std::cin >> startWord;
                std::cout << "Enter the end word\n";
                std::cin >> endWord;

                start = std::chrono::high_resolution_clock::now();
                bst->rangeSearch(bst->getRoot(),startWord, endWord);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;

                std::cout << std::endl;

                start = std::chrono::high_resolution_clock::now();
                hashTable->rangeSearch(startWord, endWord);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                secondsHash = ns / NANO;
                std::cout << "\nBST: " << std::fixed << seconds <<  " s"  << std::endl;
                std::cout << "Hash: " << std::fixed << secondsHash <<  " s\n"  << std::endl;
                break;
        }

    }


}

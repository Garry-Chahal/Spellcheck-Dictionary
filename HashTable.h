#pragma once
#include <string>
using std::string;

class HashTable
{
private:
    string *wordArray;
    int arraySize;
    int hashFunction2Value;
    int numberOfWordsStored;
    void emptyHashTable();
    int primeNumberSize(const int numberOfItemsToStore) const;
    bool isPrimeNumber(const int number) const;
    void deleteHashTable();
    void copyHashTable(const HashTable &hashTableParameter);
    int stringToIntegerValue(const string stringWord, bool collisionOccured) const;
    int hashValue1(const int key) const;
    int hashValue2(const int key) const;
    void recreateHashTable();

public:
    HashTable();
    HashTable(const int HashTableSize);
    HashTable(const HashTable &hashTableParameter);
    ~HashTable();
    HashTable &operator=(const HashTable &hashTableParameter);
    void insert(const string wordToInsert);
    bool find(const string wordToFind) const;
    int size() const;
    int maxSize() const;
    double loadFactor() const;
};
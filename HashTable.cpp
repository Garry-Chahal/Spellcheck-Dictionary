#include "HashTable.h"

// Creates a HashTable of default size
HashTable::HashTable()
{
    // Default maximum array size: 101
    arraySize = 101;
    numberOfWordsStored = 0;
    wordArray = new string[arraySize];

    // Set all array elements to the empty string
    emptyHashTable();

    // Sets the Double Hashing collision value (P2) to the first
    // prime number greater than array size / 2
    hashFunction2Value = primeNumberSize(arraySize / 2 + 1);
}

// Creates a HashTable to store the # of items from the HashTableSize parameter
HashTable::HashTable(const int HashTableSize)
{
    // Array size should be the first prime number >= HashTableSize parameter
    arraySize = primeNumberSize(2 * HashTableSize);
    numberOfWordsStored = 0;
    wordArray = new string[arraySize];
    emptyHashTable();
    hashFunction2Value = primeNumberSize(arraySize / 2 + 1);
}

// Copy constructor
HashTable::HashTable(const HashTable &hashTableParameter)
{
    copyHashTable(hashTableParameter);
}

// Destructor
HashTable::~HashTable()
{
    deleteHashTable();
}

// Overloads the assignment operator for HashTable objects
HashTable &HashTable::operator=(const HashTable &hashTableParameter)
{
    // Do not do anything if the calling object is the same as the parameter
    if (this != &hashTableParameter)
    {
        // Delete the old HashTable and attributes
        deleteHashTable();
        copyHashTable(hashTableParameter);
    }

    // Return a reference to the calling object
    return *this;
}

// Inserts unique parameter strings into the HashTable
void HashTable::insert(const string wordToInsert)
{
    // We use empty strings to indicate empty spaces in the HashTable
    // Cannot insert empty strings so that we can differentiate contents
    if (wordToInsert == "")
    {
        return;
    }

    // Check if the HashTable does not already contain the parameter
    if (!find(wordToInsert))
    {
        // Get the initial HashFunction for the given parameter string.
        int initialIndex = stringToIntegerValue(wordToInsert, false);
        numberOfWordsStored++;

        // If the initial index is empty, we can insert the string there.
        if (wordArray[initialIndex] == "")
        {
            wordArray[initialIndex] = wordToInsert;
        }
        else
        {
            // Collision detected - find the collision value.
            int collisionIndex = stringToIntegerValue(wordToInsert, true);

            int currentIteration = 1;
            bool findPosition = true;

            // Continue looping until we can reach an empty string in the given index
            while (findPosition)
            {
                // Add the collision value to the initial index
                int newIndex = (initialIndex + currentIteration * collisionIndex) % arraySize;

                if (wordArray[newIndex] == "")
                {
                    // We have found an index to insert the string
                    wordArray[newIndex] = wordToInsert;
                    findPosition = false;
                }
                currentIteration++;
            }
        }

        // If the load factor after insertion is greater than 0.67,
        // create a new larger HashTable with the current stored values.
        if (loadFactor() > 0.67)
        {
            recreateHashTable();
        }
    }
}

// Returns true if its string parameter is in the hash table, false otherwise.
bool HashTable::find(const string wordToFind) const
{
    // Return false if the string parameter is an empty string.
    if (wordToFind == "")
    {
        return false;
    }

    // Get the initial HashFunction for the given parameter string.
    int initialIndex = stringToIntegerValue(wordToFind, false);
    if (wordArray[initialIndex] != wordToFind)
    {
        // The string is not in the initial index, so use the collision value.
        int collisionIndex = stringToIntegerValue(wordToFind, true);
        int currentIteration = 0;

        bool findPosition = true;

        // Continue looping until we find the string or until we reach an empty string
        while (findPosition)
        {
            // Add the collision value to the initial index
            int newIndex = (initialIndex + currentIteration * collisionIndex) % arraySize;

            if (wordArray[newIndex] == wordToFind)
            {
                // Return true if the string is found
                return true;
            }
            if (wordArray[newIndex] == "")
            {
                // Return false if we find an empty string in that index
                return false;
            }
            currentIteration++;
        }
    }
    return true;
}

// Returns the number of items stored in the HashTable
int HashTable::size() const
{
    return numberOfWordsStored;
}

// Returns the size of the HashTable's underlying array
int HashTable::maxSize() const
{
    return arraySize;
}

// Returns the load factor of the HashTable as a double
double HashTable::loadFactor() const
{
    return (double)size() / maxSize();
}

// Sets all HashTable array elements to the empty string
void HashTable::emptyHashTable()
{
    for (int i = 0; i < arraySize; i++)
    {
        wordArray[i] = "";
    }
}

// Returns the first prime number >= to the parameter value.
int HashTable::primeNumberSize(const int numberOfItemsToStore) const
{
    int minimumArraySize = numberOfItemsToStore;

    // The smallest prime number greater than 1 is 2
    if (minimumArraySize <= 1)
    {
        return 2;
    }

    // Keep incrementing minimumArraySize until it is a prime number
    while (!isPrimeNumber(minimumArraySize))
    {
        minimumArraySize++;
    }
    return minimumArraySize;
}

// Returns true if the number is prime, false otherwise.
bool HashTable::isPrimeNumber(const int number) const
{
    // Any number less than or equal to 1 is considered prime.
    if (number <= 1)
    {
        return false;
    }
    for (int i = 2; i <= number / 2; i++)
    {
        // If the number and the current index are divisible, then
        // the number is not prime.
        if (number % i == 0)
        {
            return false;
        }
    }
    return true;
}

// Deallocates memory associated with the HashTable array
// Resets the HashTable private attributes
void HashTable::deleteHashTable()
{
    delete[] wordArray;
    wordArray = nullptr;
    arraySize = 0;
    numberOfWordsStored = 0;
}

// Deep copies the RedBlackTree reference parameter into the calling object
void HashTable::copyHashTable(const HashTable &hashTableParameter)
{
    // Set calling object attributes
    arraySize = hashTableParameter.arraySize;
    numberOfWordsStored = hashTableParameter.numberOfWordsStored;
    hashFunction2Value = hashTableParameter.hashFunction2Value;

    // Copy HashTable parameter contents to the calling object
    wordArray = new string[arraySize];
    for (int i = 0; i < hashTableParameter.arraySize; i++)
    {
        wordArray[i] = hashTableParameter.wordArray[i];
    }
}

// Converts strings to their unique integer representations using Horner's method.
// If collisionOccured is true, then a collision has occured. Calculate the 2nd Hash Function.
// Else, calculate the initial Hash Function.
int HashTable::stringToIntegerValue(const string stringWord, bool collisionOccured) const
{
    int stringLength = stringWord.length();

    // Subtract 96 to get the integer corresponding to the ASCII character
    unsigned int integerValue = (stringWord[0] - 96);

    // Iterate through the rest of the string performing Horner's method
    for (int i = 1; i < stringLength; i++)
    {
        if (collisionOccured)
        {
            // Calculate using the second Hash function
            integerValue = hashValue2((integerValue * 32 + (stringWord[i] - 96)));
        }
        else
        {
            // Calculate using the first Hash function
            integerValue = hashValue1((integerValue * 32 + (stringWord[i] - 96)));
        }
    }
    if (collisionOccured)
    {
        return hashFunction2Value - hashValue2(integerValue);
    }
    else
    {
        return hashValue1(integerValue);
    }
}

// Initial Hash Function when inserting item
int HashTable::hashValue1(const int key) const
{
    return key % arraySize;
}

// Hash Function when dealing with collisions
// Subtract from HashFunction2Value after this has been called
int HashTable::hashValue2(const int key) const
{
    return key % hashFunction2Value;
}

// Creates a new larger HashTable when the load factor is greater than 0.67
void HashTable::recreateHashTable()
{
    // Create a temporary array and copy all the contents over
    int originalSize = arraySize;
    string *originalArray = new string[originalSize];

    for (int i = 0; i < originalSize; i++)
    {
        originalArray[i] = wordArray[i];
    }

    // Delete the old HashTable
    deleteHashTable();

    // Create a new HashTable of size equal to the first prime number greater
    // than the size of the original HashTable array.
    arraySize = primeNumberSize(2 * originalSize + 1);

    // The new array size has increased - find a new Hash function collision value.
    hashFunction2Value = primeNumberSize(arraySize / 2 + 1);

    // Create a new HashTable array and insert all strings from the old HashTable array
    wordArray = new string[arraySize];
    emptyHashTable();

    for (int i = 0; i < originalSize; i++)
    {
        if (originalArray[i] != "")
        {
            insert(originalArray[i]);
        }
    }

    // Delete the temporary array
    delete[] originalArray;
    originalArray = nullptr;
}
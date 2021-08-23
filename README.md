# Spellcheck-Dictionary
Spellcheck Dictionary that utilizes a HashTable implementation in C++ to store and perform spellcheck operations on Strings

The testing framework used to test the HashTable Implementation is Catch2.
More details available here: https://github.com/catchorg/Catch2

### HashTable Method Descriptions:

- default constructor – creates a hash table of default size: 101.
- constructor – creates a hash table to store n items where the value of n is given by the constructor's single integer parameter.
- copy constructor – a constructor that creates a deep copy of its HashTable reference parameter.
- destructor – de-allocates any dynamic memory associated with the calling object.
- operator= – overloads the assignment operator for HashTable objects.
- insert – searches the hash table for the method's string parameter, if a matching string is not found it inserts the parameter string into the hash table.
- find – returns true if its string parameter is in the hash table, returns false if it is not.
- size – returns the number of items stored in the hash table.
- maxSize – returns the size of the hash table’s underlying array.
- loadFactor – returns the load factor of the hash table as a doublen the tree; the contents of the vector are in ascending order.
- size – returns the number of values stored in the tree.

### Spellcheck Method Descriptions:

- extraLetter – if word is not in the dictionary, it returns all strings that can be made by deleting a single letter from the word.
- transposition – if word is not in the dictionary, it returns all strings that can be made swapping any two adjacent letters in the word.
- missingSpace – if word is not in the dictionary, it returns all pairs of strings that can be made by inserting a single space in word.
- missingLetter – if word is not in the dictionary, it returns all strings that can be made by inserting any single letter of the alphabet at any position in word.
- incorrectLetter – if word is not in the dictionary, it returns all strings that can be made by changing any single letter of word to a different letter in the alphabet.

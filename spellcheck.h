#pragma once
#include "HashTable.h"
#include <vector>
#include <algorithm>
using std::sort;
using std::vector;

// Forward Declaration Technique
string swapLetters(string word, const int index1, const int index2);

// If word is not in dict (HashTable dictionary), return all strings that
// can be made by deleting a single letter from word.
// Store and return these sorted strings using a vector.
vector<string> extraLetter(const HashTable &dict, string word)
{
    vector<string> words;

    // If word is in dict, add it to the vector and return.
    if (dict.find(word))
    {
        words.push_back(word);
        return words;
    }

    string currentWord;

    // Iterate through the string parameter
    for (size_t i = 0; i < word.length(); i++)
    {
        string originalWord = word;

        // Delete the letter at the current index.
        currentWord = originalWord.erase(i, 1);

        // If dict contains the word, add it to the vector.
        if (dict.find(currentWord))
        {
            words.push_back(currentWord);
        }
    }
    sort(words.begin(), words.end());
    return words;
}

// If word is not in dict (HashTable dictionary), returns all strings in
// dict that can be made swapping any two adjacent letters in word.
// Store and return these sorted strings using a vector.
vector<string> transposition(const HashTable &dict, string word)
{
    vector<string> words;

    // If word is in dict, add it to the vector and return.
    if (dict.find(word))
    {
        words.push_back(word);
        return words;
    }

    string currentWord;

    // Iterate through the string parameter
    for (size_t i = 0; i < word.length() - 1; i++)
    {
        string originalWord = word;

        // Swap the letters at the current and next index.
        currentWord = swapLetters(word, i, i + 1);

        // If dict contains the word, add it to the vector.
        if (dict.find(currentWord))
        {
            words.push_back(currentWord);
        }
    }
    sort(words.begin(), words.end());
    return words;
}

// If word is not in dict (HashTable dictionary), returns all pairs of strings
// in dict that can be made by inserting a single space in word.
// Store and return these sorted strings using a vector.
vector<string> missingSpace(const HashTable &dict, string word)
{
    vector<string> words;

    // If word is in dict, add it to the vector and return.
    if (dict.find(word))
    {
        words.push_back(word);
        return words;
    }

    string currentWord1;
    string currentWord2;

    // Iterate through the string parameter
    for (size_t i = 0; i < word.length() - 1; i++)
    {
        string originalWord = word;

        // Set the first substring to letters up to the current index.
        currentWord1 = originalWord.substr(0, i + 1);

        // Set the second substring to letters from the current index till the end.
        currentWord2 = originalWord.substr(i + 1, word.length());

        // If dict contains both substrings, add the pair to the vector.
        if (dict.find(currentWord1) && dict.find(currentWord2))
        {
            words.push_back(currentWord1 + " " + currentWord2);
        }
    }
    sort(words.begin(), words.end());
    return words;
}

// If word is not in dict (HashTable dictionary), return all strings in dict
// that can be made by inserting a letter of the alphabet at any position in word.
// Store and return these sorted strings using a vector.
vector<string> missingLetter(const HashTable &dict, string word)
{
    vector<string> words;

    // If word is in dict, add it to the vector and return.
    if (dict.find(word))
    {
        words.push_back(word);
        return words;
    }

    string currentWord;

    // Iterate through the string parameter
    for (size_t i = 0; i <= word.length(); i++)
    {
        // Iterate through the alphabet
        for (char letter = 'a'; letter <= 'z'; letter++)
        {
            string originalWord = word;

            // Insert the current alphabet letter into the current string index
            currentWord = originalWord.insert(i, 1, letter);

            // If dict contains the word, add it to the vector.
            if (dict.find(currentWord))
            {
                words.push_back(currentWord);
            }
        }
    }
    sort(words.begin(), words.end());
    return words;
}

// If word is not in dict (HashTable dictionary), return all strings in dict
// that can be made by changing a letter of word to a different letter.
// Store and return these sorted strings using a vector.
vector<string> incorrectLetter(const HashTable &dict, string word)
{
    vector<string> words;

    // If word is in dict, add it to the vector and return.
    if (dict.find(word))
    {
        words.push_back(word);
        return words;
    }

    string currentWord;

    // Iterate through the string parameter
    for (size_t i = 0; i < word.length(); i++)
    {
        // Iterate through the alphabet
        for (char letter = 'a'; letter <= 'z'; letter++)
        {
            string originalWord = word;

            // Replace the current alphabet letter with the current string index
            currentWord = originalWord.replace(i, 1, 1, letter);

            // If dict contains the word, add it to the vector.
            if (dict.find(currentWord))
            {
                words.push_back(currentWord);
            }
        }
    }
    sort(words.begin(), words.end());
    return words;
}

// Helper function to swap characters in the string
string swapLetters(string word, const int index1, const int index2)
{
    char tempLetter = word[index1];
    word[index1] = word[index2];
    word[index2] = tempLetter;

    return word;
}
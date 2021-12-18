/*
  Name: Wei Da Chen
  Date: 11/2/2021
	File: spell_check.cc
*/

/*
This file contains the SpellChecker program which implements a linear/quadratic/double
hashing algorithm. It reads a dictionary txtfile and a sample txtfile and compares
the words in them.

The SpellChecker programs checks for 3 cases:
- Removed characters
- Added characters
- Swapped characters
*/

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>     /* exit, EXIT_FAILURE */

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
using namespace std;

// You can add more functions here.

// Creates and fills double hashing hash table with all words from
// dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file) {
  HashTableDouble<string> dictionary_hash;
  // Fill dictionary_hash.
  ifstream inputFile;
  string line;

  inputFile.open(dictionary_file);
  if (inputFile.fail()) {
    cout << "Error opening dictionary file: " << dictionary_file << endl;
    exit(EXIT_FAILURE);
  }

  while (inputFile >> line) {
    dictionary_hash.Insert(line);
  }

  return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary, const string &document_file) {
  ifstream inputFile;
  string line;

  inputFile.open(document_file);
  if (inputFile.fail()) {
    cout << "Error opening document file: " << document_file << endl;
    exit(EXIT_FAILURE);
  }

  while (inputFile >> line) {
    // turning all characters into lowercase
    for (size_t i = 0; i < line.length(); i++) {
      line[i] = tolower(line[i]);
    }

    size_t indexOfLine = line.length() - 1;

    // parsing non-alphabets
    while (line[indexOfLine] < 'a' || line[indexOfLine] > 'z') {
      if (line[indexOfLine] >= '0' && line[indexOfLine] <= '9') {
        break;
      }

       line = line.substr(0, indexOfLine);
       indexOfLine--;
    }

    if (dictionary.Contains(line)) {
      cout << line << " is CORRECT" << endl;
    }
    else {
      cout << line << " is INCORRECT" << endl;

      // Case A - removed characters
      for (unsigned int i = 0; i <= line.length(); i++) {
        for (char j = 'a'; j <= 'z'; j++) {
          string word = line;
          string temp(1, j);
          word.insert(i, temp);

          if (dictionary.Contains(word)) {
            cout << "*** " << line << " -> " << word << " *** case A" << endl;
          }
        }
      }

      // Case B - Added characters
      for (unsigned int i = 0; i < line.length(); i++) {
        string word = line;
        word.erase(i, 1);

        if (dictionary.Contains(word)) {
          cout << "*** " << line << " -> " << word << " *** case B" << endl;
        }
      }

      // Case C - Swapped characters
      for (unsigned int i = 0; i < line.length() - 1; i++) {
        string word = line;
        char temp = word[i];
        word[i] = word[i + 1];
        word[i + 1] = temp;

        if (dictionary.Contains(word)) {
          cout << "*** " << line << " -> " << word << " *** case C" << endl;
        }
      }
    }
  }
}

// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }

  testSpellingWrapper(argc, argv);

  return 0;
}

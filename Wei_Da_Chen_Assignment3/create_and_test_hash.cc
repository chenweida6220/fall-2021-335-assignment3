/*
  Name: Wei Da Chen
  Date: 11/2/2021
	File: create_and_test_hash.cc
*/

/*
This file contains the test functions for Linear, Quadratic, and Double Hashing.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>     /* exit, EXIT_FAILURE */

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"

using namespace std;


// You can add more functions here

// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
    //..Insert your own code
		hash_table.MakeEmpty();
		hash_table.resetNumOfCollisions();

		// Reading Words File
		ifstream words_file;
		string line;

		words_file.open(words_filename);
		if (words_file.fail()) {
			cout << "Error opening Words File: " << words_filename << endl;
			exit(EXIT_FAILURE);
		}

		while (words_file >> line) {
			hash_table.Insert(line);
		}

		cout << "number_of_elements: " << hash_table.getNumOfElements() << endl;
		cout << "size_of_table: " << hash_table.getSize() << endl;
		cout << "load_factor: " << hash_table.calcLoadFactor() << endl;
		cout << "average_collisions: " << hash_table.calcAverageNumOfCollisions() << endl;
		cout << "total_collisions: " << hash_table.getNumOfCollisions() << endl;

		cout << endl;

		// Reading Query File
		ifstream query_file;

		query_file.open(query_filename);
		if (query_file.fail()) {
			cout << "Error opening Query File: " << query_filename << endl;
			exit(EXIT_FAILURE);
		}

		while (query_file >> line) {
			hash_table.resetNumOfCollisions();

			if (hash_table.Contains(line)) {
				cout << line << " Found " << hash_table.getNumOfCollisions() + 1 << endl;
			}
			else {
				cout << line << " Not_Found " << hash_table.getNumOfCollisions() + 1 << endl;
			}
		}


}

// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5) {
			const string rvalue(argument_list[4]);
			R = stoi(rvalue);
    }

    if (param_flag == "linear") {
			// Uncomment below when you have implemented linear probing.
      HashTableLinear<string> linear_probing_table;
      TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
    }
		else if (param_flag == "quadratic") {
			HashTable<string> quadratic_probing_table;
			TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
    }
		else if (param_flag == "double") {
			cout << "r_value: " << R << endl;
			// Uncomment below when you have implemented double hashing.
			HashTableDouble<string> double_probing_table;
			double_probing_table.setRValue(R);
			TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
    }
		else {
			cout << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
	cout << "Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag>" << endl;
	cout << "or Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
	return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}

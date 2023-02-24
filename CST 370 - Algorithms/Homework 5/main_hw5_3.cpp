/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw5_3.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw5_3.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract,Name, and Date.
/*
 * Title: main_hw5_3.cpp
 * Abstract: This program implements the operations of a hash table using linear probing.
 * Name: Jennah Yasin
 * Date: December 4, 2022
 */
#include <cmath>
#include <iostream>
#include <limits.h>
#include <sstream>
#include <vector>
using namespace std;

//function that pulls out integer value from string
//and returns the int value
int findIntInString(string str){
	// convert string into stringstream
	stringstream commandString;
	commandString << str;
	string temp;
	int intFound;
  // runs loop until end of stream
	while (!commandString.eof()) {
		commandString >> temp; // extracts word by word from stream
    //if there is an int found in the string, return it
		if (stringstream(temp) >> intFound) {
			return intFound;
		}
		temp = "";
	}
	return intFound;
}

//function that handles inserting an integer to the hash table
void insert(int tableSize, vector<int> &hashTable, int keys, int &currentSize){
  //calculates index value of inserted value 
  //which is the inserted key % tableSize
	int indexValue = keys % tableSize;
  //if hash table at that index position is empty, add that key to that position.
  //hashTable vector elements were initially set to INT_MAX, so INT_MAX == empty position
	if (hashTable[indexValue] == INT_MAX) { 
		hashTable[indexValue] = keys;
	} else {
    //otherwise, if index already filled (not empty)
    //, perform Linear Probing operation:
		while (hashTable[indexValue] != INT_MAX) { 
			indexValue = (indexValue + 1) % tableSize; //add element to next empty index
		}
		hashTable[indexValue] = keys; //set keys to corresponding index values
	}
}

//function that performs rehashing when load factor > 0.5
void rehash(int nextPrimeSize, int &tableSize, vector<int> &hashTable, int &currentSize){
  //finds next prime number of double the orginal table size
	int nextPrimeNum = (2 * tableSize);
	bool foundNextPrime = false;
	while (1) {
    //keeps incrementing original size * 2 until next prime is found
		nextPrimeNum++;
		foundNextPrime = false;
    //checks if a number is prime 
		for (int i = 2; i <= sqrt(nextPrimeNum); i++) {
			if (nextPrimeNum % i == 0) {
				foundNextPrime = true;
				break;
			}
		}
		if (foundNextPrime == false) {
			break;
		}
	}
  //sets new table size to found prime number of original size * 2
	nextPrimeSize = nextPrimeNum;

  //new vector for new rehashed table
  //all elements of vector are initially set to INT_MAX (= empty)
	vector<int> rehashTable(nextPrimeSize, INT_MAX);
	for (int i = 0; i < tableSize; i++) {
    //redo insert for the values that have already been inserted
		if (hashTable[i] != INT_MAX) {
      insert(nextPrimeSize, rehashTable, hashTable[i], currentSize);
		}
	}
  //set hash table to rehashed table
	hashTable = rehashTable;
  //set table size to new table size
	tableSize = nextPrimeSize;
}

//function that searches if a given value is found in hash table
void search(int value, int keys, vector<int> &hashTable) {
  //checker variable
	bool check = false;
	for (int i = 0; i < keys; i++) {
    //if value entered by user is found in hash table vector
		if (hashTable[i] == value) {
			check = true;
      //display (value) Found
			cout << value << " Found" << endl;
			break;
		}
	}
  //otherwise, value entered is not in hash table
	if (check == false) {
		cout << value << " Not found" << endl;
	}
}

//function that displayst the current size of hash table 
void displayTableSize(int &tableSize) {
	cout << tableSize << endl;
}

//function that displays status of given index position
void displayStatus(int keys, int value, vector<int> &hashTable) {
	int index = value % keys;
  //finds all index that are not empty
	if (hashTable[index] != INT_MAX) {
    //displays the values at that specific index
		cout << hashTable[index] << endl;
	} else {
		cout << "Empty" << endl;
	}
}

int main() {
  //gets size of table from user
	int tableSize;
	cin >> tableSize;
  
	int keys;
	int nextPrimeSize;
	int currentSize = 0;
  
  //gets total number of operations user will enter
	int numCommands;
	cin >> numCommands;

  //holds all values of hashTable (key & values)  
	vector<int> hashTable(tableSize, INT_MAX); //elements initially set to INT_MAX (all empty positions)
	vector<string> commands; //holds all commands entered by user
	string userCommand; //actual command entered by user
  
	for (int i = 0; i <= numCommands; i++) {
		getline(cin, userCommand); // gets users input line by line
		commands.push_back(userCommand); //adds all entered commands in commands vector
	}

  //loops until all commands have been processed
	for (int i = 0; i < commands.size(); i++) {
    //insert command:
		if (commands[i].substr(0, 6) == "insert") {
			keys = findIntInString(commands[i]); //finds integer in entered string
			insert(tableSize, hashTable, keys, currentSize);
			currentSize++; //increment size everytime new element inserted
      
			double loadFactor;
      //calculates load factor 
			loadFactor = (double(currentSize) / tableSize);
      //if load factor is greater than 0.5, rehash table
			if (loadFactor > 0.5) {
				rehash(nextPrimeSize, tableSize, hashTable, currentSize);
      }
      
		}
    //search command:
    else if (commands[i].substr(0, 6) == "search") {
			search(findIntInString(commands[i]), keys, hashTable);
		}
    //tableSize command:
    else if (commands[i].substr(0, 5) == "table") {
			displayTableSize(tableSize);
		} 
    //displayStatus command:
    else if (commands[i].substr(0, 7) == "display") {
			displayStatus(keys, findIntInString(commands[i]), hashTable);
		}
	}
	return 0;
}

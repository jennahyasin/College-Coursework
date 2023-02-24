/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw5_1.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw5_1.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw5_1.cpp
 * Abstract: This program implements heap operations and specifically follows max heap instructions.
 * Name: Jennah Yasin
 * Date: December 4, 2022
 */
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

bool maxHeapCheck(vector<int> &values) {
	for (int i = 0; i < values.size(); i++) {
		// if parent is less than left child node, return false
		// breaks max heap conditions
		if (values[i] < values[(2 * i) + 1]) {
			return false;
		}
		// if parent is less than right child node, return false
		// breaks max heap conditions
		if ((values.size() > 2 * i + 2) && (values[(2 * i) + 2] > values[i])) {
			return false;
		}
	}
	return true;
}

// displays max of the heap which is the root node of a max heap
int displayMax(vector<int> &values) {
	// root node is position 0 of max heap
	return values[0];
}

void heapify(vector<int> &values) {
int holdCurrent;
	int lastNode = values.size() / 2;
  //holds child value of which is largest
	int largerChild, leftChild, rightChild;
	int index = lastNode; // starts from the bottom
	while (index >= 0) { //loops until index reaches the root node
    // index starts from smallest, left node
		index = min(index, lastNode); 
    //left leaf node
		leftChild = (2 * index) + 1;
    //right leaf node
		rightChild = (2 * index) + 2; 
    //checks case if last node only has 1 child
		if (rightChild >= values.size()) {
      //the left child is the larger child
			largerChild = leftChild;
		} 
    else {
      //if the right child is greater than left child
			if (values[rightChild] > values[leftChild]) {
        //right child is larger child
				largerChild = rightChild;
			} 
      else {
        //otherwise, left child is larger child
				largerChild = leftChild;
			}
		}

    //if larger child is larger than the index
		if (values[largerChild] > values[index]) {
      //hold the current of index in values in variable
			holdCurrent = values[index];
      //set parent to the largest child
			values[index] = values[largerChild];
      //largest child is stored with current index
			values[largerChild] = holdCurrent;
			index = largerChild;
		} 
    //next node
    else {
			index = index - 1;
		}
	}

}
void insertNode(vector<int> &values, int newValue) {
	// int lastNode = values.size() - 1;
	values.push_back(newValue);
	heapify(values);
}
void deleteMax(vector<int> &values) {
	int lastNode = values[values.size() - 1];
	// int maxNode = values[0];
	values[0] = lastNode; // sets the root to the most recently added node
	values.pop_back();	// removes most recently added node
	// adjusts heap to new root value
	heapify(values);
}

// displays the nodes of the max heap
void display(vector<int> &values) {
	for (int i = 0; i < values.size(); i++) {
		// checks if current element is last element,
		// if it is last element don't print space after
		if (values[i] == values[values.size() - 1]) {
			cout << to_string(values[i]);
		} else {
			cout << to_string(values[i]) << " ";
		}
	}
	cout << endl;
}

// function to pull out integer from string input
// used for the insert operation
int findIntInString(string stringInput) {
	stringstream commandString;
	commandString << stringInput;
	string temp;
	int intFound;
	while (!commandString.eof()) {
		commandString >> temp;
		if (stringstream(temp) >> intFound) {
			return intFound;
		}
		temp = "";
	}
	return intFound;
}

int main() {
	// total number of values in heap
	int numValues;
	cin >> numValues;

	// holds values in vector
	vector<int> values;
	// actual values
	int actualValues;
	for (int i = 0; i < numValues; i++) {
		cin >> actualValues;
		// add all values to vector
		values.push_back(actualValues);
	}

	// total number of operations user will enter
	int numOperations;
	cin >> numOperations;

	// vector holds all of users commands
	vector<string> commands;
	// actual command entered by user
	string userInput;

	for (int i = 0; i <= numOperations; i++) {
		// gets user input of commands
		getline(cin, userInput);
		// adds all commands entered into commands vector
		commands.push_back(userInput);
	}

	// checks if heap is a max heap
	if (maxHeapCheck(values)) {
		cout << "This is a heap." << endl;
	} else {
		cout << "This is NOT a heap." << endl;
		// since not a max heap, build the heap correctly
		heapify(values);
	}

	// loops through commands until all commands have been done
	for (int i = 0; i <= commands.size(); i++) {
		// If user enters Display Max Command:
		if (commands[i] == "displayMax") {
			cout << displayMax(values) << endl;
		}
		// If user entersInsert Command:
		else if (commands[i].substr(0, 6) == "insert") {
			int insertValue = findIntInString(commands[i]);
			insertNode(values, insertValue);
		}
		// If user enters Delete Max Command:
		else if (commands[i] == "deleteMax") {
			deleteMax(values);
		}
		// If user enters Display Comand
		else if (commands[i] == "display") {
			display(values);
		}
	}
	return 0;
}

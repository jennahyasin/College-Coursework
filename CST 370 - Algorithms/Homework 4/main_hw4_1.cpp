/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw4_1.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw4_1.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw4_1.cpp
 * Abstract: This program represents the partitioning of numbers in two
 * different approaches: approach 1 & approach 2.
 * Name: Jennah Yasin
 * Date: November 29, 2022
 */

#include <array>
#include <iostream>
using namespace std;

int main() {
	// total number of integers in the array
	int numValues;
	cin >> numValues;

	// actual numbers in array
	int approach1[numValues];
	int approach2[numValues];
	for (int i = 0; i < numValues; i++) {
		// fill array with inputted values from user
		cin >> approach1[i];
		// set both arrays to be filled with same input from user
		approach2[i] = approach1[i];
	}

	//**********APPROACH 1 **************//

	int i = 0;			   // first element in array
	int j = numValues - 1; // last element of array
	do {
		// if both i and j are positive:
		if (approach1[i] >= 0 && approach1[j] >= 0) {
			j--; // move j to the left one
		}
		// if i is negative and j is positive:
		else if (approach1[i] < 0 && approach1[j] >= 0) {
			i++; // move i to the right one
		}
		// if both i and j are negative:
		else if (approach1[i] < 0 && approach1[j] < 0) {
			i++; // move i to the right one
		}
		// if i is positive and j is negative:
		else if (approach1[i] >= 0 && approach1[j] < 0) {
			swap(approach1[i], approach1[j]); // swap the values
		}
	} while (i != j); // do until i != j (all numbers are sorted)

	// Print out sorted array of approach 1:
	for (int k = 0; k < numValues; k++) {
		// if current element is last element, dont add space
		if (approach1[k] == approach1[numValues - 1]) {
			cout << approach1[k] << endl;
		}
		// add space between numbers
		else {
			cout << to_string(approach1[k]) + " ";
		}
	}

	//**********APPROACH 2 **************//

	// two trackers that both start at the first element of array
	int m = 0; // holds position of first positive #
	int q = 0; // scans array from left to right

	do {
		// if m and q are positive:
		if (approach2[m] >= 0 && approach2[q] >= 0) {
			q++; // move q to the right one
		}
		// if m is negative and q is positive:
		else if (approach2[m] < 0 && approach2[q] >= 0) {
			m++; // move m to the right one
			q++; // move q to the right one
		}
		// if m and q are both negative
		else if (approach2[m] < 0 && approach2[q] < 0) {
			m++; // move m to the right one
			q++; // move q to the right one
		}
		// if m is positive and q is negative:
		else if (approach2[m] >= 0 && approach2[q] < 0) {
			// swap values to sort array
			swap(approach2[m], approach2[q]);
		}
	} while (q != numValues); // do until all numbers of array are sorted

	// print out sorted array of Approach 2:
	for (int k = 0; k < numValues; k++) {
		// if current element is the last element, don't add space
		if (approach2[k] == approach2[numValues - 1]) {
			cout << approach2[k] << endl;
		}
		// print elements of sorted array with spaces between
		else {
			cout << to_string(approach2[k]) + " ";
		}
	}
	return 0;
}

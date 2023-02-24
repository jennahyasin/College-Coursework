/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw4_2.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw4_2.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw4_2.cpp
 * Abstract: This program uses divide and conquer and recursion to display the max number in an array inputted by the user. 
 * Name: Jennah Yasin
 * Date: November 29, 2022
 */

#include <iostream>
using namespace std;

int largestNum_div_conq(int values[], int start, int end);
int main() {
  //number of values in the array (size)
	int numOfValues;
	cin >> numOfValues;

  //array that holds actual numbers
	int values[numOfValues];
	for (int i = 0; i < numOfValues; i++) {
    //numbers are inputted by user
		cin >> values[i];
	}

	int start;
	int end;
  //calls the function for users input
	int largestNum = largestNum_div_conq(values, 0, numOfValues - 1);

  //displays the largest number in array
	cout << largestNum << endl;
}

//function that uses divide and conquer to find max number in an array
int largestNum_div_conq(int values[], int start, int end) {
  //base case
  //if theres only one number in the array, that is the max number
	if (start == end) {
		return values[start];
	} 
  else {
    //divides the problem into two subproblems
		int largestNum1 = largestNum_div_conq(values, start, (start + end) / 2);
		int largestNum2 =
			largestNum_div_conq(values, ((start + end) / 2) + 1, end);

    //combines two subproblems & finds the largest between the two subproblems
    //if first is greater than second, return first number
		if (largestNum1 > largestNum2) {
		  return largestNum1;
		} 
    //if second is greater than first subproblem, return second number
    else {
		  return largestNum2;
		}
	}
}

/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw6_1.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw6_1.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw6_1.cpp
 * Abstract: This program is an implementation of the max coin collecting
   problem where the max number of coins that can be collected of an inputted
   table is displayed along with the path for that max finding. 
 * Name: Jennah Yasin
 * Date: December 10, 2022
 */
#include <iostream>
#include <vector>
using namespace std;

// function that implements the max coin collecting problem
void countMaxCoins(
	int i,
	int j,
	int currentCoin,
	int numRows,
	int numColumns,
	vector<vector<int>> &matrixData,
	vector<pair<int, int>> currentPath,
	vector<pair<int, int>> &holdOptimalPath,
	int &maxCoinsFound) {
	// if the current is not outside of the table
	if (i < numRows && j < numColumns) {
		// adds the current pairs to the current path vector
		currentPath.push_back({i + 1, j + 1});
	} else {
		// if out of parameters of table, don't add to current path vector
		return;
	}
	// recursive call to function
	countMaxCoins(i + 1,j,currentCoin + matrixData[i][j],numRows,numColumns,matrixData,currentPath,holdOptimalPath,maxCoinsFound);
	countMaxCoins(i,j + 1,currentCoin + matrixData[i][j],numRows,numColumns,matrixData,currentPath,holdOptimalPath,maxCoinsFound);

	// update the optimal path with the one that holds the most coins
	// when you reach the end of the table
	if (i == matrixData.size() - 1 && j == matrixData[i].size() - 1) {
		// if the current path is larger than max, set it to the new max
		if (currentCoin + matrixData[i][j] > maxCoinsFound) {
			// set to new max
			maxCoinsFound = matrixData[i][j] + currentCoin;
			// set optimal path to current path
			holdOptimalPath = currentPath;
		}
	}
}

// function that displays the maximum coins found with its corresponding path
void displayMatrix(
	int &maxCoinsFound,
	vector<pair<int, int>> &holdOptimalPath,
	int numRows,
	int numColumns) {
	cout << "Max coins:" << maxCoinsFound << endl;
	cout << "Path:";
	// print out content of vector
	for (auto pairs : holdOptimalPath) {
		// if it is the last element of vector don't add "->""
		if (pairs.first == numRows && pairs.second == numColumns) {
			cout << "(" << pairs.first << "," << pairs.second << ")" << endl;
		} 
    else {
			// add arrow between pairs in the path
			cout << "(" << pairs.first << "," << pairs.second << ")"
				 << "->";
		}
	}
}

int main() {
	// table info
	// get number of rows and columns of table
	int numRows;
	int numColumns;
	// user input of table size (m x n)
	cin >> numRows >> numColumns;

	// vector that holds the values in the table entered by user
	vector<vector<int>> matrixData(numRows, vector<int>(numColumns));
	// vector that holds the pairs of the current path of coin collecting
	vector<pair<int, int>> currentPath;
	// vector that holds the optimal/final path pairs (max coins)
	vector<pair<int, int>> holdOptimalPath;

	int i = 0; // index to move down
	int j = 0; // index to move left
	int currentCoin = 0;
	int maxCoinsFound = 0;
	// get user input
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numColumns; j++) {
			cin >> matrixData[i][j];
		}
	}
	// function call to implement max coin collecting problem
	countMaxCoins(i,j,currentCoin,numRows,numColumns,matrixData,currentPath,holdOptimalPath,maxCoinsFound);

	// funciton call to display the max coins and its corresponding path of pairs
	displayMatrix(maxCoinsFound, holdOptimalPath, numRows, numColumns);

	return 0;
}

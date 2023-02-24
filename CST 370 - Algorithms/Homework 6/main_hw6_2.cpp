/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw6_2.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw6_2.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw6_2.cpp
 * Abstract: This program implements Floyd's Algorithm and ultimately displays the minimum path between each pair of the graph/matrix.
 * Name: Jennah Yasin
 * Date: December 10, 2022
 */
#include <iostream>
#include <vector>
using namespace std;

// function for printing out the resulting matrix
void printMatrix(vector<vector<int>> &matrixData2, int numVertices) {
	for (int i = 0; i < matrixData2.size(); i++) {
		for (int j = 0; j < matrixData2[i].size(); j++) {
			// checks if the current element is the last element
			if (j == matrixData2[i].size() - 1) {
				// if it is, don't print space after
				cout << matrixData2[i][j];
			} 
      else {
				// print matrix elements with spaces between
				cout << to_string(matrixData2[i][j]) << " ";
			}
		}
		// new line after ever row in the matrix
		cout << endl;
	}
}

// function that implements floyd's algorithm
void floydAlgorithm(int numVertices, vector<vector<int>> &matrixData) {
	// temp vector that holds original matrix info
	vector<vector<int>> matrixData2 = matrixData;

	for (int k = 0; k < numVertices; k++) {
		for (int i = 0; i < numVertices; i++) {
			for (int j = 0; j < numVertices; j++) {
        //find connecting elements for index that is not set to -1 
				if (matrixData2[k][j] != -1 && matrixData2[i][k] != -1) {
          //if current is set to -1:
					if (matrixData2[i][j] == -1) {
            //change it to newcalculated path
						matrixData2[i][j] = matrixData2[i][k] + matrixData2[k][j];
					} 
          else {
            //hold the shortest path 
						matrixData2[i][j] = min(matrixData2[i][j], matrixData2[i][k] + matrixData2[k][j]);
					}
				}
			}
		}
	}
  //call print function to display the resulting matrix
	printMatrix(matrixData2, numVertices);
}

int main() {
  //size of matrix
	int numVertices;
  //prompt user to input size of matrix
	cin >> numVertices;

  //vector that holds the data in the matrix
	vector<vector<int>> matrixData(numVertices, vector<int>(numVertices));

  //fill the matrix with user's input
	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			cin >> matrixData[i][j];
		}
	}
  //call function to implement floyd algorithm on inputted matrix
	floydAlgorithm(numVertices, matrixData);

	return 0;
}

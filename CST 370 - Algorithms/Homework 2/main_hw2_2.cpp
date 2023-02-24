/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw2_2.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw2_2.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw2_2.cpp
 * Abstract: This program displays all possibe combinations of a set that the user enters besides the list of index in decimal and their binary representations depending on the set size provided.
 * Name: Jennah Yasin
 * Date: November 8, 2022
 */
#include <bits/stdc++.h> //for the pow function
#include <iostream>
using namespace std;

//This function fills in the 0:0:EMPTY format from left to right,
//and stops when no more combinations exists. Starts with displaying
//the index of combination, then adds on the binary representation of that
//index value, and finally displays all possible combinations of the elements
//that the user inputted
int main()
{
    double setSize; //number of items that user types in for set
                    //set as a double variable instead of int for later 
                    //use of power (pow) function.
    cin >> setSize; 
    string setElements[int(setSize)]; //array of all elements entered by user
    //adds elements entered by user to the array
    for(int i = 0; i < int(setSize); i++){
      cin >> setElements[i];
    }

    //Total number of combinations can be found by calculating 2 ^ size of set
    int numOfCombinations = pow(2.0, setSize); //2^setSize

    //for all of the combinations, display index, binary reperesenation
    //and actual set elements
    for(int i = 0; i < numOfCombinations; i++){
      //displays the index of combination
      cout << i << ":";
      //Used logic of the decimal to binary program provided to 
      //convert decimal values to binary
      int decimalNumber = i; //
      int binaryNum[32];
      int k = 0; //holds binary array
      //decimal to binary calculation for integers greater than 0
      while(decimalNumber > 0){
        binaryNum[k] = decimalNumber % 2;
        decimalNumber = decimalNumber / 2;
        k++;
      }

      //checks if binary value is less than the number of integers of set 
      // i.e: if user enters 3, binary values must be 3 integers (0 -> 000)
      if(k < int(setSize)){
          //adds zeros to binary #s that are less than set size
          for(int j = k; j < int(setSize); j++){
            binaryNum[j] = 0;
          }
      }
      
      //if user inputs 0 for set size, display 0 for binary value
      if(setSize == 0){
        cout<< 0;
      }
      
      //displays decimal number in binary 
      for(int j = int(setSize) - 1; j >= 0; j--){
        cout << binaryNum[j];
      }

      cout<<":";
      
      //Displaying all of the subsets 
      int temp = 0; //postion of current index
      int tracker = 0; //stores amount of 1's in binary
      vector <string> allValues; //vector that holds all content of set
      
      //Prints out subsets from last to first index
      for(int j = int(setSize) - 1; j >= 0; j--){
        if(binaryNum[j] == 1){
          //adds all elements to allValues vector
          allValues.push_back(setElements[temp]);

          //if current element is the first, dont add space before
          if(allValues.front() == setElements[temp]){
             cout<<setElements[temp];
          }
          //add space between every element
          else{
            cout<< " " + setElements[temp];
            }
          tracker++;
        }
        temp++;
       }
      
      //if binary value contains 0 1's (0), display EMPTY
      if(tracker == 0){
        cout <<"EMPTY";
      }
      
      cout<<endl;
    }
    return 0;

}

/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw1_1.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw1_1.cpp". Please DO NOT change
 *     the name of the main procecure "main()"
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw1_1.cpp
 * Abstract: This program allows the user to enter a chosen amount of integers and find the shortest distance between all of the integers. 
 * Name: Jennah Yasin
 * Date: October 31, 2022
 */
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
    int minDiff; //holds the value of the minimum distance
    int difference; //calculates the difference between 2 integers
    int totalValues; //number of integers user will enter
    //gets users input for number of integers that will be entered
    cin >> totalValues;
    int numberArray[totalValues]; 
    //vector of integers that holds difference between all value
    vector <int> differenceValues;
    //getting the users input based on first number entered
    for(int i = 0; i<totalValues; i++){
      cin >> numberArray[i];
    }
  
    //goes through the array of numbers to calculate difference between each two numbers
    for(int i = 0; i<totalValues; i++){
      for(int j = i+1; j<totalValues; j++){
        difference = numberArray[j] - numberArray[i];
        //adds the difference calculations to a new vector
        differenceValues.push_back(abs(difference));
        //finds minimum difference in the created vector
        minDiff = *min_element(differenceValues.begin(), differenceValues.end());
      }
    }
    //Prints out all content of vector
    cout << "Min Distance:" << minDiff <<endl;

    for(int i = 0; i<totalValues; i++){
      for(int j = i+1; j<totalValues; j++){
          int n = sizeof(numberArray) / sizeof(numberArray[0]);
          sort(numberArray, numberArray + n);
          //prints the pairs in ascending order
          if(abs(numberArray[j] - numberArray[i]) == minDiff){
            if(numberArray[i]<numberArray[j]){
              cout<<"Pair:" << numberArray[i] << " " << numberArray[j]<<endl; 
            }
            else if(numberArray[i]>numberArray[j]){
              cout<<"Pair:"<< numberArray[j] << " " << numberArray[i]<<endl; 
            }
          }
      }
    }
    return 0;
}

  
  
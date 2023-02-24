/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw3_1.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw3_1.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw3_1.cpp
 * Abstract: This program allows the user to input integers of a chosen size and be presented with the integers in ascending order as well as short representation for numbers that are consecutive (i.e: 1 2 3: 1-3).
 * Name: Jennah Yasin
 * Date: November 15, 2022
 */
#include<bits/stdc++.h>
#include <algorithm>
#include <iostream>
using namespace std;


int main()
{
  int numValues; //total number of values to be inputted
  cin >> numValues; 

  int values[numValues]; //array that holds all entered by user

  //user input of the actual values
  for(int i = 0; i < numValues; i++)
  {
    cin >> values[i];
  }
  
  int length = sizeof(values) / sizeof(values[0]); //array length
  sort(values, values + length); //sorting array in asc order

  //keeps track of the starting number in ranges
  int temp = 0;
  vector <string> fixWhitespace;
  for(int i = 1; i < numValues; i++) //index position of array
  {
      //if number at position 1 and position 2 are consecutive
      int previousValue = values[i-1];
      if(values[i] != previousValue + 1)
      {
        int numOfRanges = i - 1 - temp;
        //if theres more than two ranges 
        if(numOfRanges >= 1){
        cout << to_string(values[temp]) + "-" + to_string(values[i-1]) + " ";
         temp = i; //setting the temp to current position
        }
        else{ //not continuous, print out single numbers
          cout << to_string(values[temp]) + " ";
          temp = i; //setting the temp to current position
        }
      }
    }

  int allValues = numValues - 1 - temp;
    //displays all of the ranges correctly
    if(allValues < 1){
      fixWhitespace.push_back(to_string(values[temp]));
      if(fixWhitespace.front() == to_string(values[temp])){
        cout<< to_string(values[temp])<<endl;
        }
      else{
        cout<<" " + to_string(values[temp])<<endl;
      }
    }
    else{
     fixWhitespace.push_back(to_string(values[temp]));
     if(fixWhitespace.front() == to_string(values[temp])){
       cout << to_string(values[temp]) + "-" + to_string(values[numValues - 1])<<endl;
      }
      else{
        cout<< " " + to_string(values[temp]) + "-" + to_string(values[numValues - 1]) <<endl;
      }
    }
    return 0;
  }
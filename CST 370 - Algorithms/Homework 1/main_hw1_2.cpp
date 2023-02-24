/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw1_2.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw1_2.cpp". Please DO NOT change
 *     the name of the main procecure "main()"
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw1_2.cpp
 * Abstract: This program allows the user to enter a word and check if it is a palindrome
              or not. It also checks the user's input to ignore any special characters and is 
              not case sensitive.
 * Name: Jennah Yasin
 * Date: November 1, 2022
 */
#include<bits/stdc++.h>
#include <iostream>
using namespace std;

//function that returns if an inputted string is a palindrome or not 
//boolean: true/false
bool checkPalindrome(string word){
    string noSpecialChar;
    //checks if every letter in string word is valid: no special characters
    //uses ASCII values of all alphabet and 1-9.
    for(int i = 0; i < word.length(); i++){
      if((word[i] < 48 || word[i] > 57) 
        && (word[i] < 97 || word[i] > 122)){
          //erases special characters if found and gets rid of space
          word.erase(i, 1);
          i--;
          //sets the new word string without special characters to word to new variable
          noSpecialChar = word;
      }
    }
    //is a palindrome if a word is the same written regular and backwards
    if(noSpecialChar == string(noSpecialChar.rbegin(), noSpecialChar.rend())
      && word == string(word.rbegin(), word.rend())){
      return true;
    }
  return false;
}
int main() {
  //holds users input of word in string variable
  string word;
  cin >> word;
  //converts users input to all lowercase letters
  transform(word.begin(), word.end(), word.begin(), ::tolower);
  //Print statements
  if(checkPalindrome(word) == true){
    cout<<"TRUE"<<endl;
  }
  else{
    cout<<"FALSE"<<endl;
  }
	return 0;
}

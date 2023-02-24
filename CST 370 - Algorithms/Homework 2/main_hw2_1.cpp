/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw2_1.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw2_1.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw2_1.cpp
 * Abstract: This program allows the user to input two timestamps in hh:mm:ss (24 hour system) format and then provides the time between those two timestamps.
 * Name: Jennah Yasin
 * Date: November 8, 2022
 */

#include <iostream>
using namespace std;

int main()
   {
     //variables that holds start and end timestamps
     string time1, time2;
     //variables to separate string into hh:mm:ss
     string hour1, min1, sec1, hour2, min2, sec2;

     //user inputs two timestamps
     cin>> time1>> time2;

     //use of substr function to separate the two timestamps
     //by selecting the position and length of each substring:
     //Start timestamp
     hour1 = time1.substr(0,2);
     min1 = time1.substr(3, 2);
     sec1 = time1.substr(6, 2);

     //End timestamp
     hour2 = time2.substr(0,2);
     min2 = time2.substr(3,2);
     sec2 = time2.substr(6,2);

     //converts all string substrings into integer values
     //to use for mathematical computions 
     //(stoi function = string to integer)
     int minutes1 = stoi(min1);
     int minutes2 = stoi(min2);
     int seconds2 = stoi(sec2);
     int seconds1 = stoi(sec1);
     int hours1 = stoi(hour1);
     int hours2 = stoi(hour2);
     //variables to hold the results of each calculation 
     //of final timestamp
     int secResult;
     int minResult;
     int hourResult;

     //if seconds of end time >= seconds of start time,
     //subtract regurally
     if(sec2 >= sec1){
       secResult = seconds2 - seconds1;
     }
     //otherwise, add 60 to ensure time format and then subtract, and subtract one from minutes for the "carry" part of subtraction
     else{
       secResult = (seconds2 + 60) - seconds1;
       minutes2--;
     }
     //minute calculations work the same as seconds, but
     //instead subtract one from hours.
     if(min2 >= min1){
       minResult = minutes2 - minutes1;
     }
     else{
       minResult = (minutes2 + 60) - minutes1;
       hours2--;
     }

     //if hours in end timestamp > hours in start, subtract
     //normally
     if(hour2 >= hour1){
       hourResult = hours2 - hours1;
     }
     //otherwise, subtract start from 24 first and then add
     //second timestamp to ensure it stays in 24 hour format
     else{
       hourResult = (24 - hours1) + hours2;
     }

     //checking if any of the results are single digits 
     //(less than 10). If it is, add a 0 before the single digit
     if(hourResult >= 10){
       cout<<to_string(hourResult) + ":";
       }
     else{
       cout<<"0" + to_string(hourResult) + ":";
     }
     
     if(minResult >= 10){
       cout<<to_string(minResult) + ":";
       }
     else{
       cout<<"0" + to_string(minResult) + ":";
     }
     
     if(secResult >= 10){
       cout<<to_string(secResult)<<endl;
       }
     else{
       cout<<"0" + to_string(secResult)<<endl;
     }
    return 0;
}


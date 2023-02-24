/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw5_2.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw5_2.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw5_2.cpp
 * Abstract: This program displays the execution times of how long the merge sort and quick sort algorithms take to sort an inputted size by the user. 
 * Name: Jennah Yasin
 * Date: December 4, 2022
 * Sources Used: 
    Merge Sort Algorithm: https://www.geeksforgeeks.org/merge-sort/
    Quick Sort Algorithm: https://www.geeksforgeeks.org/cpp-program-for-quicksort/
 */
#include <ctime>
#include <time.h>
#include <vector>
#include <iostream>
using namespace std;
//function for merge sort implementation
void merge(vector <int> &random1, int left, int middle, int right){
  auto const subArray1 = middle - left + 1;
  auto const subArray2 = right - middle;

  auto *leftArray = new int[subArray1], *rightArray = new int[subArray2];

  for(auto i = 0; i < subArray1; i++){
    leftArray[i] = random1[left + i];
    }
  for(auto j = 0; j < subArray2; j++){
    rightArray[j] = random1[middle+1+j];
  }
  auto indexOfSubArray1 = 0, indexOfSubArray2 = 0;

  int indexOfMergedArray = left;

  while(indexOfSubArray1 < subArray1 && indexOfSubArray2 < subArray2){
    if(leftArray[indexOfSubArray1] <= rightArray[indexOfSubArray2]){
      random1[indexOfMergedArray] = leftArray[indexOfSubArray1];
      indexOfSubArray1++;
    }
    else{
      random1[indexOfMergedArray] = rightArray[indexOfSubArray2];
      indexOfSubArray2++;
    }
    indexOfMergedArray++;
  }

  while(indexOfSubArray1 < subArray1){
    random1[indexOfMergedArray] = leftArray[indexOfSubArray1];
    indexOfSubArray1++;
    indexOfMergedArray++;
  }
  while(indexOfSubArray2 < subArray2){
    random1[indexOfMergedArray] = rightArray[indexOfSubArray2];
    indexOfSubArray2++;
    indexOfMergedArray++;
  }
}

//mergeSort implementation
void mergeSort(vector <int> &random, int left, int right){
  //int middle;
  if(left >= right){
    return;
  }
  auto middle = left + (right - left) / 2;
  mergeSort(random, left, middle);
  mergeSort(random, middle+1, right);
  merge(random, left, middle, right);
}

//helper function for quick sort implementation
int partition(vector<int> &random2, int start, int end){
  int pivot = random2[start];

  int count = 0;
  for(int i = start + 1; i <= end; i++){
    if(random2[i] <= pivot){
      count++;
    }
  }
  int pivotIndex = start + count;
  swap(random2[pivotIndex], random2[start]);

  int i = start, j = end;

  while(i < pivotIndex && j > pivotIndex){
    while(random2[i] <= pivot){
      i++;
    }
    while(random2[j] > pivot){
      j--;
    }
    if(i < pivotIndex && j > pivotIndex){
      swap(random2[i++], random2[j--]);
    }
  }
  return pivotIndex;
}

//function for quicksort implementation
void quickSort(vector<int> &random2, int start, int end){
  if(start >= end){
    return;
  }

  int partitioning = partition(random2, start, end);

  quickSort(random2, start, partitioning - 1);
  quickSort(random2, partitioning + 1, end);
}
int main()
{
  //asks user to input size of unsorted integers
  cout << "Enter Input Size: ";
  
  //holds size 
  int inputSize;
  cin >> inputSize;
  
  vector <int> random1; //vector of random integers for merge sort
  vector <int> random2; //vector of random integers for quick sort
  //generates random integers in vector
  for(int i = 1; i <= inputSize; i++){
    int randomVals = rand() % 999991;
    random1.push_back(randomVals);
  }
  //add same elements to vector 2
  for(int i = 0; i < random1.size(); i++){
    random2.push_back(random1[i]);
  }

  //***** EXECUTION TIME FOR MERGE SORT *****//
  //clock to track time for merge sort
  clock_t startClock1, stopClock1;
  double countTime1; 
  //starts the clock
  startClock1 = clock();
  //calls mergeSort function
  mergeSort(random1, 0, inputSize - 1);
  //stops the clock
  stopClock1 = clock();
  //calculates the time between start to end
  countTime1 = stopClock1 - startClock1;
  //holds actual elapsed time
  double elapsedTime1;
  //calculates elapsed time in seconds
  elapsedTime1 = ((double)countTime1)/CLOCKS_PER_SEC;
  //convert seconds to ms
  elapsedTime1 = elapsedTime1 * 1000;
  //displays execution time of merge sort algorithm
  cout << "========= Execution Time ==========" << endl;
  cout << "Merge sort: " << elapsedTime1 << " mlliseconds" << endl;

  //**** EXECUTION TIME FOR QUICK SORT *****//

  //clock to track execution time of quick sort algorithm
  clock_t startClock2, stopClock2;
  double countTime2;

  //starts the clock
  startClock2 = clock();
  //quick sort algorithm executes
  quickSort(random2, 0, inputSize - 1);
  //stop clock once sort is finished
  stopClock2 = clock();
  
  countTime2 = stopClock2 - startClock2;
  
  //calculate time between start and end 
  double elapsedTime2;
  //calculate actual execution time in seconds
  elapsedTime2 = ((double)countTime2)/CLOCKS_PER_SEC;
  //convert seconds to ms
  elapsedTime2 = elapsedTime2 * 1000;
  //display execution time of quick sort algorithm
  cout << "Quick sort: " << elapsedTime2 << " milliseconds" << endl;
  cout << "===================================";
  return 0;
}


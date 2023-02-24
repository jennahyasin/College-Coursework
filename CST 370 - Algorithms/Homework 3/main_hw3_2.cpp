/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw3_2.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw3_2.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw3_2.cpp
 * Abstract: This program allows the user to input graph information and implements the Travelling Salesman Problem(TSP) to find the path with the least cost. 
 * Name: Jennah Yasin
 * Date: November 15, 2022
 */
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <iostream>
using namespace std;

void readGraph(vector<vector<int>> & g){
  //graph info inputted by user: 

  //number of vertices in graph
  int numVertices;
  cin >> numVertices;

  //resize graph to inputted number of vertices
  g.resize(numVertices);

  //number of edges in graph
  int numEdges;
  cin>>numEdges;

  for(int i = 0; i <numVertices; i++){
      g[i].resize(numVertices);
  }
  
  int source, destination;
  int cost = 0;

  //adds edges between two vertices of graph
  for(int i = 0; i < numEdges; i++){
    cin >> source;
    cin >> destination;
    cin>> cost;

    //if a path exists between two vertices, set edge to cost value 
    g[source][destination] = cost;
  }  
}

 void tspProblem(vector<vector<int>> &g, int startingPoint){
  vector<int> holdVertices; //holds vertices that isn't the starting point
  vector<int> holdPathWeights; //holds all path weights calculated
  int noPaths = 135;
  vector <int> actualPath; //holds the minimum path weight
  int optimalPath = INT_MAX; 

   //holds all vertices besides starting point in vector
   for(int i = 0; i < g.size(); i++){
    if(i != startingPoint){
      holdVertices.push_back(i);
    }
  }

  //holds all vertices in new vector
  actualPath.assign(holdVertices.begin(), holdVertices.end());
   
  int j;
  do{
    //start at starting vertex
    j = startingPoint;
    //calculate weight
    int weight = 0;
    //traverse through all of the vertices
    for(int i = 0; i < holdVertices.size(); i++){
        //holds cost between two vertices
        int pathCost = g[j][holdVertices[i]];
        if(pathCost != 0){  //if cost is not 0, path exists
          weight += g[j][holdVertices[i]]; //add cost to weight variable
          j = holdVertices[i];//traverse to next index
        }
        else{ //no path found
          //set weight to highest possible int and break
          weight = INT_MAX;
          break;
      }
    }  
    //last point back to starting point
    if(weight < optimalPath){
      //adds weight between starting point and current index
      weight += g[j][startingPoint];
    }

    //adds all weight calculations to a vector
    holdPathWeights.push_back(weight);

    //update weight if found lower
    if(weight < optimalPath){
      //records the path of lowest cost
      actualPath.assign(holdVertices.begin(), holdVertices.end());
      //searches for smallest element in weight vector
      optimalPath = *min_element(holdPathWeights.begin(), holdPathWeights.end());
    }
    //find all permutations/combinations of vertices 
}while(next_permutation(holdVertices.begin(), holdVertices.end()));

  
//Print out path
if(optimalPath < INT_MAX && optimalPath != noPaths){
    cout<<"Path:" << startingPoint << "->";
    for(auto i : actualPath){
      cout<<i<<"->";
    }
  cout<<startingPoint<<endl<<"Cost:"<< optimalPath<<endl;
 }
    //no path exists case
   else{
         cout<<"Path:" <<endl<<"Cost:-1"<<endl;
   }
}

int main()
{
  //vector holding graphs info 
  vector<vector<int>> graph;
  
  //get graphs info from readGraph
  readGraph(graph);

  //get starting vertex value from user
  int startingVertex;
  cin >> startingVertex;

  //apply travelling salesman problem of given graph & starting point
  tspProblem(graph, startingVertex);
    
  return 0;
}


/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw3_3.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw3_3.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw3_3.cpp
 * Abstract: This program implements the DFS algorithm (recursively) of a graph (vertices/edges inputted by user). It displays the mark array of the solution to the DFS problem.
 * Name: Jennah Yasin
 * Date: November 15, 2022
 */
#include <stack>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
void readGraph(vector<vector<int>> &g){
  //user input of graph info:

  //number of vertices in graph
  int numOfVertices;
  cin >> numOfVertices;

  //resize graph vector to size of vertices
  g.resize(numOfVertices);


  //number of edges in graph
  int numOfEdges;
  cin>>numOfEdges;

  for(int i = 0; i < numOfVertices; i++){
      g[i].resize(numOfVertices);
  }
  
  int source, destination;

  //add edges between source and destination vertices 
  for(int i = 0; i < numOfEdges; i++){
    cin >> source;
    cin >> destination;
    g[source].push_back(destination);
    //if a path is found, set to 1
    g[source][destination] = 1;
  }
}

//recursive function
void dfs(vector<vector<int>> &g, vector<int> &markArray, int currentIndex, int &count){
  //increment the counter by 1
  count = count+1;
  //mark current/first index with count to mark off as visited 
  markArray[currentIndex] = count;
  //for all vertices in the graph 
  for(int i = 0; i < g.size(); i++){
    //if neighbor path exists AND these vertices have not been visited(marked) yet:
    if(g[currentIndex][i] == 1 && markArray[i] == 0){ 
      //recursive call to visit i until i >= g.size()
      dfs(g, markArray, i, count);
    }
  }
}

//DFS
vector<int> DFS(vector<vector<int>> &g, int startingVertex){
  vector<int> markArray(g.size(), 0); //vector for checking if visited or not
  int count = 0;
  for(int i = 0; i < g.size(); i++){ //goes through all vertices of the graph
    if(markArray[i] != 0){ //checks if current vertex is not 0 (visited)
      markArray[i] = 0; //initially sets all vertices as not visited 
    }
  }
    //call to recursive function
    dfs(g, markArray, startingVertex, count);
  
    return markArray;
}


int main()
{
  vector<vector<int>> graph;
  //call to read graph function to hold graph's info
  readGraph(graph);

  //starting vertex is always 0
  int startingPoint = 0;

  vector<int> mark; //vector that holds if a vertex has been marked/visited
  //run DFS function for graph at given startingPoint
  mark = DFS(graph, startingPoint);

  //Print stored marks of visited vertices
  for(int i = 0; i < graph.size(); i++){
    cout << "Mark[" << i << "]:"<<mark[i]<<endl;
  }
      return 0;
}


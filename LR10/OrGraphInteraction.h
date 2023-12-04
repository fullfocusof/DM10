#pragma once
#include <iostream>
#include <fstream>

#include <Windows.h>
#include <conio.h>
#include <cmath>

#include <vector>
#include <stack>

#define MAXV 1000

using namespace std;

enum classificatons 
{
	TREE = 1,
	BACK = -1,
	FORWARD = 2,
	CROSS = 0
};

class OrGraphInteraction
{
public:

	vector<vector<bool>> adjacencyM;
	int verts, edges;

	OrGraphInteraction();

	void printQuit();
	void Read_g();
	void Print_g();

	int edgeClass(int first, int second, vector<int>& parents, vector<int>& visited, vector<int>& entryTimes);

	void DFSComps(stack<int> st, vector<int>& comp, vector<bool>& status, int curVert);
	vector<vector<int>> FindCompsDFS();
};
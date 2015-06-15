//============================================================================
// Name        : Triangles.cpp
// Author      : Jake Kenealy
// Version     :
// Copyright   : ©
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {

	ifstream text("triangle.txt");
	if(text.is_open())
	{
		vector< vector<int > > tree; //will store a vector for each row of the triangle
		vector< int > values;		 //will temporarily store the numbers in a row, then feed it into the tree vector
		string line;
		int n;

		//This loop runs while there is another line of text to read
		//The line is then split into the individual numbers, which are pushed back onto the values vector
		//This vector is then pushed onto the trees vector, and then cleared to ready it for the next line
		while(getline(text, line))
		{
			istringstream iss(line);
			while(iss >> n)
				values.push_back(n);
			tree.push_back(values);
			values.clear();
		}


		//Starting from the bottom of the triangle, a max path up the tree is found
		//This is infinitely preferable to the top-down approach as it eliminates a huge number of sub-optimal sequences,
		//without having to manually compute the entirety of every path down
		int vectorindex=tree.size()-2; //Start at the second to last row of the triangle
		while(vectorindex>=0)
		{
			for (int entryindex=0;entryindex<=vectorindex;entryindex++)
			{
				//This compares the current entries two children for the max value and adds it to itself,
				//storing the value at the current entry
				//This way the maximum path down from any point can simply be read from the children values instead of computed repeatedly
				tree.at(vectorindex).at(entryindex)+= max( tree.at(vectorindex+1).at(entryindex), tree.at(vectorindex+1).at(entryindex+1));
			}
			vectorindex--;
		}

		cout << tree.at(0).at(0);
	}
	else
	{
		cout << "Failed to open file";
	}

	text.close();
}

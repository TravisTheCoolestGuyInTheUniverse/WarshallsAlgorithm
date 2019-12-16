/*
 ` Name: Travis Stop
 ` Date: 10/5/18
 ` Class: CSC2710
 ` Description: This program determines if a graph is connected or not by utilizing Warshalls algorithm.
 `
 ` to compile: g++ BuyOrSell.cpp -o FM.
 ` 
 ` to execute the program using I/O redirection where output goes to
 ` standard output: BOS 0<test.txt
 `
 ` if you want the output to go somewhere else, execute 
 ` this way: BOS 0< test.txt > output.txt
*/
#include <iostream>
#include <iomanip>

using namespace std;

//function prototypes
void load(int**&, int**&, string*&, int&, int&);
void testLoad(int**, int**, string*, int, int);
void warShalls(int**&, int);
bool isConnected(int**, int);

//driver function
int main()
{
	int n;
	cin >> n;
	//loads in collection and determines connectivity one at a time for n collections.
	for (int i=0; i<n; i++)
	{
		int** W;
		int** D;
		string* names;
		int m, numNames;
		load(W, D, names, numNames, m);
		//testLoad(W, D, names, numNames, m);
		warShalls(D, numNames);
		//testLoad(W, D, names, numNames, m);
		if (isConnected(D, numNames))
		cout << "connected" << endl;
	    else 
		cout << "disconnected" << endl;
	}
}

/* function: load() loads in data from a file using i/o redirection on a keyboard.
 ` 
 `  precondition: W and D are references to int**, names is a reference to a string pointer, 
 `  numNames and m are references to integers.
 ` 
 ` postcondition: W and D are dynamically allocated 2D integer arrays containing the direct
 ` connections between friends, (1 connected, 0 not connected). names contains the names 
 ` of all friends in the graph. numNames is the number of names in the graph. m is the number
 ` of direct connections there are in the graph.
*/
void load(int**& W, int**& D, string*& names, int& numNames, int& m)
{
	cin >> m;
	//alocate space for the maximum number of verticies possible for a given number of relationships
	W = new int*[2*m+1];
	D = new int*[2*m+1];
	//because this is the maximum number of unique names possible given m relationships. +1 because using 1 based array.
	names = new string[2*m+1];
	
	for (int i=1; i<m+1; i++)
	{
		W[i] = new int[m+1];
		D[i] = new int[m+1];
		for (int j=1; j<m+1; j++)
		{
			W[i][j] = 0;
			D[i][j] = 0;
		}
	}
	
	numNames = 0;
	string nameFrom, nameTo;
	for (int i=1; i<m+1; i++)
	{
		//input to nameTo twice to get rid of "friends".
		cin >> nameFrom >> nameTo >> nameTo;
		int nameFromIndex=0, nameToIndex=0;
		for (int i=1; i<numNames+1; i++)
		{
			if (names[i] == nameFrom)
			{
				nameFromIndex = i;
			}
			if (names[i] == nameTo)
			{
				nameToIndex = i;
			}
		}
		
		//case where both names are in the array
		if (nameToIndex != 0 && nameFromIndex != 0)
			{
				W[nameFromIndex][nameToIndex] = 1;
				D[nameFromIndex][nameToIndex] = 1;
				//case where neither name is in the array
				
			} else if (nameFromIndex == 0 && nameToIndex == 0)
			{
				numNames++;
				names[numNames] = nameFrom;
				numNames++;
				names[numNames] = nameTo;
				W[numNames-1][numNames] = 1;
				D[numNames-1][numNames] = 1;
				
				//case where nameTo is not in the array
			} else if (nameFromIndex != 0 && nameToIndex == 0)
			{
				numNames++;
				names[numNames] = nameTo;
				W[nameFromIndex][numNames] = 1;
				D[nameFromIndex][numNames] = 1;
				
				//case where nameFrom is not in the array
			} else if (nameToIndex != 0 && nameFromIndex == 0)
			{
				numNames++;
				names[numNames] = nameFrom;
				W[numNames][nameToIndex] = 1;
				D[numNames][nameToIndex] = 1;
			}
	}
}

/* function testLoad() - Prints data previously loaded to standard output.
 ` 
 ` precondtion:  W and D are dynamically allocated 2D integer arrays containing the direct
 ` connections between friends, (1 connected, 0 not connected). names contains the names 
 ` of all friends in the graph. numNames is the number of names in the graph. m is the number
 ` of direct connections there are in the graph.
 ` 
 ` postcondition: information stored in the arrays and other parameters are printed to standard output.
*/
void testLoad(int** W, int** D, string* names, int numNames, int m)
{
	cout << "**** W ****" << endl;
	for (int i=1; i<numNames+1; i++)
	{
		cout << endl;
		for (int j=1; j<numNames+1; j++)
		{
			cout << W[i][j] << " ";
		}
	}
	cout << endl << "**** D ****" << endl;
	for (int i=1; i<numNames+1; i++)
	{
		cout << endl;
		for (int j=1; j<numNames+1; j++)
		{
			cout << D[i][j] << " ";
		}
	}
	cout << endl << "**** names ****" << endl;
	for (int i=0; i<numNames+1; i++)
	{
		cout << names[i] << " ";
	}
	cout << endl << "numNames: " << numNames << endl << "m: " << m << endl;
}
/* function warShalls() - determines if there is a path between one vertex and another vertex on a graph. 
 `  
 ` precondtion: D is a populated dynamically allocated 2d array representing direct connections between
 ` verticies on a graph and n is the length/width of the array-1.
 ` 
 ` postcondition: D now contains information showing if there is a path between any two verticies on a graph. 
 ` n is unchanged.
*/
void warShalls(int**& D, int n)
{	
	for(int k=1; k<=n; k++)
	{
		for(int i=1; i<=n; i++)
		{
			for(int j =1; j <= n; j++)
			{
					if (i != j)
					D[i][j] = D[i][j]||(D[i][k] && D[k][j]);
			}
		}
	}
}

/* function isConnected() - determines if a graph is connected or disconnected. 
 ` 
 ` precondition: D is a 2d array containing information showing if there is a path between 
 ` any two verticies on a graph.
 ` postcondition: returns true if there is a path between all verticies, 
 ` false otherwise.
*/
bool isConnected(int** D, int n)
{
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			if (i != j && D[i][j] == 0)
				return false;
			
			return true;
}
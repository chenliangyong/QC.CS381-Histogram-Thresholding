#include <iostream> 
#include <fstream> 
#include <string>
#include <sstream>
using namespace std;
/*
--- Please use C++ 11 when you Compile in Venus  ---g++ -std=gnu++11 Threshold.cpp -o Threshold.out
*/

class BuildThreshold {
private:
	int **thr_Ary;	
	int numRows;	//image Head info
	int numCols;	//image Head info
	int minVal;	//image Head info
	int maxVal;	//image Head info
	int thr_Val;	// user input value
	string output;

public:
	BuildThreshold(char **File) {
		// loading the image data
		cout << "Start Reading Image..." << endl;
		HeadLoading(File[1]);

		//initialize thr_Ary;
		thr_Ary = new int*[numRows + 1];
		for (int i = 0; i < numRows + 1; i++) {
			thr_Ary[i] = new int[numCols + 1];
			for (int j = 0; j < numCols + 1; j++) {
				thr_Ary[i][j] = 0;
			}
		}

		// get the user input thr_val
		askUserInput();

		// generate output file
		fstream foutput;
		output = "thr_";
		stringstream s;
		s << thr_Val;
		output = output+s.str()+".txt";

		foutput.open(output, ios::out);
		foutput << numRows << " ";
		foutput << numCols << " ";
		foutput << minVal << " ";
		foutput << maxVal << endl;
		foutput.close();
	}

	void askUserInput() {
		while (true) {
			cout << "Please enter your threshold Value (" << minVal << "-" << maxVal << ") : ";
			cin >> thr_Val;
			if (thr_Val >= minVal && thr_Val <= maxVal) break;
			cout << "Input out of range!!!" << endl;
		}
	}

	void computeThreshold(string inFile) {
		fstream finput;
		finput.open(inFile);
		if (!finput.is_open()) {
			throw "Error ! Open Input File Failed, try again...";
		}

		string temp;
		int gVal = 0;
		if (!finput.eof()) {
			getline(finput, temp); // skip the image head
								   // cout << temp << endl;		
			for (int i = 1; i < numRows + 1; i++) {
				for (int j = 1; j < numCols + 1; j++) {
					if (!finput.eof() && finput.peek() != EOF) {
						finput >> gVal;
					}
					else { break; }
					cout << gVal << " ";
					if (gVal < thr_Val) {
						thr_Ary[i][j] = 0;
					}
					else {
						thr_Ary[i][j] = 1;
					}
				}
				cout << endl;
			}
		}
		else {
			finput.close();
			throw "Error ! Input File is empty, try again...";
		}
		finput.close();

		printThresholdArray();
		cout << "Finish Computation Threshold..." << endl;
	}


	void HeadLoading(string inFile) {
		fstream finput;
		finput.open(inFile);
		if (!finput.is_open()) {
			throw "Error ! Open Input File Failed, try again...";
		}
		if (!finput.eof() && finput.peek() != EOF) {
			finput >> numRows;
			finput >> numCols;
			finput >> minVal;
			finput >> maxVal;
		}
		else {
			finput.close();
			throw "Error ! Input File is empty, try again...";
		}
		finput.close();
		cout << "Image size is " << numRows << "x" << numCols << ", " << "Grey-Scale Range is " << minVal << "-" << maxVal << ";" << endl;
	}

	void printThresholdArray() {
		fstream foutput;
		foutput.open(output, ios::out|ios::app);
		for (int i = 1; i < numRows + 1; i++) {
			for (int j = 1; j < numCols + 1; j++) {
				cout << thr_Ary[i][j] << " ";
				foutput << thr_Ary[i][j] << " ";
			}
			cout << endl;
			foutput << endl;
		}
		foutput.close();
	}
};


int main(int argc, char *argv[])
{
	try {
		if (argc != 2) {
			cout << "Parameters missing... ( Run as : command <input file 1> ).";
			return 0;
		}
		BuildThreshold Threshold(argv);
		Threshold.computeThreshold(argv[1]);
	}
	catch (const char* msg) {
		cerr << msg << endl;
		return 0;
	}
	return 0;
};
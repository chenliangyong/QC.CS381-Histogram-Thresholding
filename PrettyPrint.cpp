#include <iostream> 
#include <fstream> 
#include <string>
#include <sstream>
using namespace std;
/*
--- Please use C++ 11 when you Compile in Venus  ---g++ -std=gnu++11 Threshold.cpp -o Threshold.out
*/

class PrettyPrint {
private:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	string output;

public:
	PrettyPrint(char **File) {
		// loading the image data
		cout << "Start Reading Image..." << endl;
		HeadLoading(File[1]);
		output = File[1];
		output = output + "_PP.txt";

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

	void prettyPrint(string inFile) {
		fstream finput;
		finput.open(inFile);
		if (!finput.is_open()) {
			throw "Error ! Open Input File Failed, try again...";
		}

		int gVal = 0;
		string temp;
		fstream foutput;
		foutput.open(output, ios::out | ios::app);
		if (!finput.eof()) {
			getline(finput, temp); // skip the image head
			for (int i = 1; i < numRows + 1; i++) {
				for (int j = 1; j < numCols + 1; j++) {
					if (!finput.eof() && finput.peek() != EOF) {
						finput >> gVal;
					}
					else { break; }
					if (gVal > 0) {
						cout << gVal << " ";
						foutput << gVal << " ";
					}
					else {
						cout << "  ";
						foutput << "  ";
					}
				}
				cout << endl;
				foutput << endl;
			}
		}
		finput.close();
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
		PrettyPrint PrettyPrint(argv);
		PrettyPrint.prettyPrint(argv[1]);
	}
	catch (const char* msg) {
		cerr << msg << endl;
		return 0;
	}
	return 0;
};
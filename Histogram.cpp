#include <iostream> 
#include <fstream> 
#include <string>
using namespace std;
/*
--- Please use C++ 11 when you Compile in Venus  ---g++ -std=gnu++11 Histogram.cpp -o histogram.out
*/

class BuildHistogram {
private:
	int *histogram;			// an 1-D array of image data
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	string outFile;

public:
	BuildHistogram(char **File) {
		outFile = File[2];

		// loading the image data
		cout << "Start Reading Image..." << endl;
		HeadLoading(File[1]);

		// initialize 1D Array
		histogram = new int[maxVal + 1];
		for (int i = 0; i < maxVal + 1; i++) {
			histogram[i] = 0;
		}

		computeHistogram(File[1]);
	}
	~BuildHistogram() {
		delete[] histogram;
	}

	void computeHistogram(string inFile) {
		fstream finput;
		finput.open(inFile);
		if (!finput.is_open()) {
			throw "Error ! Open Input File Failed, try again...";
		}

		string temp;
		int gVal=0;
		if (!finput.eof()) {
			getline(finput, temp); // skip the image head
			// cout << temp << endl;
			while (!finput.eof() && finput.peek() != EOF) {
				finput >> gVal;
				histogram[gVal]++;
			}
		}
		else {
			finput.close();
			throw "Error ! Input File is empty, try again...";
		}
		finput.close();
		cout << "Finish Computation Histogram." << endl;
	}


	void HeadLoading(string inFile) {
		fstream finput;
		finput.open(inFile);
		if (!finput.is_open()) {
			throw "Error ! Open Input File Failed, try again...";
		}
		if (!finput.eof() && finput.peek()!=EOF ) {
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

	void printHistogram() {
		fstream foutput;
		foutput.open(outFile, ios::out);
		cout << "Print Image Histogram:" << endl;
		for (int i = 0; i < maxVal + 1; i++) {
			cout << "("<< i << "):" << histogram[i] << " ";
			foutput << "(" << i << "):" << histogram[i] << " ";
			if (histogram[i] > 0) {
				int limit = histogram[i];
				if (limit > 80) {limit = 80;	}				
				for (int j = 0; j < limit; j++) {
					cout << "+";
					foutput << "+";
				}
				cout << endl;
				foutput << endl;
			}
			else {
				cout << endl;
				foutput << endl;
			}
		}
		foutput.close();
	}
};


int main(int argc, char *argv[])
{
	try {
		if (argc != 3) {
			cout << "Parameters missing... ( Run as : command <input file 1> <output file 1> ).";
			return 0;
		}
		BuildHistogram Histogram(argv);
		Histogram.printHistogram();
	}
	catch (const char* msg) {
		cerr << msg << endl;
		return 0;
	}
	return 0;
};
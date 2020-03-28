// main.cpp
// Tests all functionality of the class My_matrix class.

#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <numeric>
using namespace std; 
// this function computes the gcd between two values
unsigned int gcd(unsigned int n1, unsigned int n2) { 
	unsigned int tmp; //tmp is random variable placeholder
	while (n2 != 0) { //if second number is not 0
		tmp = n1; //tmp set to n1
		n1 = n2; //n1 is then set to n2
		n2 = tmp % n2; //n2 is n1 mod n2
	}
	return n1; //return n1
}
int main() {
	//import text file
	ifstream file("F4F4test.txt"); // test file to import
	int f1 = 4e6; //first frequency
	int f2 = 3e6; //second frequency
	string myArray[16][17]; //size of array for file size is arbitrary
	if (file.is_open()) //i = rows, j = columns
	{
		for (int i = 0; i < 16; i++) //runs 16 times 
		{ 
			for (int j = 0; j < 17; j++) //runs 17 times
			{
				file >> myArray[i][j]; //imports numbers from file into array
			//	cout << myArray[i][j] << " "; //displays contents
			}
		//	cout << "\n"; //new line
		}
	}

	cout << "Chopped Imported Table Values : \n";
	//chop off left side of table
	string newarray[16][16]; //new array with 1 shorter column
	for (int i = 0; i < 16; i++)
	{
		for (int j = 1; j < 17; j++)
		{
			newarray[i][j - 1] = myArray[i][j]; //chops off first column because unneccessary
			
			cout << newarray[i][j - 1] << " ";
		}
		cout << "\n";
	}
	//calculate values
	cout << "\n";//spacing
	cout << "\n";
	double w1 = 2 * M_PI*f1; //calculates w1
	double w2 = 2 * M_PI*f2; //calculates w2
	int gcd1 = gcd(f1, f2); //finds gcd between f1 and f2
	int phase = 0; //phase value 
	string dectoHex[16][16]; // matrix to get hex values
	cout << "Calculated Table: \n ";
	for (int i = 0; i < 16; i++) //iterates 16 times
	{
		for (int j = 0; j < 16; j++) //iterates 16 times
		{
			phase = i * 16 + j; // phase is calculated
			double sine1 = sin((phase*w1) / (256 * gcd1)); //calculates value for first sine wave
			double sine2 = sin((phase*w2) / (256 * gcd1)); //calculates value for second sine wave
			double div2 = 63.0 / (double) 2.0; // 63 is bitsize  2 is to normalize amplitude
			double beforeround = div2*(sine1 + sine2);  // calculates actual value
			//cout << beforeround << " ";
			int roundedans = round(beforeround); // round value
			if (roundedans < 0) //if value is negative
			{
				roundedans = roundedans + 128; // add 128 
			}
			char hexString[20]; //placeholder for hex value
			_itoa_s(roundedans, hexString, 16); //convert dec to hex
			string sub = hexString; //put char value into string
			for (int a = 0; a <= sub.length();a++) //this loop looks through the string and converts lower case letters to uppercase
			{
				if (sub[a] >= 97 && sub[a] <= 122)
				{
					sub[a] = sub[a] - 32;
				}
			}
			dectoHex[i][j] = sub; // value is stored into dectoHex
			cout << dectoHex[i][j] << " "; //display value
		}
		cout << "\n"; 
	}
	cout << "\n";//spacing
	cout << "\n";//spacing
	int error = 0; // error indexer
	for (int i = 0; i < 16; i++) //runs 16 times
	{
		for (int j = 0; j < 16; j++) //runs 16 times
		{
			if (newarray[i][j].compare(dectoHex[i][j]) != 0) //if imported array is not equal to computed values
			{
				error += 1; //error indexes
				cout << newarray[i][j] << " " << dectoHex[i][j] << "\n"; //display wrong values
			}
		}
	}
	if (error == 0) //if no errors
	{
		cout << "NO ERRORS \n"; //display
	}
	else
	{
		cout << "there are " << error << " errors \n"; //else display
	} 
	system("pause");
	
}

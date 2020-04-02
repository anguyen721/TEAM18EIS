
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <functional>
#include <algorithm>

// TODO: reference additional headers your program requires here
#include <iostream>
#include <fftw3.h>
// macros for the real and imaginary parts
#define REAL 0
#define IMAG 1
#define N 8000	
// length of the complex arrays
using namespace std;
/* Computes the 1-D fast Fourier transform. */
void fft(fftw_complex *in, fftw_complex *out)
{
	// create a DFT plan
	fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	// execute the plan
	fftw_execute(plan);
	// do some cleaning
	fftw_destroy_plan(plan);
	fftw_cleanup();
}

/* Computes the 1-D inverse fast Fourier transform. */
void ifft(fftw_complex *in, fftw_complex *out)
{
	// create an IDFT plan
	fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
	// execute the plan
	fftw_execute(plan);
	// do some cleaning
	fftw_destroy_plan(plan);
	fftw_cleanup();
	// scale the output to obtain the exact inverse
	for (int i = 0; i < N; ++i) {
		out[i][REAL] /= N;
		out[i][IMAG] /= N;
	}
}
void digitalfiltering(string name)
{

	ifstream myfile(name);
	vector<string> outputfiltering;
	string line;
	vector<string> out_left;
	vector<string> out_right;


	while (getline(myfile, line)) {
		outputfiltering.push_back(line);
	}
	myfile.close();
	int size = 0;
	string targ_ln;
	for (int i = 0; i <= outputfiltering.size() - 1; i++) {
		targ_ln = outputfiltering[i];
		out_left.push_back(targ_ln.substr(0, targ_ln.find(' ')));
		out_right.push_back(targ_ln.substr(targ_ln.find(' ') + 1));

	}
	double base;
	int exp;
	vector<unsigned int> freqs;
	vector <double>mags;

	for (int i = 1; i <= outputfiltering.size() - 1; i++) {
		if (out_left[i].find('e') != std::string::npos) {
			base = stod(out_left[i].substr(0, out_left[i].find('e')));
			exp = stoi(out_left[i].substr(out_left[i].find('+') + 1));
			freqs.push_back(base * pow(10, exp));
		}
		else {
			freqs.push_back(stoi(out_left[i]));
		}
		mags.push_back(stod(out_right[i]));
	}
	vector <double>mags_copy;

	for (int i = 0; i <= outputfiltering.size() - 2; i++) {
		if (freqs[i] > 100000 && freqs[i] < 10000000) {
			mags_copy.push_back(mags[i]);
		}
		else {
			mags_copy.push_back(0);
		}
	}
	sort(mags_copy.begin(), mags_copy.end(), greater<double>());
	double sec_max = mags_copy[1];

	for (int i = 0; i <= outputfiltering.size() - 2; i++) {
		if ((freqs[i] < 100000) || (freqs[i] > 10000000) || (mags[i] < sec_max)) {
			mags[i] = 0;
		}
	}

	ofstream filtered_output;
	filtered_output.open("filtered_output.txt");
	for (int i = 0; i <= outputfiltering.size() - 2; i++) {
		filtered_output << to_string(freqs[i]) << ' ' << to_string(mags[i]);
		if (i != outputfiltering.size() - 2)
		{
			filtered_output << endl;
		}
	}
	filtered_output.close();
}
/* Displays complex numbers in the form a +/- bi. */
void displayComplex(fftw_complex *y)
{
	ofstream myfile;
	myfile.open("displaycomplex.txt");
	for (int i = 0; i < N; ++i)
		if (y[i][IMAG] < 0)
		{
			myfile << y[i][REAL] << " - " << abs(y[i][IMAG]) << "i" << endl;
			//cout << y[i][REAL] << " - " << abs(y[i][IMAG]) << "i" << endl;
		}
		else
		{
			myfile << y[i][REAL] << " + " << y[i][IMAG] << "i" << endl;
		//	cout << y[i][REAL] << " + " << y[i][IMAG] << "i" << endl;
		}
	myfile.close();

}


/* Displays the real parts of complex numbers. */
void displayReal(fftw_complex *y)
{
	for (int i = 0; i < N; ++i)
		cout << y[i][REAL] << endl;
}

int main()
{
	// READING IN FILE AND STORING DATA INTO VECTORS
	//
	//
	string timevar, inputvar, outputvar; //variables from file are here
	vector<float>time; //time component of fft
	vector<double>input; //input wave
	vector<double>output; //output wave

	//input filename
	string file = "23500R16pf.txt";
	int count = 0;

	ifstream coeff(file); //opening the file.
	if (coeff.is_open()) //if the file is open
	{
		//ignore first line
		string line;
		getline(coeff, line);

		while (!coeff.eof()) //while the end of file is NOT reached
		{
			//storing text values into respective categories
			getline(coeff, timevar, '\t');
			time.push_back(stof(timevar));
			getline(coeff, inputvar, '\t');
			input.push_back(stof(inputvar));
			getline(coeff, outputvar, '\n');
			output.push_back(stof(outputvar));
			count += 1; //increment number of lines
		}
		//cout << count;
		coeff.close(); //closing the file
	}
	else cout << "Unable to open file"; //if the file is not open output

	//COMPUTING FFT
	// input array
	fftw_complex inputwave[N];
	// output array
	fftw_complex inputwavefinal[N];
	// input array
	fftw_complex outputwave[N];
	// output array
	fftw_complex outputwavefinal[N];
	// fill the array with input and output vector values
		for (int i = 0; i < N; ++i) {
		inputwave[i][REAL] = input.at(i);		// i.e., { 1, 2, 3, 4, 5, 6, 7, 8 }
		inputwave[i][IMAG] = 0;
		outputwave[i][REAL] = output.at(i);		// i.e., { 1, 2, 3, 4, 5, 6, 7, 8 }
		outputwave[i][IMAG] = 0;
	}
	// compute the FFT 
	fft(inputwave, inputwavefinal);
	fft(outputwave, outputwavefinal);
	vector <double> inputwavefinalmag;
	vector <double> outputwavefinalmag;

	//calculating from complex to magintide
	for (int i = 0; i < N; ++i)
	{
		inputwavefinalmag.push_back(sqrt(pow(inputwavefinal[i][REAL], 2) + pow(abs(inputwavefinal[i][IMAG]), 2)));
		outputwavefinalmag.push_back(sqrt(pow(outputwavefinal[i][REAL], 2) + pow(abs(outputwavefinal[i][IMAG]), 2)));

	}
	//END OF FFT
	//CALCULATING SINGLE SIDED SPECTRUM
	double Fs = count/.0001; //sampling frequency
	double T = 1 / Fs; // Period
	double f = 1000000;
	double t[N]; //time vector
	double ff[N]; //frequency step vector
	for (int i = 0; i< N; i++) //calculating frequency step
	{
		t[i] = i*T;
		ff[i] = Fs*i / N;
	}


	ofstream inputoutput;
	ofstream outputoutput;
	//CREATING FILES FOR DIGITAL FILTERING
	inputoutput.open("inputplot.txt");
	outputoutput.open("outplot.txt");
	inputoutput << "input" << endl;
	outputoutput << "output" << endl;
	for (int i = 0; i < N; ++i)
	{

		inputoutput << ff[i] << " " << inputwavefinalmag[i] << endl;
		outputoutput << ff[i] << " " << outputwavefinalmag[i] << endl;

	}
	inputoutput.close();
	outputoutput.close();
	//digital filtering
	digitalfiltering("inputplot.txt");
	//Seperating frequency from magnitude
	string file2 = "filtered_output.txt";
	string freqvar;
	string magvar;
	vector<int> frequencyfiltered;
	vector<double> magfiltered;
	ifstream coeff2(file2); //opening the file.
	if (coeff2.is_open()) //if the file is open
	{
		while (!coeff2.eof()) //while the end of file is NOT reached
		{
			
			getline(coeff2, freqvar, ' ');
			frequencyfiltered.push_back(stoi(freqvar));
			getline(coeff2, magvar, '\n');
			magfiltered.push_back(stod(magvar));
		}
		coeff2.close(); //closing the file
	}
	else cout << "Unable to open file"; //if the file is not open output
	double max1 = 0; //first spike in fft
	double max2 = 0; //second spike in fft
	int freq1 = 0; //first frequency spike
	int freq2 = 0; //second frequency spike
	int maxcount = 0;
	for (int i = 0; i < magfiltered.size(); i++) //this loop finds the two non zero spikes in the filtered fft and stores the frequency and magnitude
	{
		if (magfiltered[i] != 0)
		{
			if (maxcount == 0)
			{
				max1 = magfiltered[i];
				freq1 = frequencyfiltered[i];
				maxcount++;
			}
			else
			{
				max2 = magfiltered[i];
				freq2 = frequencyfiltered[i];
				break;
			}
		}
	}
	cout << freq1 << " " << max1 << endl;
	cout << freq2 << " " << max2 << endl;
	//digital filtering output
	digitalfiltering("outplot.txt");

	string file3 = "filtered_output.txt";
	string freqvar2;
	string magvar2;
	vector<int> frequencyfiltered2;
	vector<double> magfiltered2;
	ifstream coeff3(file3); //opening the file.
	if (coeff3.is_open()) //if the file is open
	{
		while (!coeff3.eof()) //stores data in respective vectors
		{

			getline(coeff3, freqvar2, ' ');
			frequencyfiltered2.push_back(stoi(freqvar2));
			getline(coeff3, magvar2, '\n');
			magfiltered2.push_back(stod(magvar2));
		}
		coeff3.close(); //closing the file
	}
	else cout << "Unable to open file"; //if the file is not open output

	double max11 = 0; //spike value 1
	double max22 = 0; // fft spike value 2
	int freq11 = 0; //frequency spike 1
	int freq22 = 0; //frequency spike 2
	int maxcount2 = 0;
	for (int i = 0; i < magfiltered2.size(); i++) //finds the two nonzero spikes in filtered frequency and stores them into respective variables
	{
		if (magfiltered2[i] != 0)
		{
			if (maxcount2 == 0)
			{
				max11 = magfiltered2[i];
				freq11 = frequencyfiltered2[i];
				maxcount2++;
			}
			else
			{
				max22 = magfiltered2[i];
				freq22 = frequencyfiltered2[i];
				break;
			}
		}
	}
	cout << freq11 << " " << max11 << endl;
	cout << freq22 << " " << max22 << endl;
	ofstream finalresults;
	//FINAL IMPEDANCE CALCULATIONS VIN/VOUT*100
	double calc1modified=0;
	double calc2modified = 0;
	finalresults.open("finalresults.txt");
	double calc1 = 0; //FREQUENCY 1 CALC
	double calc2 = 0; //FREQUENCY 2 CALC
	if (freq11 == freq1)
	{
		calc1 = (max1 / max11) * 100;
		calc1modified = (calc1) / (1 + (freq1/ (pow(10,7))));
		cout << freq1 << " : " << calc1 << endl;
		finalresults << freq1 << " " << calc1 << endl;
	}
    if (freq22 == freq2 )
	{
		calc2 = (max2 / max22) * 100;
		cout << freq2 << " : " << calc2 << endl;
		calc2modified = (calc2) / (1 + (freq2 / (pow(10, 7))));
		finalresults << freq2 << " " << calc2 << endl;
	}
	if (freq22 == freq1)
	{
		calc1 = (max1 / max22) * 100;
		calc1modified=  calc1/ (1 + (freq1 / (pow(10, 7))));
		cout << freq1 << " : " << calc1 << endl;
		finalresults << freq1 << " " << calc1 << endl;
		calc2 = (max2 / max11) * 100;
		calc2modified = calc2 / (1 + (freq2 / (pow(10, 7))));
		cout << freq2 << " : " << calc2 << endl;
		finalresults << freq1 << " " << calc2 << endl;
	}
	cout << freq1 << " : " << calc1modified << endl;

	cout << freq2 << " : " << calc2modified << endl;

	system("pause");
    return 0;
}


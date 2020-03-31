#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <functional>

using namespace std;

int main() {


	ifstream myfile("/Users/tracy/CLionProjects/untitled/outplot.txt");
	vector<string> output;
	string line;
	vector<string> out_left;
	vector<string> out_right;


	while (getline(myfile, line)) {
		output.push_back(line);
	}
	myfile.close();
	int size = 0;
	string targ_ln;
	for (int i = 0; i <= output.size() - 1; i++) {
		targ_ln = output[i];
		out_left.push_back(targ_ln.substr(0, targ_ln.find(' ')));
		out_right.push_back(targ_ln.substr(targ_ln.find(' ') + 1));

	}
	double base;
	int exp;
	vector<unsigned int> freqs;
	vector <double>mags;

	for (int i = 1; i <= output.size() - 1; i++) {
		if (out_left[i].find('e') != std::string::npos) {
			base = stod(out_left[i].substr(0, out_left[i].find('e')));
			exp = stoi(out_left[i].substr(out_left[i].find('+') + 1));
			freqs.push_back ( base * pow(10, exp));
		}
		else {
			freqs.push_back(stoi(out_left[i]));
		}
		mags.push_back(stod(out_right[i]));
	}
	//double mags_copy[output.size() - 1];
	vector <double>mags_copy;

	for (int i = 0; i <= output.size() - 2; i++) {
		if (freqs[i] > 100000 && freqs[i] < 10000000) {
			mags_copy.push_back(mags[i]);
		}
		else {
			mags_copy.push_back( 0);
		}
	}
	sort(mags_copy.begin(), mags_copy.end() + output.size() - 1, greater<double>());
	double sec_max = mags_copy[1];

	for (int i = 0; i <= output.size() - 2; i++) {
		if ((freqs[i] < 100000) || (freqs[i] > 10000000) || (mags[i] < sec_max)) {
			mags[i] = 0;
		}
	}

	ofstream filtered_output;
	filtered_output.open("/Users/tracy/CLionProjects/untitled/filtered_output.txt");
	for (int i = 0; i <= output.size() - 2; i++) {
		filtered_output << to_string(freqs[i]) << ' ' << to_string(mags[i]) << endl;
	}
	filtered_output.close();
	return 0;
}


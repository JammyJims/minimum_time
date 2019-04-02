#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
string minimum_time(int A, int B, int C, int D, int E, int F) {
	string impossible = "NOT_POSSIBLE";
	vector<int> vec = {A, B, C, D, E, F};
	vector<int> low;
	vector<int> high;
	for (int i : vec) {
		if (i >= 0 && i < 6) low.push_back(i);
		if (i > 6) high.push_back(i);
	}

	// sort high and low from highest values to lowest values
	sort(low.begin(), low.end(), greater<>());
	sort(high.begin(), high.end(), greater<>());

	// declare container to place HH:MM:SS into
	vector<int> arr = {-1, -1, -1, -1, -1, -1};

	// handling the higher values
	// the higher numbers can only go into indices 5, 3, 1
	if (high.size() > 3) return impossible;
	int index = 5;
	for (int i : high) {
		arr[index] = i;
		index = index - 2;
	}

	// handling the rest of the values
	// lower values can go anywhere in arr with the exception of index 0
	index = 5;
	for (int i : low) {
		while (arr[index] != -1) index--; // moves the index to the next untouched spot
		if (index != 0) arr[index] = i; // index 0 is the exception
		else {
			// index at 0
			if (i > 1) return impossible;
			if (i == 2 && arr[index+1] >= 4) return impossible; // cannot have hours greater than equal to 24
			arr[index] = i;
		}
	}

	// final check of arr, all spots should be taken up
	for (int i : arr) if (i < 0) return impossible;

	// prep return string and return results
	string text = "";
  text += to_string(arr.at(0));
  text += to_string(arr.at(1));
  text += ":";
  text += to_string(arr.at(2));
  text += to_string(arr.at(3));
  text += ":";
  text += to_string(arr.at(4));
  text += to_string(arr.at(5));
	return text;
}

int main(int argc, char *argv[]) {
	if (argc != 7) {
		cout << "invalid number of arguments, requires 6" << endl;
		return -1;
	}
	int A = stoi(argv[1]);
  int B = stoi(argv[2]);
  int C = stoi(argv[3]);
  int D = stoi(argv[4]);
  int E = stoi(argv[5]);
  int F = stoi(argv[6]);
	string results = minimum_time(A,B,C,D,E,F);
	cout << results << endl;
	return 0;
}

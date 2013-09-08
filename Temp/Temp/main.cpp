#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

void print(vector<int> &ar) {
	for (unsigned int i = 0; i < ar.size(); i++)
		cout << ar[i] << " ";
	cout << endl;
}

/* Head ends here */
void insertionSort(vector<int>  ar) {
	// initializing iterator
	int it = ar.size()-1;

	// saving number to be sorted
	int v = ar[it];

	it--;
	if (it < 0)
		return;

	bool done = false;
	while (!done) {
		// shift cell to the right
		if (ar[it] > v) {
			ar[it+1] = ar[it];
			if (it == 0)
				ar[it] = v;
		}
		else {
			ar[it+1] = v;
			done = true;
		}

		it--;
		if (it < 0)
			done = true;

		print(ar);
	}
}

/* Tail starts here */
int main(void) {
	vector<int>  _ar;
	int _ar_size;

	cin >> _ar_size; cin.ignore();
	for(int _ar_i = 0; _ar_i < _ar_size; _ar_i++) {
		int _ar_tmp;
		cin >> _ar_tmp;
		_ar.push_back(_ar_tmp); 
	}
	 cin.ignore();
	insertionSort(_ar);
	cin.get();

	return 0;
}
#include<iostream>
#include<vector>

using namespace std;

class Sort {
public:
	void mergeSort(vector<double>& vecToSort);
private:
	void swapVec(vector<double>& vec);
	bool mergeTwoSortedVectors(vector<double>& vecA, vector<double>& vecB, vector<double>& vecC);
};

void Sort::swapVec(vector<double>& vec) {
	vec.push_back(vec.at(0));
	vec.at(0) = vec.at(1);
	vec.at(1) = vec.at(2);
	vec.pop_back();
}

bool Sort::mergeTwoSortedVectors (vector<double>& vecA, vector<double>& vecB, vector<double>& vecC) {
	int countA = 0, countB = 0, countC = 0;
	
	for (int i = 1; i < vecA.size(); i++) {
			if (vecA.at(i) < vecA.at(i - 1)) {
				return false;
			}
	}

	for (int i = 1; i < vecB.size(); i++) {
			if (vecB.at(i) < vecB.at(i - 1)) {
				return false;
			}
	}											// end of check

	while (countA < vecA.size() && countB < vecB.size()) {
		if (vecA.at(countA) < vecB.at(countB)) {
			vecC.at(countC) = vecA.at(countA);
			countC++;
			countA++;
		}
		else {
			vecC.at(countC) = vecB.at(countB);
			countC++;
			countB++;
		}
	}

	while (countA < vecA.size()) {
		vecC.at(countC) = vecA.at(countA);
		countC++;
		countA++;
	}

	while (countB < vecB.size()) {
		vecC.at(countC) = vecB.at(countB);
		countC++;
		countB++;
	}

	return true;
}

void Sort::mergeSort (vector<double>& vecToSort) {
	if (vecToSort.size() < 2) {
		return;
	}
	else if (vecToSort.size() == 2) {
		
		if (vecToSort.at(0) > vecToSort.at(1)) {
			swapVec(vecToSort);
		}

		return;
	}

	vector<double>vec1(vecToSort.size() / 2);									// sub-vector 1
	vector<double>vec2(vecToSort.size() - (vecToSort.size() / 2));				// sub-vector 2
	int i, p;
	bool accurate = true;

	for (i = 0; i < (vecToSort.size() / 2); i++) {
		vec1.at(i) = vecToSort.at(i);
	}

	for (i = (vecToSort.size() / 2), p = 0; i < vecToSort.size() && p < vec2.size(); i++, p++) {

		vec2.at(p) = vecToSort.at(i);
	}

	mergeSort(vec1);				// recursion call 1
	mergeSort(vec2);				// recursion call 1

	accurate = mergeTwoSortedVectors(vec1, vec2, vecToSort);

	if (accurate == false) {			// outputs warning if problem in mergeTwoSortedVectors function
		char Bell = '%' - 30;
		cout << endl << Bell << "Error! Execution of mergeTwoSortedVectors function sent incorrectly sorted vector(s) to mergeSort function.";
		cout << endl << "- Statement about the numbers being sorted below is possibly incorrect." << endl << endl;
	}
}

int main() {
	vector<double> vecA;
	int vecSize = 0, incorrect = 0;
	Sort sorter;

	cout << "This is a vector sorting program. Please enter a non-negative integer for the size of the vector: ";
	cin >> vecSize;

	while (vecSize < 1) {
		incorrect++;
		if (incorrect == 8) {
			char bell = '%' - 30;
			cout << endl << "Too many incorrect entries. Program will now end. " << bell << system("pause");
			return 0;
		}
		else {
			cout << endl << "Invalid input. Please enter a non-negative integer for the size of the vector: ";
			cin >> vecSize;
		}
	}

	vecA.resize(vecSize);

	for (int i = 0; i < vecSize; i++) {
		cout << endl << "Enter number for position " << (i + 1) << ": ";
		cin >> vecA.at(i);
	}

	cout << endl << endl << "Your original Vector: (";
	for (int i = 0; i < vecA.size(); i++) {
		cout << vecA.at(i);

		if (i < (vecA.size() - 1)) {
			cout << ", ";
		}
	}
	cout << ')' << endl << endl;

	sorter.mergeSort(vecA);							// call	

	cout << "Your vector with the numbers re-ordered least to greatest: (";
	for (int i = 0; i < vecA.size(); i++) {
		cout << vecA.at(i);

		if (i < (vecA.size() - 1)) {
			cout << ", ";
		}
	}
	cout << ')' << endl << endl << endl;

	system("pause");
	return 0;
}
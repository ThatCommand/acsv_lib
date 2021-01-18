#include "pch.h"
#include "Utils.h"
#include <iostream>

namespace Utils {
	int Functions::compare(std::string *s1, std::string *s2) {
		int res = 0;
		int l1 = s1->length();
		int l2 = s2->length();
		const char *cs1 = s1->c_str();
		const char *cs2 = s2->c_str();
		for (int i = 0; i < (l1 < l2 ? l1 : l2); i++) {
			if (cs1[i] < cs2[i]) {
				res = -1;
				break;
			}
			else if (cs1[i] > cs2[i]) {
				res = 1;
				break;
			}
		}
		if (!res) {
			res = (l1 < l2) ? -1 : (l1 > l2 ? 1 : 0);
		}
		return res;
	}

	NewIndexes* Functions::sortStringArray(std::string* arr[], int dim,bool desc) {
		NewIndexes* ni = new NewIndexes;
		ni->dim = dim;
		ni->indexes = new int[dim];
		for (int i = 0; i < dim; i++) {
			ni->indexes[i] = i;
		}
		for (int i = 0; i < dim; i++) {
			int swaps = 0;         //flag to detect any swap is there or not
			for (int j = 0; j < dim - i - 1; j++) {
				if (compare(arr[j], arr[j+1]) == (desc ? -1 : 1)) {       //when the current item is bigger than next
					std::string* temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
					int t = ni->indexes[j];
					ni->indexes[j] = ni->indexes[j+1];
					ni->indexes[j+1] = t;
					swaps = 1;    //set swap flag
				}
			}
			if (!swaps)
				break;       // No swap in this pass, so array is sorted
		}
		return ni;
	}

	int Functions::binarySearch(std::string* arr[], int p, int r, std::string* str) {
		if (p <= r) {
			int mid = (p + r) / 2;
			if (compare(arr[mid],str) == 0)
				return mid;
			if (compare(arr[mid], str) == 1)
				return binarySearch(arr, p, mid - 1, str);
			if (compare(arr[mid], str) == -1)
				return binarySearch(arr, mid + 1, r, str);
		}
		return -1;
	}
}
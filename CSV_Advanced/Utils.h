#pragma once
#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED
#ifndef DllExport
#define DllExport  __declspec( dllexport )
#endif // !DllExport

#include "string"
namespace Utils {

	typedef struct NewIndexes {
		int* indexes;
		int dim;
	};

	class DllExport Functions {
	public:
		int compare(std::string *s1, std::string *s2);
		NewIndexes* sortStringArray(std::string* arr[], int dim, bool desc);
		int binarySearch(std::string* arr[], int p, int r, std::string* str);
	};
}
#endif // !UTILS_INCLUDED

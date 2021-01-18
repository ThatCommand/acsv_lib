#pragma once
#define DATAITERATOR_INCLUDED

#define MAX_COLUMNS 100
#ifndef MAX_ROWS
#define MAX_ROWS 100000
#endif // !MAX_ROWS

#ifndef FILEREADER_INCLUDED
	#include "FileReader.h"
#endif 

namespace Data {

	typedef struct StringMatrix{
		std::string values[MAX_COLUMNS][MAX_ROWS];
	};

	typedef struct SortedStringMatrix {
		std::string* values[MAX_COLUMNS][MAX_ROWS];
	};

	typedef struct DataPos {
		int row;
		int column;
	};

	class DllExport DataIterator
	{
	private:
		std::string columns[MAX_COLUMNS];
		int read_columns = 0;
		int read_rows = 0;

		int max_length_column[MAX_COLUMNS];

		StringMatrix values;
		SortedStringMatrix sorted_values;

		bool sorted = false;
		int sorted_column = -1;

		std::string data;
		char curr_separator; 
		Reader::FileReader source;

	public:
		DataIterator(std::string path_to_file,char separator);
		bool parseData(Reader::FileReader fr);
		bool parseData();
		bool writeOut();

		StringMatrix* getData();
		SortedStringMatrix* getSortedData();

		std::string* getColumnsHeader();
		int getShowColumnSize(int column);
		int getColumnSize();
		int getRowSize();

		void sortCSV(int column);
		bool isSorted();
		int sortedColumn();

		DataPos getPosOf(std::string val, int column);
		std::string* getStringAt(DataPos pos);

		void printInfo();
		void printTable(int max, int page);
		void printRow(bool columns_headers, int row);
	};
}


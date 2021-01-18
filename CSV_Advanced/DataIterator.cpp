#include "pch.h"

#ifndef DATAITERATOR_INCLUDED
	#include "DataIterator.h"
#endif
#include "Utils.h"

namespace Data {

	DataIterator::DataIterator(std::string path_to_file,char separator) {
		curr_separator = separator;
		source.setPath(path_to_file);
		bool read = source.readFile();
		if (!read) {
			throw std::invalid_argument("File could not be read.");
		}
	}

	bool DataIterator::parseData() {
		return parseData(source);
	}

	bool DataIterator::parseData(Reader::FileReader fr) {
		if (fr.isLoaded() && fr.isOpened()) {
			bool first_line = true;
			int current_column = 0;
			std::string dt = fr.getData();
			std::string current_dt = "";
			bool enter_or_end;
			for (int i = 0; i < dt.length(); i++) {
				enter_or_end = dt[i] == (int)'\n' || i == dt.length() - 1;
				if (dt[i] == (int)curr_separator || enter_or_end) {
					if (first_line) {
						columns[current_column] = current_dt;
						read_columns++;
						first_line = !enter_or_end;
					} else {
						values.values[current_column][read_rows] = current_dt;
						sorted_values.values[current_column][read_rows] = &values.values[current_column][read_rows];
						read_rows += enter_or_end&&current_column>0;
					}
					max_length_column[current_column] = max_length_column[current_column] < current_dt.length() ?  current_dt.length() : max_length_column[current_column];
					current_column = enter_or_end ? 0 : ++current_column;
					current_dt = "";
				} else {
					current_dt += dt[i];
				}
			}
			return true;
		}
		return false;
	}

	bool DataIterator::writeOut() {
		std::string dt="";
		for (int i = 0; i < read_columns; i++) {
			dt += columns[i];
			if (i + 1 < read_columns) {
				dt += curr_separator;
			}
		}
		dt += "\n";
		for (int i = 0; i < read_rows; i++) {
			for (int y = 0; y < read_columns; y++) {
				dt += *sorted_values.values[y][i];
				if (y + 1 < read_columns) {
					dt += curr_separator;
				} else {
					if (i + 1 < read_rows) {
						dt += "\n";
					}
				}
			}
		}
		std::fstream output;
		output.open(source.getPath(), std::ios::out | std::ios::trunc);
		if (output){
			output << dt;
			output.close();
			return true;
		}
		return false;
	}

	std::string* DataIterator::getColumnsHeader() {
		return columns;
	}

	StringMatrix* DataIterator::getData() {
		return &values;
	}

	SortedStringMatrix* DataIterator::getSortedData() {
		return &sorted_values;
	}

	int DataIterator::getColumnSize() {
		return read_columns;
	}

	int DataIterator::getRowSize() {
		return read_rows;
	}

	int DataIterator::getShowColumnSize(int column) {
		return max_length_column[column];
	}

	DataPos DataIterator::getPosOf(std::string val,int column) {
		DataPos dp;
		dp.column = column;
		if (sorted_column != column) {
			sortCSV(column);
		}
		Utils::Functions* f = new Utils::Functions;
		int index = f->binarySearch(sorted_values.values[column], 0, read_rows-1, &val);
		dp.row = index;
		return dp;
	}

	std::string* DataIterator::getStringAt(DataPos pos) {
		std::string* s = new std::string;
		return s;
	}

	void DataIterator::sortCSV(int column) {
		if (column > -1) {
			Utils::Functions* f = new Utils::Functions;
			std::string** arr = new std::string * [MAX_ROWS];
			for (int i = 0; i < read_rows; i++) {
				arr[i] = &values.values[column][i];
			}
			Utils::NewIndexes* ni = f->sortStringArray(arr, read_rows, false);
			for (int y = 0; y < read_rows; y++) {
				for (int i = 0; i < read_columns; i++) {
					sorted_values.values[i][y] = &values.values[i][ni->indexes[y]];
				}
			}
			sorted = true;
			sorted_column = column;
			delete[] arr;
			delete f;
		}
	}

	bool DataIterator::isSorted() {
		return sorted;
	}

	int DataIterator::sortedColumn() {
		return sorted_column;
	}

	void DataIterator::printInfo() {
		std::cout << std::endl
			<< "\t\tAdvanced CSV Report"
			<< std::endl << std::endl
			<< "\tLoaded CSV: " << source.getPath() << std::endl
			<< "\tN columns: " << read_columns << std::endl
			<< "\tN rows: " << read_rows << std::endl
			<< "\tUsed separator: " << curr_separator << std::endl << std::endl;
	}

	void DataIterator::printTable(int max, int page) {
		int mx = (page * max + max);
		int cond = (mx < read_rows ? mx : read_rows);
		std::cout << "Showing pag." <<page +1 << " \trows: " << page * max << " - " << cond << std::endl << std::endl;
		printRow(true, 0);
		for (int i = page * max; i <  cond; i++) {
			printRow(false, i);
		}
	}

	void DataIterator::printRow(bool columns_headers, int row) {
		std::string top_and_low = "";
		std::string center = "";
		row = row < 0 ? 0 : row;
		for (int i = 0; i < read_columns; i++) {
			int req_sz = max_length_column[i];
			top_and_low += std::string((long long int)(req_sz) + 3, '-');
			std::string val = "";
			int more_spaces = 0;
			if (columns_headers) {
				more_spaces = req_sz - columns[i].length();
				val = columns[i];
				if (sorted_column == i) {
					val += (char)217;
					more_spaces -= 1;
				}
			}
			else {
				more_spaces = req_sz - sorted_values.values[i][row]->length();
				val = (*sorted_values.values[i][row]);
			}
			center += "| " + val + (more_spaces > -1 ? std::string(more_spaces, ' ') + ' ' : "");
		}
		center += '|';
		top_and_low += '-';
		std::cout << (columns_headers ? top_and_low : "") << "\n" << center << "\n" << top_and_low;
	}

}
#include "pch.h"
#include <iostream>
#include <fstream>
#include "FileReader.h"
namespace Reader {
	FileReader::FileReader() {
		has_init = false;
	}

	FileReader::FileReader(std::string path) {
		setPath(path);
	}

	bool FileReader::isOpened() {
		return has_opened;
	}

	bool  FileReader::isLoaded() {
		return has_loaded;
	}

	bool FileReader::readFile() {
		if (has_init) {
			data = "";
			fs.open(path_to_file, std::ios::in);  // open a file to perform write operation using file object
			if (fs.is_open()) {   //checking whether the file is open
				has_opened = true;
				std::string tp;
				while (std::getline(fs, tp)) {  //read data from file object and put it into string.
					data += tp;
					data += "\n";
				}
				fs.close();   //close the file object.
				if (data.length() > 0) {
					has_loaded = true;
				}
				return true;
			}
			else {
				has_opened = false;
				has_loaded = false;
			}
		}
		return false;
	}

	std::string FileReader::getData() {
		return data;
	}

	void FileReader::setPath(std::string path) {
		path_to_file = path;
		has_init = path.length() > 0;
	}

	std::string FileReader::getPath() {
		return path_to_file;
	}
}
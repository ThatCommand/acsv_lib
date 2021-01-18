#pragma once
#ifndef DllExport
#define DllExport  __declspec( dllexport )
#endif // !DllExport

#define FILEREADER_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
namespace Reader {
	class DllExport FileReader
	{
	private:
		std::string path_to_file;
		std::fstream fs;
		std::string data;
		bool has_init = false;
		bool has_opened = false;
		bool has_loaded = false;

	public:
		FileReader();
		FileReader(std::string path);
		FileReader(const FileReader& rhs) {
			this->data = rhs.data;
			this->path_to_file = rhs.path_to_file;
			this->has_init = false;
			this->has_loaded = rhs.has_loaded;
			this->has_opened = rhs.has_opened;
		}

		bool isOpened();
		bool isLoaded();

		bool readFile();

		std::string getData();
		void setPath(std::string path);
		std::string getPath();
	};
}


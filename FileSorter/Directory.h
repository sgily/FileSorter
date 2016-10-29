#pragma once

#include <vector>
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>


#define BUFSIZE MAX_PATH
#define MAX_LENGTH 50

namespace mydir {

	class Directory {
		std::vector<std::wstring> listFileNames;
		std::vector<std::wstring> listDirNames;
		std::wstring directoryPath; //including dirname
		int something;
	public:
		Directory() : something(0) {} //remove non arg constructor
		Directory(std::wstring path) : directoryPath(path) {}
		Directory(const TCHAR * path) {
			std::wstring temp(path);
			directoryPath = temp;
		}
		void addFileName(const std::wstring cFileName);
		void addDirName(const std::wstring cFileName);
		void removeDirectory(const TCHAR * directoryName);
		void removeFile(const char * fileName);
		std::vector<std::wstring> getListOfFileNames() const;
		std::vector<std::wstring> getListOfDirectoryNames() const;
		std::wstring mydir::Directory::getDirectoryName() const;
		std::wstring getDirectoryPath() const;
		//std::wstring setDirectoryPath
	};
}

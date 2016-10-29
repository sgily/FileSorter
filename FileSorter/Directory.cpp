
#include "Directory.h"


void mydir::Directory::addFileName(const std::wstring cFileName) {
	listFileNames.push_back(cFileName);
}

void mydir::Directory::addDirName(const std::wstring cFileName) {
	listDirNames.push_back(cFileName);
}

std::vector<std::wstring> mydir::Directory::getListOfDirectoryNames() const {
	return listDirNames;
}

std::vector<std::wstring> mydir::Directory::getListOfFileNames() const {
	return listFileNames;
}

std::wstring mydir::Directory::getDirectoryPath() const {
	return directoryPath;
}

std::wstring mydir::Directory::getDirectoryName() const {
	auto it = directoryPath.end();
	do {
		--it;
	} while (*it != L'\\');
	int pos = it - directoryPath.begin();
	std::wstring temp = directoryPath.substr(pos);
	return temp;
}





void mydir::Directory::removeDirectory(const TCHAR * directoryName) {
	std::wstring name(directoryName);
	auto it = listDirNames.begin();
	while (it != listDirNames.end()) {
		if (*it == name) {
			listDirNames.erase(it);
			it = listDirNames.end();
		}
	}
}

void mydir::Directory::removeFile(const char * fileName) {
	std::wstring name(TEXT("%s", fileName));
	auto it = listFileNames.begin();
	while (it != listFileNames.end()) {
		if (*it == name) {
			listFileNames.erase(it);
			it = listFileNames.end();
		}
	}
}

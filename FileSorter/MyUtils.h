#pragma once

#include <string>
#include <iostream>
#include <atlconv.h>
#include "Directory.h"

#define MAX_DEPTH 10
#define SEPARATOR L"|--"

namespace myutils {
	void wstrtowchr(std::wstring inStr, TCHAR * Buf, size_t bufSize);
	mydir::Directory scanDir(const TCHAR * directoryPath);
	mydir::Directory scanDir(std::wstring directoryPath);
	std::wstring construct_separator(int n);
	std::wstring recDirs(std::vector<std::wstring> &myvec, int n, int depth);
	void displayErrorBox(LPTSTR lpszFunction);
}

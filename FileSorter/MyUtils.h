#pragma once

#include <string>
#include <tchar.h>
#include <iostream>
#include "Directory.h"

namespace myutils {
	void wstrtowchr(std::wstring inStr, TCHAR * Buf, size_t bufSize);
	mydir::Directory scanDir(const TCHAR * directoryPath);
	mydir::Directory scanDir(std::wstring directoryPath);
	void displayErrorBox(LPTSTR lpszFunction);
}

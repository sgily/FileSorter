#include "MyUtils.h"

void myutils::wstrtowchr(std::wstring inStr, TCHAR * Buf, size_t bufSize) {
	//should handle some exceptions ?
	const wchar_t * cname;

	cname = inStr.c_str();
	wcscpy(Buf, cname);
	//std::wcstombs(Buf, cname, bufSize);


}

//IN: myvec: list of directories in root directory
//IN: n: depth
std::wstring myutils::recDirs(std::vector<std::wstring> &myvec, int n, int depth) {
	std::vector<std::wstring> lcopy(myvec);
	std::vector<std::wstring>::iterator it;
	std::vector<std::wstring> localList;
	std::wstring separator = construct_separator(n);
	std::wstring next_separator = construct_separator(++n);
	int recursion_flag = 0;

	for (auto m : lcopy) {
		if (m.substr(0, separator.length()) == separator) {
			std::wstring dname = m.substr(separator.length());
			mydir::Directory temp = myutils::scanDir(dname);
			if (!temp.getListOfDirectoryNames().empty()) {
				for (auto mb : temp.getListOfDirectoryNames()) {
					localList.push_back(next_separator + dname + L"\\" + mb);
				}
				it = myvec.begin();
				while (it < myvec.end()) {
					if ((*it) != m) {
						++it;
					}
					else {
						break;
					}
				}
				if (it == myvec.end()) {
					myvec.insert(myvec.end(), localList.begin(), localList.end());
				}
				else {
					myvec.insert(++it, localList.begin(), localList.end());
				}
				localList.clear();
				recursion_flag = 1;
			}
		}
	}
	if (separator == construct_separator(depth)) {
		return L"done";
	}
	else {
		return recDirs(myvec, n++, depth);
	}
}

std::wstring myutils::construct_separator(int n) {
	std::wstring ret;
	for (int i = 0; i < n; i++) {
		ret += SEPARATOR;
	}
	return ret;
}

mydir::Directory myutils::scanDir(const TCHAR * directoryPath) {
	WIN32_FIND_DATA ffd;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	LARGE_INTEGER filesize;
	DWORD dwError = 0;
	mydir::Directory dir(directoryPath);

	StringCchCopy(szDir, MAX_PATH, directoryPath);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind) {
		//displayErrorBox(TEXT("FindFirstFile1"));
		//trigger exception
		printf("error 1");
		return dir;
	}
	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			std::wstring temp(ffd.cFileName);
			//if (temp.front() != L'.') {
			if (temp != L"." && temp != L".." && temp != L".vs") {
				dir.addDirName(ffd.cFileName);
			}
		}
		else {
			dir.addFileName(ffd.cFileName);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) {
		printf("error 2");
		//displayErrorBox(TEXT("FindFirstFile2"));
	}
	FindClose(hFind);
	//dir.removeDirectory(L".");
	//dir.removeDirectory(L"..");

	return dir;
}

mydir::Directory myutils::scanDir(std::wstring directoryPath) {//, const std::wstring front_append) {
	WIN32_FIND_DATA ffd;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	LARGE_INTEGER filesize;
	DWORD dwError = 0;
	mydir::Directory dir(directoryPath);
	myutils::wstrtowchr(directoryPath, szDir, MAX_PATH); // this doesn't work as expected need to convert from wstring to *char
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind) {
		//displayErrorBox(TEXT("FindFirstFile1"));
		//trigger exception
		printf("error 1\n");
		std::wcout << L"path is " << directoryPath << std::endl;
		//std::wcout << L"dashes is " << front_append << std::endl;
		std::cout << "szDir contains :" << std::endl;
		int i = 0;
		
		for (auto tc : szDir) {
			++i;
			printf("%c", tc);
			i == 14 ? printf("\n") : printf(" ");
			if (tc == NULL) {
				printf("\n");
				return 0;
			}
		}
		return dir;
	}
	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			std::wstring temp(ffd.cFileName);
			//if (temp.front() != L'.') {
			if (temp != L"." && temp != L".." && temp != L".vs") {
				//temp = front_append + temp;
				dir.addDirName(temp);
			}
		}
		else {
			dir.addFileName(ffd.cFileName);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) {
		printf("error 2");
		//displayErrorBox(TEXT("FindFirstFile2"));
	}
	FindClose(hFind);
	//dir.removeDirectory(L".");
	//dir.removeDirectory(L"..");

	return dir;
}

void myutils::displayErrorBox(LPTSTR lpszFunction) {
	//Retrieve the system error message for the last error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	//Display the error message and clean up
	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));

	StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"), lpszFunction, dw, lpMsgBuf);

	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);

	LocalFree(lpDisplayBuf);
}
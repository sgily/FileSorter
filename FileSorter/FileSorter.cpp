// FileSorter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
//#include <list>
//#include <string>
//#include <string.h>
#include "MyUtils.h"

//Global args
char _current_dir[MAX_PATH];
char _filename[MAX_LENGTH] = "defaultTree.txt";
TCHAR _current_path[MAX_PATH];
int _depth = MAX_DEPTH;

template <size_t N>
int checkCurrentDirectory(DWORD dwRet, TCHAR(&Buffer)[N]);

void parseMyCLI(int argc, char **argv);

void main(int argc, char **argv)
{
	DWORD dwRet;
	parseMyCLI(argc, argv);
	std::vector<std::wstring> tofill;
	std::vector<std::wstring> output;
	std::wstring dashes(L"--");


	dwRet = GetCurrentDirectory(BUFSIZE, _current_path);
	if (checkCurrentDirectory(dwRet, _current_path) != 0) {
		return;
	}

	//mydir::Directory testdir = myutils::scanDir(L"C:\\Users\\Stas\\Documents\\Visual Studio 2015\\Projects");
	mydir::Directory dir = myutils::scanDir(_current_path);
	printf("print the contents of dir: \n");

	tofill.push_back(dir.getDirectoryPath());
	if (!dir.getListOfDirectoryNames().empty()) {
		for (std::wstring m : dir.getListOfDirectoryNames()) {
			std::wcout << L"Directory: " << m << std::endl;
			tofill.push_back(SEPARATOR + dir.getDirectoryPath() + L"\\" + m);
		}
	}
	output.push_back(L"this is output");
	
	std::wstring myret = myutils::recDirs(tofill, 1, _depth);
	for (auto m : tofill) {
		std::wstring::iterator it1 = m.begin();
		std::wstring::iterator it2 = m.end();
		while ((*it1) == L'-' || (*it1) == L'|') {
			++it1;
		}
		do {
			--it2;
		} while ((*it2) != '\\');
		m.erase(it1, ++it2);
		output.push_back(m);
	}
	std::wofstream myfile(_filename);

	if (!output.empty()) {
		printf("output not empty\n");
		for (auto m : output) {
			myfile << m << std::endl;
		}
	}
	myfile.close();

	return;

}

template <size_t N>
int checkCurrentDirectory(DWORD dwRet, TCHAR (&Buffer)[N]) {
	if (dwRet == 0)
	{
		printf("GetCurrentDirectory failed (%d)\n", GetLastError());
		return 1;
	}

	if ((dwRet + 3) > BUFSIZE)
	{
		printf("Buffer too small; need %d characters\n", dwRet);
		return 2;
	}

	printf("%d characters written to the bufffer; Current Directory is: %s\n", (int)dwRet, Buffer);
	printf("Buffer contains: ");
	int i = 0;
	for (auto tc : Buffer) {
		++i;
		printf("%c", tc);
		i == 14 ? printf("\n") : printf(" ");
		if (tc == NULL) {
			printf("\n");
			return 0;
		}
	}
	printf("\n");
	return 0;
}

//add errorchecking (Exceptions ?)
void parseMyCLI(int argc, char ** argv) {
	if (argc == 1) {
		//use default
		return;
	}
	for (int i = 0; i < argc; i++) {
		printf("argv[%d] = %s\n", i, argv[i]);
		//filename for the tree
		if (strcmp(argv[i], "-f") == 0) {
			strcpy(_filename, argv[i + 1]);
			if (strstr(_filename, ".txt") == NULL) {
				strcat(_filename, ".txt");
			}
		}
		//directory depth
		if (strcmp(argv[i], "-d") == 0) {
			_depth = strtol(argv[i + 1], NULL, 10);
		}
	}
}
#pragma once
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <cstdlib>

using namespace std;

struct Utils
{
	static void FullPathName(string name)
	{
		TCHAR buffer[4096] = TEXT("");
		TCHAR** lppPart = { NULL };
		DWORD retval = GetFullPathName((TCHAR*)name.c_str(), 4096, buffer, lppPart);
		std::cout << buffer << std::endl;
	}

	static bool FileExist(const char * fileName)
	{
		ifstream infile(fileName);
		return infile.good();
	}

	static stringstream * ReadFile(const char* fileName)
	{
		if (!FileExist(fileName))
			return NULL;

		stringstream* ss = new stringstream();
		string line;
		ifstream file(fileName);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				*ss << line << "\n";
			}
			file.close();
		}
		return ss;
	}
};
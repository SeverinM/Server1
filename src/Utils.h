#pragma once
#include <sys/stat.h>
#include <fstream>
#include <sstream>

using namespace std;

struct Utils
{
	static bool FileExist(const char * fileName)
	{
		struct stat buffer;
		return (stat(fileName, &buffer) == 0);
	}

	stringstream * ReadFile(const char* fileName, unsigned int &size)
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
				*ss << line;
			}
			file.close();
		}
		return ss;
	}
};
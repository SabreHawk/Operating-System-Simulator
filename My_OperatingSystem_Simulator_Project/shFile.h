#pragma once
#ifndef _SH_FILE_H_
#define _SH_FILE_H_

#include <string>
#include <vector>
#include "shAbsolutePath.h"
class shFile
{
private:
	//shAbsolutePath absolutePath;
	std::string fileName;
	std::string context;
	bool attribute[3];
	void initAttrbutes();
public:
	shFile();
	shFile(std::string);
	~shFile();
	//bool setAbsolutePath(shAbsolutePath);
	std::string getFileName();
	bool setFileName(std::string);
	bool getAttribute(int);
	bool setAttribute(int,bool);
	std::string getContext();
	bool setContext(std::string);
	bool addContext(std::string);
};

#endif // !_SH_FILE_H_



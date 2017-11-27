#pragma once
#ifndef _SH_ABSOLUTEPATH_H_
#define _SH_ABSOLUTEPATH_H_

#include <iostream>
#include <string>
#include <vector>
class shAbsolutePath{
	std::vector<std::string> addressVector;
	bool isLegal;
public:
	shAbsolutePath();
	shAbsolutePath(std::string);
	shAbsolutePath(std::vector<std::string>);
	~shAbsolutePath();
	bool dispPath();
	int getLayer();
	std::string getFolderName(int);
	shAbsolutePath getFatherPath();
	bool setPath(std::string);
	bool checkPath();
	bool addAddress(std::string);
};
#endif // !_SH_ABSOLUTEPATH_H_



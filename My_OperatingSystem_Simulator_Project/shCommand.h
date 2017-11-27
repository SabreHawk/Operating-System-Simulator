#pragma once

#ifndef _SH_COMMAND_H_
#define _SH_COMMAND_H_
#include <map>
#include <string>
#include <vector>
class shCommand
{
	std::map<std::string, int> cmdTable;
	std::string operationType;
	std::vector<std::string> operationParameter;
	bool initCMDTable();
public:
	shCommand();
	~shCommand();
	shCommand(std::string);
	bool setCommand(std::string);
	bool dispCommand();
	int getOperationType();
	bool isLegal();
	int getParameterNum();
	std::string getParameter(int);
	bool clear();
};
#endif // !_SH_COMMAND_H_



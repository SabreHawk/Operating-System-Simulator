#include "stdafx.h"
#include "shCommand.h"

#include <iostream>
shCommand::shCommand() {
	initCMDTable();
}


shCommand::~shCommand() {
}
shCommand::shCommand(std::string _comd) {
	initCMDTable();
	setCommand(_comd);
}

bool shCommand::initCMDTable() {
	cmdTable["create"] = 1;
	cmdTable["open"] = 2;
	cmdTable["read"] = 3;
	cmdTable["write"] = 4;
	cmdTable["close"] = 5;
	cmdTable["closeall"] = 6;
	cmdTable["del"] = 7;
	cmdTable["undel"] = 8;
	cmdTable["copy"] = 9;
	cmdTable["dir"] = 10;
	cmdTable["cd"] = 11;
	cmdTable["md"] = 12;
	cmdTable["rd"] = 13;
	cmdTable["type"]= 14;
	cmdTable["ren"] = 15;
	cmdTable["attrib"] = 16;
	cmdTable["uof"] = 17;
	cmdTable["help"] = 18;
	cmdTable["exit"] = 19;
	cmdTable["fc"] = 20;
	cmdTable["replace"] = 21;
	cmdTable["move"] = 22;
 	return true;
}
bool shCommand::setCommand(std::string _str) {
	operationType.clear();
	operationParameter.clear();
	int temp_len = (int)_str.length();
	int charIndex = 0;

	for (charIndex = 0; charIndex < temp_len; ++charIndex) {
		if (_str[charIndex] != ' ') {
			operationType += _str[charIndex];
		} else {
			++charIndex;
			break;
		}
	}
	
	std::string temp_str;
	for (; charIndex < temp_len; ++charIndex) {
		if (_str[charIndex] != ' ') {
			temp_str += _str[charIndex];
		} else {
			operationParameter.push_back(temp_str);
			temp_str.clear();
		}
	}
	if (temp_str.size() != 0) {
		operationParameter.push_back(temp_str);
	}

	return true;
}

bool shCommand::dispCommand() {
	std::cout << operationType;
	std::vector<std::string>::iterator itor;
	for (itor = operationParameter.begin(); itor != operationParameter.end(); ++itor) {
		std::cout << " " << *itor;
	}std::cout << std::endl;
	return true;
}
int shCommand::getOperationType() {
	if (isLegal()) {
		return cmdTable[operationType];
	} else {
		return -1;
	}

}
bool shCommand::isLegal() {
	std::map<std::string, int>::iterator itor;
	itor = cmdTable.find(operationType);
	if (itor == cmdTable.end()) {
		return false;
	} else {
		return true;
	}
}
int shCommand::getParameterNum() {
	return operationParameter.size();
}
std::string shCommand::getParameter(int _index) {
	if (_index < operationParameter.size()) {
		return operationParameter[_index];
	} else {
		return "";
	}
}

bool shCommand::clear() {
	operationType.clear();
	operationParameter.clear();
	return true;
}
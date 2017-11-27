#include "stdafx.h"
#include "shFolder.h"


void shFolder::initAttrbutes() {
	memset(attributes, false, sizeof(bool) * 3);
}

shFolder::shFolder() {
	initAttrbutes();
}

shFolder::~shFolder() {
}

shFolder::shFolder(std::string _folderName, shAbsolutePath _absPath) 
:folderName(_folderName){
	initAttrbutes();
	//folderPath = _absPath;
}

//bool shFolder::setAbsolutePath(shAbsolutePath _path) {
//	folderPath = _path;
//}
bool shFolder::getAttribute(int _index) {
	return attributes[_index];
}

bool shFolder::setAttribute(int _index,bool _type) {
	attributes[_index] = _type;
	return true;
}

void shFolder::dispAbsolutePath() {
//	folderPath.dispPath();
}

bool shFolder::setIndex(int _address) {
	index = _address;
	return true;
}

std::string shFolder::getFolderName() {
	return folderName;
}

int shFolder::getSubfolderIndex(int _index) {
	return subfolderIndexVector[_index];
}

int shFolder::getSubfolderNum() {
	return (int)subfolderIndexVector.size();
}

bool shFolder::setFatherIndex(int _index) {
	fatherIndex = _index;
	return true;
}

int shFolder::getFolderIndex() {
	return index;
}

bool shFolder::addSubFolder(int _index) {
	subfolderIndexVector.push_back(_index);
	return true;
}

bool shFolder::setFolderName(std::string _name) {
	folderName = _name;
	return true;
}

int shFolder::getFatherIndex() {
	return fatherIndex;
}

bool shFolder::addFile(shFile temp_file) {
	//temp_file.setAbsolutePath(folderPath);
	fileVector.push_back(temp_file);
	return true;
}

int shFolder::getFileNum() {
	return (int)fileVector.size();
}

bool shFolder::setFileName(int _index,std::string _newName) {
	fileVector[_index].setFileName(_newName);
	return true;
}

bool shFolder::setFileAttribute(int _index, int _no,bool type) {
	fileVector[_index].setAttribute(_no, type);
	return true;
}

std::string shFolder::getFileContext(int _index) {
	if (_index >= fileVector.size()) {
		return "";
	}
	return fileVector[_index].getContext();
}

bool shFolder::setFileContext(int _index,std::string _context) {
	if (_index > fileVector.size()) {
		std::cout << "Index Out Of Range" << std::endl;
		return "";
	}
	fileVector[_index].setContext(_context);
	return true;
}

shFile shFolder::getFile(int _index) {
	if (index >= fileVector.size()) {
		std::cout << "File Index Out Of Range" << std::endl;
		return false;
	}
	return fileVector[_index];
}

bool shFolder::setFile(int _index,shFile _file) {
	fileVector[_index] = _file;
//	fileVector[_index].setAbsolutePath(folderPath);
	return true;
}

std::string shFolder::getFileName(int _index) {
	if (_index >= fileVector.size()) {
		return "";
	} else {
		return fileVector[_index].getFileName();
	}
}

bool shFolder::getFileAttribute(int _index,int _attIndex) {
	return fileVector[_index].getAttribute(_attIndex);
}

bool shFolder::deleteSubfolder(int _index) {
	std::vector<int>::iterator itor;
//std::cout << _index << std::endl;
//std::cout << subfolderIndexVector.size() << std::endl;
	itor = subfolderIndexVector.begin() + _index;
	subfolderIndexVector.erase(itor);
	return true;
}

bool shFolder::deleteFile(int _index) {
	std::vector<shFile>::iterator itor;
	itor = fileVector.begin() + _index;
	fileVector.erase(itor);
	return true;
}

bool shFolder::decrementIndex() {
	std::cout << index << std::endl;
	--index;
	return true;
}





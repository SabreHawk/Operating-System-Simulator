#include "stdafx.h"
#include "shFile.h"

//private
void shFile::initAttrbutes() {
	memset(attribute, false, sizeof(bool) * 3);
}
shFile::shFile() {
	initAttrbutes();
}
shFile::shFile(std::string _fileName) {
	initAttrbutes();
	fileName = _fileName;
}

shFile::~shFile() {
}

//bool shFile::setAbsolutePath(shAbsolutePath _path) {
//	absolutePath = _path;
//	return true;
//}
std::string shFile::getFileName() {
	return fileName;
}

bool shFile::setFileName(std::string _fileName) {
	fileName = _fileName;
	return true;
}

bool shFile::getAttribute(int _index){
	if (_index > 3 || _index < 0) {
		return false;
	}
	return attribute[_index];
}
bool shFile::setAttribute(int _index,bool _a) {
	if (_index > 3 || _index < 0) {
		return false;
	}
	attribute[_index] = _a;
	return true;
}
std::string shFile::getContext() {
	return context;
}

bool shFile::setContext(std::string _c) {
	context = _c;
	return true;
}
bool shFile::addContext(std::string _c) {
	context += _c;
	return true;
}

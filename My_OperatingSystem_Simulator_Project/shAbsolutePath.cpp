#include "stdafx.h"
#include "shAbsolutePath.h"


shAbsolutePath::shAbsolutePath() {

}
shAbsolutePath::shAbsolutePath(std::string _path){

	std::string temp_str;
	int temp_len = _path.length();
	for (int i = 1; i < temp_len; ++i) {
		if (_path[i] != '/') {
			temp_str += _path[i];
		} else {
			addressVector.push_back(temp_str);
			temp_str = "";
		}
	}
	addressVector.push_back(temp_str);
	if (*addressVector.begin() != "root") {
		addressVector.insert(addressVector.begin(), "root");
	}
	if (_path[0] != '/') {
		isLegal = false;
	}
	isLegal = true;
}
shAbsolutePath::shAbsolutePath(std::vector<std::string> _addressVector){
	addressVector = _addressVector;
}


shAbsolutePath::~shAbsolutePath(){
}

bool shAbsolutePath::dispPath() {
	if (!addressVector.size()) {
		return false;;
	}
	std::vector<std::string>::iterator itor;
	for (itor = addressVector.begin(); itor != addressVector.end(); ++itor) {
		std::cout << "/" << *itor;
	}
	return true;
}
std::string shAbsolutePath::getFolderName(int _layer) {
	if (_layer < addressVector.size()) {
		return addressVector.back();
	} else {
		std::cout << "Couldn't Get Path By Layer " << _layer << std::endl;
		return "";
	}
}
bool shAbsolutePath::setPath(std::string _path) {
	std::string temp_str = "";
	int temp_len = _path.length();
	for (int i = 1; i < temp_len; ++i) {
		if (_path[i] != '/') {
			temp_str += _path[i];
		} else {
			addressVector.push_back(temp_str);
			temp_str = "";
		}
	}
	addressVector.push_back(temp_str);
	if (*addressVector.begin() != "root") {
		addressVector.insert(addressVector.begin(), "root");
	}
	isLegal = true;
	if (_path[0] != '/') {
		isLegal = false;
	}
	return true;
}

shAbsolutePath shAbsolutePath::getFatherPath() {
	std::vector < std::string> fatherVector = addressVector;
	fatherVector.pop_back();
	shAbsolutePath father_path(fatherVector);
	return father_path;
}

int shAbsolutePath::getLayer() {
	return addressVector.size();
}

bool shAbsolutePath::checkPath() {
	return isLegal;
}
bool shAbsolutePath::addAddress(std::string temp_address) {
	if (isLegal) {
		addressVector.push_back(temp_address);
		return true;
	}
	return false;
}
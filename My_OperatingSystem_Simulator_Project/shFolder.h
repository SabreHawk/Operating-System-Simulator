#pragma once
#ifndef _SH_FOLDER_H_
#define _SH_FOLDER_H_
#include "shFile.h"
#include "shAbsolutePath.h"

class shFolder
{
	std::string folderName;
	//shAbsolutePath folderPath;
	std::vector<shFile> fileVector;
	std::vector<int> subfolderIndexVector;
	bool attributes[3];
	int fatherIndex;
	int index;
	void initAttrbutes();
public:
	shFolder();
	shFolder(std::string, shAbsolutePath);
	~shFolder();

	void dispAbsolutePath();
//	void dispRelativePath();
	bool addFile(shFile);
	bool addSubFolder(int);
	std::string  getFolderName();
	//bool setAbsolutePath(shAbsolutePath);
	bool getAttribute(int);
	bool setAttribute(int,bool);
	bool setFolderName(std::string);
	int getFatherIndex();
	bool setFatherIndex(int);
	bool setIndex(int);
	int getFolderIndex();
	int getSubfolderIndex(int);
	int getSubfolderNum();
	shFile getFile(int);
	bool setFile(int,shFile);
	int getFileNum();
	std::string getFileContext(int);
	bool setFileName(int, std::string);
	bool setFileContext(int,std::string);
	bool setFileAttribute(int, int, bool);
	std::string getFileName(int);
	bool getFileAttribute(int,int);
	bool deleteSubfolder(int);
	bool deleteFile(int);
	bool decrementIndex();

};


#endif // !_SH_FOLDER_H_


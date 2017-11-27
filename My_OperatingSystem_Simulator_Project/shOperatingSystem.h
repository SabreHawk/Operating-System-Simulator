#pragma once
#ifndef _SH_OPERATING_SYSTEM_H_
#define _SH_OPERATING_SYSTEM_H_

#include "shFolder.h"
#include "shCommand.h"

struct openFilePos {
	int folderIndex;
	int fileIndex;
};
class shOperatingSystem{
	shAbsolutePath currentPath;
	std::vector<shFolder> folderVector;
	shCommand currentCommand;
	int curFile;
	std::vector<openFilePos>::iterator filePointer;
	std::vector<openFilePos> openedFile;

	bool isRunning;
	bool listenCommand();
	bool distributeCommand();
	bool isFileOpened(std::string);
	bool findAddress(shAbsolutePath);
	bool createFolder(std::string,std::string);
	bool deleteFolder(std::string);
	int getFolderIndex(shAbsolutePath, int = 0, int = 0);
	bool createFile(std::string, shAbsolutePath);
	bool openFile(std::string);
	bool closeFile(std::string);
	bool writeFile(std::string, std::string, int _pos);
	bool readFile(std::string, int);
	bool copyFile(std::string, std::string);
	bool renameFile(std::string, std::string);
	bool changeAttribute(std::string, std::string);
	bool compareFile(std::string, std::string);
	bool replaceFile(std::string, std::string);
	bool moveFile(std::string, std::string);
public:
	shOperatingSystem();
	~shOperatingSystem();
	bool launchSystem();
	bool createCMD();
	bool openCMD();				
	bool readCMD();				
	bool writeCMD();			
	bool closeCMD();
	bool closeAllCMD();
	bool delCMD();
	bool unDelCMD();
	bool copyCMD();
	bool dirCMD();
	bool cdCMD();
	bool mdCMD();
	bool rdCMD();
	bool typeCMD();
	bool renCMD();
	bool attribCMD();
	bool uofCMD();
	bool helpCMD();
	bool exitCMD();
	bool fcCMD();
	bool replaceCMD();
	bool moveCMD();
};
#endif // !_SH_OPERATING_SYSTEM_H_



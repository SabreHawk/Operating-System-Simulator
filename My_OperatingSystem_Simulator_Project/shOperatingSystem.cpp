#include "stdafx.h"
#include "shOperatingSystem.h"

shOperatingSystem::shOperatingSystem()
:curFile(-1){
}

shOperatingSystem::~shOperatingSystem(){
}

bool shOperatingSystem::listenCommand() {
	std::string user_command_str;
	std::getline(std::cin, user_command_str);
	shCommand temp_comd(user_command_str);
	if (user_command_str == "") {
		return true;
	}
	currentCommand = temp_comd;
	if (currentCommand.isLegal()) {
		return true;
	} else {
		return false;
	}

}

bool shOperatingSystem::distributeCommand() {
	bool isCompleted = false;
//	std::cout << "TYPE :" << currentCommand.getOperationType() << std::endl;
	switch (currentCommand.getOperationType()) {
	case 1:
		if (createCMD()) {
			isCompleted = true;
		}break;
	case 2:
		if (openCMD()) {
			isCompleted = true;
		}break;
	case 3:
		if (readCMD()) {
			isCompleted = true;
		}break;
	case 4:
		if (writeCMD()) {
			isCompleted = true;
		}break;
	case 5:
		if (closeCMD()) {
			isCompleted = true;
		}break;
	case 6:
		if (closeAllCMD()) {
			isCompleted = true;
		}break;
	case 7:
		if (delCMD()) {
			isCompleted = true;
		}break;
	case 8:
		if (unDelCMD()) {
			isCompleted = true;
		}break;
	case 9:
		if (copyCMD()) {
			isCompleted = true;
		}break;
	case 10:
		if (dirCMD()) {
			isCompleted = true;
		}break;
	case 11:
		if (cdCMD()) {
			isCompleted = true;
		}break;
	case 12:
		if (mdCMD()) {
			isCompleted = true;
		}break;
	case 13:
		if (rdCMD()) {
			isCompleted = true;
		}break;
	case 14:
		if (typeCMD()) {
			isCompleted = true;
		}break;
	case 15:
		if (renCMD()) {
			isCompleted = true;
		}break;
	case 16:
		if (attribCMD()) {
			isCompleted = true;
		}break;
	case 17:
		if (uofCMD()) {
			isCompleted = true;
		}break;
	case 18:
		if (helpCMD()) {
			isCompleted = true;
		}break;
	case 19:
		if (exitCMD()) {
			isCompleted = true;
		}break;
	case 20:
		if (fcCMD()) {
			isCompleted = true;
		}break;
	case 21:
		if (replaceCMD()) {
			isCompleted = true;
		}break;
	case 22:
		if (moveCMD()) {
			isCompleted = true;
		}break;
	default:
		break;
	}
	currentCommand.clear();
	return isCompleted;
}

bool shOperatingSystem::launchSystem() {
	//Launch & display system info
	std::cout << "Launching System " << std::endl;
	std::cout << "Initialzing Disks " << std::endl;
	shAbsolutePath rootAddress("/root");
	shFolder rootDirectory("root", rootAddress);
	rootDirectory.setIndex(0);
	folderVector.push_back(rootDirectory);
	currentPath = rootAddress;
	std::cout << "System Ready " << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "Current Path :";
	rootDirectory.dispAbsolutePath();
	std::cout << std::endl;

	//
	isRunning = true;
	while (isRunning) {
		currentPath.dispPath();
		std::cout << ">";
		if (listenCommand()) {
			distributeCommand();
		} else {
			std::cout << "Command illegal" << std::endl;
		}
	}
	return true;
}

bool shOperatingSystem::isFileOpened(std::string _fileName) {
	std::vector<openFilePos>::iterator itor;
	for (itor = openedFile.begin(); itor != openedFile.end(); ++itor) {
		if (_fileName == folderVector[itor->folderIndex].getFileName(itor->fileIndex) && getFolderIndex(currentPath) == itor->folderIndex) {
			return true;
		}
	}
	return false;
}

bool shOperatingSystem::createFolder(std::string _fileName,std::string _attrib) {
	shAbsolutePath temp_path = currentPath;
	temp_path.addAddress(currentCommand.getParameter(0));
	if (findAddress(temp_path)) {
		std::cout << "# ERROR : Folder Is Existed" << std::endl;
		return false;
	}
	shFolder temp_folder(_fileName, temp_path);
	int father_folder_index = this->getFolderIndex(currentPath);
	temp_folder.setFatherIndex(father_folder_index);
	temp_folder.setIndex((int)folderVector.size());
	if (_attrib.size() > 3) {
		std::cout << "# ERROR : Attributes Number Ilegal" << std::endl;
		return false;
	} 
	for (int i = 0; i < _attrib.size(); ++i) {
		switch (_attrib[i]) {
		case 'r':
			temp_folder.setAttribute(0, true); break;
		case 'h':
			temp_folder.setAttribute(1, true); break;
		case 's':
			temp_folder.setAttribute(1, true); break;
		default:
			std::cout << "# ERROR : Attributes Type Ilegal" << std::endl;
			break;
		}
	}
	folderVector.push_back(temp_folder);
	folderVector[father_folder_index].addSubFolder(temp_folder.getFolderIndex());
	std::cout << "$ Create Folder " << _fileName << std::endl;
	return true;
}

bool shOperatingSystem::deleteFolder(std::string _folderName) {
	shAbsolutePath temp_path = currentPath;
	shFolder temp_folder = folderVector[getFolderIndex(temp_path)];
	shFolder temp_subfolder;
	int subfolder_num = temp_folder.getSubfolderNum();
	for (int i = 0; i < subfolder_num; ++i) {
		temp_subfolder = folderVector[temp_folder.getSubfolderIndex(i)];
		if (temp_subfolder.getFolderName() == _folderName) {
			if (temp_subfolder.getFileNum() != 0 || temp_subfolder.getSubfolderNum() != 0) {
				std::cout << "# ERROR :The Folder Is Not Empty" << std::endl;
			} else {
				folderVector[getFolderIndex(temp_path)].deleteSubfolder(i);
				int temp_subIndex = temp_subfolder.getFolderIndex();
				std::vector<shFolder>::iterator itor = folderVector.begin() + temp_subIndex;
				folderVector.erase(itor);
				for (itor = folderVector.begin() + temp_subIndex; itor != folderVector.end(); ++itor) {
					itor->dispAbsolutePath();
				}
				std::cout << "$ Delete Folder : " << _folderName << std::endl;
				return true;
			}
		}
	}
	std::cout << "# ERROR : Folder Is Not Existing" << std::endl;
	return false;
}

int shOperatingSystem::getFolderIndex(shAbsolutePath _path, int _folderIndex, int _layer) {
	int out_index = -1;
	if (_path.getLayer() - 1 == _layer) {
		return _folderIndex;
	}
	shFolder curFolder = folderVector[_folderIndex];
	shFolder temp_subFolder;
	int subFolderNum = curFolder.getSubfolderNum();
	//curFolder.dispAbsolutePath(); std::cout << subFolderNum << std::endl;
	for (int i = 0; i < subFolderNum; ++i) {
		temp_subFolder = folderVector[curFolder.getSubfolderIndex(i)];
		std::string subFolderName = temp_subFolder.getFolderName();
		//std::cout << subFolderName << std::endl;
		if (_path.getFolderName(_layer) == subFolderName) {
			out_index = getFolderIndex(_path, temp_subFolder.getFolderIndex(), _layer + 1);
			break;
		}
	}
	return out_index;
}

bool shOperatingSystem::createFile(std::string _fileName, shAbsolutePath _absPath) {
	shFile temp_file(_fileName);
	//temp_file.setAbsolutePath(_absPath);
	int temp_index = getFolderIndex(_absPath);
	folderVector[temp_index].addFile(temp_file);
	std::cout << "$ Create File : " << _fileName << std::endl;
	return true;
}

bool shOperatingSystem::openFile(std::string _fileName) {
	shAbsolutePath temp_path = currentPath;
	shFolder temp_folder = folderVector[getFolderIndex(temp_path)];
	openFilePos temp_filePos;
	temp_filePos.folderIndex = getFolderIndex(temp_path);
	if (temp_filePos.folderIndex != temp_filePos.folderIndex) {
		std::cout << "# ERROR : Folder Index Illegal" << std::endl;
	}
	std::vector<openFilePos>::iterator itor;
	for (itor = openedFile.begin(); itor != openedFile.end(); ++itor) {
		if (_fileName == folderVector[itor->folderIndex].getFileName(itor->fileIndex) && getFolderIndex(currentPath) == itor->folderIndex) {
			filePointer = itor;
			std::cout << "$ Update Current File" << std::endl;
			return false;
		}
	}
	for (int i = 0; i < temp_folder.getFileNum(); ++i) {
		if (_fileName == temp_folder.getFileName(i)) {
			temp_filePos.fileIndex = i;
			openedFile.push_back(temp_filePos);
			filePointer = openedFile.end()-1;
			std::cout << "$ Open File : " << _fileName << std::endl;
			return true;
		}
	}
	std::cout << "# ERROR : File Is Not Existing" << std::endl;
	return false;
}

bool shOperatingSystem::closeFile(std::string _fileName) {
	if (openedFile.size() == 0) {
		std::cout << "# ERROR : No File Is Opened" << std::endl;
		return true;
	}
	if (_fileName == "#c" && filePointer != openedFile.end()) {
		std::cout << "$ Close File : " << folderVector[filePointer->folderIndex].getFileName(filePointer->fileIndex) << std::endl;
		openedFile.erase(filePointer);
	//	std::cout << "E" << std::endl;
		if (openedFile.size() != 0) {
			filePointer = openedFile.end() - 1;
		} else {
			filePointer = openedFile.end();
		}

		return true;
	}
	std::vector<openFilePos>::iterator itor;
	for (itor = openedFile.begin(); itor != openedFile.end(); ++itor) {
		if (_fileName == folderVector[itor->folderIndex].getFileName(itor->fileIndex) && getFolderIndex(currentPath) == itor->folderIndex) {
			openedFile.erase(itor);
			std::cout << "$ Close File : " << _fileName << std::endl;
			return true;
		}
	}
		std::cout << "# ERROR : File Is Not Existing Or Opened" << std::endl;
		return false;
}

bool shOperatingSystem::writeFile(std::string _fileName, std::string _context, int _pos) {
	shAbsolutePath temp_path = currentPath;
	shFolder temp_folder = folderVector[getFolderIndex(temp_path)];
	int temp_file_num = temp_folder.getFileNum();
	std::vector<openFilePos>::iterator itor;
	bool isOpened = false;
	for (itor = openedFile.begin(); itor != openedFile.end(); ++itor) {
		if (_fileName == folderVector[itor->folderIndex].getFileName(itor->fileIndex) &&getFolderIndex(currentPath) == itor->folderIndex) {
			isOpened = true;
			if (folderVector[itor->folderIndex].getFileAttribute(itor->fileIndex, 0)) {
				std::cout << "# ERROR : Read-Only File " << std::endl;
				return false;
			}
		}
	}
	if (!isOpened) {
		std::cout << "# ERROR : File Is Not Existing Or Opened" << std::endl;
		return false;
	}
	for (int i = 0; i < temp_file_num; ++i) {
		if (_fileName == temp_folder.getFileName(i)) {
			std::string temp_context = temp_folder.getFileContext(i);
			if (_pos > temp_context.size()) {
				std::cout << "# ERROR : Writing Position Illegal" << std::endl;
				return false;
			} else {
				std::string pre_str = temp_context.substr(0, _pos);
				std::string aft_str = temp_context.substr(_pos, temp_context.size() - _pos);
				folderVector[getFolderIndex(temp_path)].setFileContext(i, pre_str + _context + aft_str);
				return true;
			}
		}
	}
	std::cout << "# ERROR : File Is Not Existing" << std::endl;
	return false;
}

bool shOperatingSystem::readFile(std::string _fileName, int _pos) {
	std::vector<openFilePos>::iterator itor;
	std::string temp_str;
	for (itor = openedFile.begin(); itor != openedFile.end(); ++itor) {
		if (_fileName == folderVector[itor->folderIndex].getFileName(itor->fileIndex) && getFolderIndex(currentPath) == itor->folderIndex) {
			temp_str = folderVector[itor->folderIndex].getFileContext(itor->fileIndex);
			std::cout << "$ Context : ";
			for (int j = 0; j < temp_str.size(); ++j) {
				std::cout << temp_str[j];
			}std::cout << std::endl;
			return true;
		}
	}
	std::cout << "# ERROR : File Is Not Existing Or Opened" << std::endl;
	return false;
}

bool shOperatingSystem::copyFile(std::string _souFileName, std::string _tarFileName) {
	shAbsolutePath temp_path = currentPath;
	shFolder temp_folder = folderVector[getFolderIndex(temp_path)];
	shFile temp_file;
	std::string sou_context;
	int tarFileIndex = 0;
	bool isSouFileExist = false;
	bool isTarFileExist = false;
	for (int i = 0; i < temp_folder.getFileNum(); ++i) {
		if (_souFileName == temp_folder.getFileName(i)) {
			sou_context = temp_folder.getFileContext(i);
			temp_file = temp_folder.getFile(i);
			isSouFileExist = true;
		}
		if (_tarFileName == temp_folder.getFileName(i)) {
			tarFileIndex = i;
			isTarFileExist = true;
		}
	}
	if (!isSouFileExist) {
		std::cout << "# ERROR : Source File Is Not Existing" << std::endl;
		return false;
	}
	if (isTarFileExist) {
		folderVector[getFolderIndex(temp_path)].setFileContext(tarFileIndex, sou_context);
		std::cout << "$ Copy File Succeed" << std::endl;
		return true;
	} else {
		for (int i = 0; i < temp_folder.getSubfolderNum(); ++i) {
			if (_tarFileName == folderVector[temp_folder.getSubfolderIndex(i)].getFolderName()) {
				temp_path.addAddress(_tarFileName);
				//temp_file.setAbsolutePath(temp_path);
				folderVector[getFolderIndex(temp_path)].addFile(temp_file);
				std::cout << "$ Copy File To Subfolder Succeed" << std::endl;
				return true;
			}
		}
		temp_file.setFileName(_tarFileName);
		folderVector[getFolderIndex(temp_path)].addFile(temp_file);
		std::cout << "$ Create And Copy File Succeed" << std::endl;
		return true;
	}
}

bool shOperatingSystem::renameFile(std::string _oldName, std::string _newName) {
	std::vector<openFilePos>::iterator itor;
	for (itor = openedFile.begin(); itor != openedFile.end(); ++itor) {
		if (_oldName == folderVector[itor->folderIndex].getFileName(itor->fileIndex) && getFolderIndex(currentPath) == itor->folderIndex) {
			std::cout << "# ERROR : File Is Opened" << std::endl;
			return false;
		}
	}
	shAbsolutePath temp_path = currentPath;
	shFolder temp_folder = folderVector[getFolderIndex(temp_path)];
	for(int i = 0;i < temp_folder.getFileNum();++ i){
		if (_oldName == temp_folder.getFileName(i)) {
			folderVector[getFolderIndex(temp_path)].setFileName(i,_newName);
			std::cout << "Rename File : " << _oldName << " -> " << _newName << std::endl;
			return true;
		}
	}
	std::cout << "# ERROR : File Is Not Existing Or Opened" << std::endl;
	return false;

}

bool shOperatingSystem::changeAttribute(std::string _fileName, std::string _order) {
	if (_order.size() != 2) {
		std::cout << "# ERROR : Command Parameter Type Ilegal" << std::endl;
		return false;
	}

	std::vector<openFilePos>::iterator itor;
	for (itor = openedFile.begin(); itor != openedFile.end(); ++itor) {
		if (_fileName == folderVector[itor->folderIndex].getFileName(itor->fileIndex) && getFolderIndex(currentPath) == itor->folderIndex) {
			std::cout << "# ERROR : File Is Opened" << std::endl;
			return false;
		}
	}

	bool orderType = false;;
	int paraType = 0;
	if (_order[0] == '-') {
		orderType = false;
	} else if (_order[0] == '+') {
		orderType = true;
	} else {
		std::cout << "# ERROR : Command Parameter Type Ilegal" << std::endl;
		return false;
	}
	if (_order[1] == 'r') {
		paraType = 0;
	} else if (_order[1] == 'h') {
		paraType = 1;
	} else if (_order[1] == 's') {
		paraType = 2;
	}
	shAbsolutePath temp_path = currentPath;
	shFolder temp_folder = folderVector[getFolderIndex(temp_path)];
	for (int i = 0; i < temp_folder.getFileNum(); ++i) {
		if (_fileName == temp_folder.getFileName(i)) {
			folderVector[getFolderIndex(temp_path)].setFileAttribute(i, paraType, orderType);
			std::cout << "Set File Attribute : " << _order[1]  << " to " << orderType << std::endl;
			return true;
		}
	}
	std::cout << "# ERROR : File Is Not Existing" << std::endl;
	return false;

}

bool shOperatingSystem::compareFile(std::string _file1, std::string _file2) {
	int temp_folder_index = getFolderIndex(currentPath);
	bool found1 = false;
	bool found2 = false;
	std::string context1;
	std::string context2;
	for (int i = 0; i < folderVector[temp_folder_index].getFileNum(); ++i) {
		if (_file1 == folderVector[temp_folder_index].getFileName(i)) {
			context1 = folderVector[temp_folder_index].getFileContext(i);
			found1 = true;
		}
		if (_file2 == folderVector[temp_folder_index].getFileName(i)) {
			context2 = folderVector[temp_folder_index].getFileContext(i);
			found2 = true;
		}
		if (found1 && found2) {
			break;
		}
	}
	if (!found1) {
		std::cout << " #ERROR : File " << _file1 << " Is Not Existing" << std::endl;
	} else if (!found2) {
		std::cout << " #ERROR : File " << _file2 << " Is Not Existing" << std::endl;
	}
	if (!found1 || !found2) {
		return false;
	}
	bool isSame = true;
	int temp_len = context1.size() > context2.size() ? (int)context2.size() : (int)context1.size();
	for (int i = 0; i < temp_len; ++i) {
		if (context1[i] != context2[i]) {
			std::cout << "Difference : " << std::endl;
			std::cout << "Position : " << i << std::endl;
			std::cout << "Character : " << context1[i] << " - " << context2[i] << std::endl;
			return true;
		}
	}
	if (context1.size() == context2.size()) {
		std::cout << "File Contexts Match" << std::endl;
		return true;
	}
	if (temp_len == context1.size()) {
		std::cout << "Difference : " << std::endl;
		std::cout << "Position : " << temp_len + 1 << std::endl;
		std::cout << "Character : " << "NONE" << " - " << context2[temp_len+1] << std::endl;
	} else if (temp_len == context2.size()) {
		std::cout << "Difference : " << std::endl;
		std::cout << "Position : " << temp_len + 1 << std::endl;
		std::cout << "Character : " << context2[temp_len + 1] << " - " << "NONE "<< std::endl;
	}
	return true;
}

bool shOperatingSystem::replaceFile(std::string _fileName, std::string _path) {
	int folder_index = getFolderIndex(currentPath);
	shFile temp_file;
	bool isFile1 = false;
	bool isFile2 = false;
	for (int i = 0; folderVector[folder_index].getFileNum(); ++i) {
		if (_fileName == folderVector[folder_index].getFileName(i)) {
			isFile1 = true;
			temp_file = folderVector[folder_index].getFile(i);
			break;
		}
	}
	if (!isFile1) {
		std::cout << "# ERROR : File " << _fileName << " Is Not Existing At Current Folder" << std::endl;
		return false;
	}
	shAbsolutePath temp_path(_path);
	if (!findAddress(temp_path)) {
		std::cout << "# ERROR : Ilegal Path : ";
		temp_path.dispPath(); std::cout << std::endl;
		return false;
	}
	folder_index = getFolderIndex(_path);
	for (int i = 0; i < folderVector[folder_index].getFileNum(); ++i) {
		if (_fileName == folderVector[folder_index].getFileName(i)) {
			isFile2 = true;
			bool isContinue = true;
			if (folderVector[folder_index].getFileAttribute(i, 0)) {
				std::cout << "% Read-Only File : Enter 1/0 To Continue Or Not" << std::endl;
				std::cin >> isContinue;
				if (isContinue) {
					std::cout << "$ File Replacement Sicceed" << std::endl;
					folderVector[folder_index].setFile(i, temp_file);
				} else {
					std::cout << "# ERROR : Operation - Replace Terminated By User" << std::endl;
					return false;
				}
			}
			if (folderVector[folder_index].getFileAttribute(i, 1) || folderVector[folder_index].getFileAttribute(i, 2)) {
				std::cout << "# ERROR : Hiden File Or System File Can Not Be Replaced" << std::endl;
				return false;
			}
			std::cout << "$ File Replacement Sicceed" << std::endl;
			folderVector[folder_index].setFile(i, temp_file);
			return true;
		}
	}
	if (!isFile2) {
		std::cout << "# ERROR : File " << _fileName << " Is Not Existing At Target Path" << std::endl;
		return false;
	}

}

bool shOperatingSystem::moveFile(std::string _souName, std::string _tarName) {
	int cur_folder_index = getFolderIndex(currentPath);
	int temp_file_index = -1;
	int temp_folder_index = -1;
	int subfolder_index = -1;
	int temp_target_folder_index = -1;
	//Detection Open File
	std::vector<openFilePos>::iterator itor;
	for (itor = openedFile.begin(); itor != openedFile.end(); ++itor) {
		if (_souName == folderVector[itor->folderIndex].getFileName(itor->fileIndex) && getFolderIndex(currentPath) == itor->folderIndex) {
			std::cout << "# ERROR : Can Not Move A Opened File" << std::endl;
			return false;
		}
	}
	//Find The File To Be Moved
	for (int i = 0; i < folderVector[cur_folder_index].getFileNum(); ++i) {
		if (_souName == folderVector[cur_folder_index].getFileName(i)) {
			temp_file_index = i;
		}
	}
	//If Not File  - Find The Folder To Be Moved
	int temp_subfolder_index;
	for (int i = 0; i < folderVector[cur_folder_index].getSubfolderNum(); ++i) {
		temp_subfolder_index = folderVector[cur_folder_index].getSubfolderIndex(i);
		if (_souName == folderVector[temp_subfolder_index].getFolderName()) {
			temp_folder_index = temp_subfolder_index;
			subfolder_index = i;
		}
		if (_tarName == folderVector[temp_subfolder_index].getFolderName()) {
			//std::cout << "T " << _tarName << " _ " << folderVector[temp_subfolder_index].getFolderName() << std::endl;
		//	std::cout << "INDEX : " << temp_subfolder_index << std::endl;
			temp_target_folder_index = temp_subfolder_index;
		}
	}
	//Neither File Nor Folder Found Return A Error
	if (temp_file_index == -1 && temp_folder_index == -1) {
		std::cout << " # ERROR : File Or Folder Is Not Existing" << std::endl;
		return false;
	}
	//If Not Find Target Folder - Return A Error
	if (temp_target_folder_index == -1 && temp_file_index != -1) {
		std::cout << "# ERROR : Source Folder Is Not Existing" << std::endl;
		return false;
	}

	//If Move File
	if (temp_file_index != -1) {
		//Conclude Weather Exist A File With The Same Name
		int isExistSameFile = false;
		int temp_same_file_index;
		for (int i = 0; i < folderVector[temp_target_folder_index].getFileNum(); ++i) {
			if (_souName == folderVector[temp_target_folder_index].getFileName(i)) {
			//	std::cout << temp_target_folder_index << std::endl;
				isExistSameFile = true;
				temp_same_file_index = i;
				break;
			}
		}
		//If Exist File With The Same Name ,Ask User For Choice
		if (isExistSameFile) {
			bool temp_cmd = false;
			std::cout << "% A File With The Same Name In The Folder " << _tarName << " , Enter 1/0 To Continue Or Not " << std::endl;
			std::cin >> temp_cmd;
			if (!temp_cmd) {
				std::cout << "# ERROR : Operation - Move Terminated By User" << std::endl;
			} else {
				folderVector[temp_target_folder_index].setFile(temp_same_file_index, folderVector[cur_folder_index].getFile(temp_file_index));
				folderVector[cur_folder_index].deleteFile(temp_file_index);
				std::cout << "$ Move File " << _souName << " To Folder " << _tarName << std::endl;
			}
			return true;
		} else {//If Not Exist File With The Same Name
			folderVector[temp_target_folder_index].addFile(folderVector[cur_folder_index].getFile(temp_file_index));
			folderVector[cur_folder_index].deleteFile(temp_file_index);
			std::cout << "$ Move File " << _souName << " To Folder " << _tarName << std::endl;
			return true;
		}		
	} else if(temp_folder_index != -1) {//If Move Folder Or Rename
		//Rename Folder
		if (temp_target_folder_index == -1) {
			folderVector[temp_folder_index].setFolderName(_tarName);
			std::cout << "$ Rename Folder " << _souName << " To " << _tarName << std::endl;
			return true;
		} else {//Move Folder
			//If Exist Subfolder With The Same Name
			for (int i = 0; i < folderVector[temp_target_folder_index].getSubfolderNum(); ++i) {
				temp_subfolder_index = folderVector[temp_target_folder_index].getSubfolderIndex(i);
				if (_souName == folderVector[temp_subfolder_index].getFolderName()) {
					std::cout << "# ERROR : Exist Subfolder With The Same Name" << std::endl;
					return false;
				}
			}
			//If Not Exist
			folderVector[temp_target_folder_index].addSubFolder(temp_folder_index);
			folderVector[cur_folder_index].deleteSubfolder(subfolder_index);
			folderVector[temp_folder_index].setFatherIndex(temp_target_folder_index);
			std::cout << "$ Move Folder " << _souName << " To " << _tarName << std::endl;
			return true;
		}
	} 
	std::cout << "# Unknown ERROR : Operation - Move " << std::endl;
	return false;
}


bool shOperatingSystem::createCMD() {
	//create <filename> 
	if (currentCommand.getParameterNum() == 0 || currentCommand.getParameterNum() > 2) {
		std::cout << "Illegal Command Parameter Number " << std::endl;
		return false;
	}
	std::string temp_file_name = currentCommand.getParameter(0);
	shAbsolutePath temp_path = currentPath;
	if (currentCommand.getParameterNum() == 1) {
		temp_path = currentPath;
	} else if (currentCommand.getParameterNum() == 2) {
		temp_path.setPath(currentCommand.getParameter(1));
	} 
	int temp_index = getFolderIndex(temp_path);
	shFolder temp_folder = folderVector[temp_index];
	int temp_file_num = temp_folder.getFileNum();
	for (int i = 0; i < temp_file_num; ++i) {
		if (temp_file_name == temp_folder.getFileName(i)) {
			std::cout << "A File Has The Same Name " << std::endl;
			return false;
		}
	}
	createFile(temp_file_name, temp_path);
	return true;
}

bool shOperatingSystem::openCMD() {
	if (currentCommand.getParameterNum() != 1) {
		std::cout << "# ERROR : Command Parameter Number Ilegal" << std::endl;
		return false;
	}
	openFile(currentCommand.getParameter(0));
	return true;
}

bool shOperatingSystem::readCMD() {
	if (currentCommand.getParameterNum() == 1) {
		readFile(currentCommand.getParameter(0), 0);
		return true;
	} else if (currentCommand.getParameterNum() == 2) {
		int startPos = atoi(currentCommand.getParameter(1).c_str());
		readFile(currentCommand.getParameter(0), startPos);
		return true;
	}
	std::cout << "# ERROR : Command Parameter Number Ilegal" << std::endl;
	return false;
}

bool shOperatingSystem::writeCMD() {
	if (currentCommand.getParameterNum() == 2) {
		writeFile(currentCommand.getParameter(0), currentCommand.getParameter(1), 0);
		return true;
	} else if (currentCommand.getParameterNum() == 3) {
		int startPos = atoi(currentCommand.getParameter(2).c_str());
		writeFile(currentCommand.getParameter(0), currentCommand.getParameter(1), startPos);
		return true;
	}
	std::cout << "# ERROR : Command Parameter Number Ilegal" << std::endl;
	return false;
}

bool shOperatingSystem::closeCMD() {
	if (currentCommand.getParameterNum() > 1) {
		std::cout << "# ERROR : Command Parameter Number Ilegal" << std::endl;
		return false;
	}
	if (currentCommand.getParameterNum() == 1) {
		closeFile(currentCommand.getParameter(0));
	}
	if (currentCommand.getParameterNum() == 0) {
		closeFile("#c");
	}
	return true;
}

bool shOperatingSystem::closeAllCMD() {
	return true;
}

bool shOperatingSystem::delCMD() {
	return true;
}

bool shOperatingSystem::unDelCMD() {
	return true;
}

bool shOperatingSystem::copyCMD() {
	if (currentCommand.getParameterNum() != 2) {
		std::cout << "# ERROR : Command Parameter Numebr Ilegal" << std::endl;
		return false;
	}
	copyFile(currentCommand.getParameter(0), currentCommand.getParameter(1));
	return true;
}

bool shOperatingSystem::dirCMD() {
	if (currentCommand.getParameterNum() < 0 || currentCommand.getParameterNum() > 1) {
		std::cout << "Illegal Command Parameter Number" << std::endl;
		return false;
	}
	shFolder temp_folder;
	shAbsolutePath temp_path;
	if (currentCommand.getParameterNum() == 0) {
		temp_folder = folderVector[getFolderIndex(currentPath)];
	}
	if (currentCommand.getParameterNum() == 1) {
		temp_path.setPath(currentCommand.getParameter(0));
		if (!temp_path.checkPath()) {
			std::cout << "Illegal Path" << std::endl;
			return false;
		}
		if (!findAddress(temp_path)) {
			std::cout << "No Such Path" << std::endl;
			return false;
		}
		temp_folder = folderVector[getFolderIndex(temp_path)];
	}
	int subfolderNum = temp_folder.getSubfolderNum();
	int fileNum = temp_folder.getFileNum();
	std::cout << "folder : " << std::endl;
	for (int i = 0; i < subfolderNum; ++i) {
		std::cout << folderVector[temp_folder.getSubfolderIndex(i)].getFolderName() << std::endl;
	}
	std::cout << "file : " << std::endl;
	for (int i = 0; i < fileNum; ++i) {
		std::cout << temp_folder.getFileName(i) << std::endl;
	}
	return true;
}

bool shOperatingSystem::cdCMD() {
	//cd <pathName>	
	shAbsolutePath temp_Path;
	if (currentCommand.getParameterNum() == 0) {
		std::cout << "Current Path : ";
		currentPath.dispPath(); std::cout << std::endl;
		return true;
	}

	if (currentCommand.getParameterNum()  != 1) {
		std::cout << "Illegal Parameter Number" << std::endl;
		return false;
	}
	if (currentCommand.getParameter(0)[0] != '/') {
		int temp_index = getFolderIndex(currentPath);
		shFolder temp_folder = folderVector[temp_index];
		int subfolder_num = temp_folder.getSubfolderNum();
		for (int i = 0; i < subfolder_num; ++i) {
			if (currentCommand.getParameter(0) == folderVector[temp_folder.getSubfolderIndex(i)].getFolderName()) {
				currentPath.addAddress(currentCommand.getParameter(0));
				return true;
			}
		}
		std::cout << "No Such Subfolder" << std::endl;
		return false;
	}
	temp_Path.setPath(currentCommand.getParameter(0));
/*temp_Path.dispPath(); std::cout << std::endl;*/
	if (temp_Path.checkPath()) {
		if (findAddress(temp_Path)) {
			currentPath = temp_Path;
//std::cout << "IN CD" << std::endl;
			return true;
		} else {
			std::cout << "No Such Path" << std::endl;
		}
	} else {
		std::cout << "Illegal Path" << std::endl;
	}
	return false;
}

bool shOperatingSystem::mdCMD() {
	std::string attribType;
	if (currentCommand.getParameterNum() == 1) {
		attribType = "";
	} else if (currentCommand.getParameterNum() == 2) {
		attribType = currentCommand.getParameter(1);
//		shAbsolutePath temp_path(currentCommand.getParameter(1));
////std::cout << currentCommand.getParameter(1) << std::endl;
//		if (!temp_path.checkPath()) {
//			std::cout << "# ERROR : Illegal Path" << std::endl;
//			return false;
//		}
//		if (!findAddress(temp_path)) {
//			std::cout << "# ERROR : No Such Path" << std::endl;
//			return false;
//		}
//		if (createFolder(currentCommand.getParameter(0), temp_path , attribType)) {
//			std::cout << "$ Create Folder : " << currentCommand.getParameter(0) << std::endl;
//			return true;
//		} else {
//			std::cout << "# ERROR : Create Folder Failed" << std::endl;
//			return false;
//		}
	} else {
		std::cout << "# ERROR : Command Parameter Ilegal" << std::endl;
		return false;
	}
	createFolder(currentCommand.getParameter(0), attribType);
	return true;
}

bool shOperatingSystem::rdCMD() {
	if (currentCommand.getParameterNum() != 1) {
		std::cout << "Illegal Command Parameter Number" << std::endl;
		return false;
	}
	deleteFolder(currentCommand.getParameter(0));
	return true;
}

bool shOperatingSystem::typeCMD() {
	return true;
}

bool shOperatingSystem::renCMD() {
	if (currentCommand.getParameterNum() == 2) {
		renameFile(currentCommand.getParameter(0), currentCommand.getParameter(1));
		return true;
	}
	std::cout << "# ERROR : Command Parameter Number Ilegal" << std::endl;
	return false;
}

bool shOperatingSystem::attribCMD() {
	if (currentCommand.getParameterNum() != 2) {
		std::cout << "# ERROR : Command Parameter Number Ilegal" << std::endl;
		return false;
	}
	changeAttribute(currentCommand.getParameter(0), currentCommand.getParameter(1));
	return true;
}

bool shOperatingSystem::uofCMD() {
	return true;
}

bool shOperatingSystem::helpCMD() {
	return true;
}

bool shOperatingSystem::exitCMD() {
	isRunning = false;
	return true;
}

bool shOperatingSystem::fcCMD() {
	if (currentCommand.getParameterNum() != 2) {
		std::cout << "# ERROR : Command Parameter Ilegal" << std::endl;
		return false;
	} 
	compareFile(currentCommand.getParameter(0), currentCommand.getParameter(1));
	return true;
}

bool shOperatingSystem::replaceCMD() {
	if (currentCommand.getParameterNum() != 2) {
		std::cout << "# ERROR : Command Parameter Ilegal" << std::endl;
		return false;
	}
	replaceFile(currentCommand.getParameter(0), currentCommand.getParameter(1));
	return true;
}

bool shOperatingSystem::moveCMD() {
	if (currentCommand.getParameterNum() != 2) {
		std::cout << "# ERROR : Command Parameter Ilegal" << std::endl;
		return false;
	}
	moveFile(currentCommand.getParameter(0), currentCommand.getParameter(1));
	return true;
}

bool shOperatingSystem::findAddress(shAbsolutePath temp_path) {
	if (getFolderIndex(temp_path) != -1) {
		return true;
	} else {
		return false;
	}
}
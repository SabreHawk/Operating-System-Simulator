// My_OperatingSystem_Simulator_Project.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <string>
#include <iostream>
//
//#include "shAbsolutePath.h"
//#include "shFolder.h"
#include "shOperatingSystem.h"
#include "shCommand.h"
using namespace std;

void testFunction();
int main()
{
	shOperatingSystem test_OS;
	test_OS.launchSystem();
	testFunction();

    return 0;
}

void testFunction() {
	/*string temp_str = "cd /root";
	shCommand temp_cmd(temp_str);
	cout << temp_cmd.getParameterNum()<< endl;
	temp_cmd.dispCommand();*/
	//string temp_str = "/c/abc";
	//shAbsolutePath temp_path(temp_str);
	//temp_path.dispPath();
	
	/*test_OS.createFolder("test", temp_path);

	string temp_comd = "cf temp";
	shCommand temp_Comd(temp_comd);
	temp_Comd.dispCommand();*/

	system("PAUSE");
}


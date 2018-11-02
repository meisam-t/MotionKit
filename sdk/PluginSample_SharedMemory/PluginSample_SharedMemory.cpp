#include "stdafx.h"
#include "plugin.h"
#include "map_acs.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Fileio.h"
#include <ctime>
#include <chrono>
#include <thread>
#include <concrt.h>
#include <wmp.h>
#include <atlbase.h>
#include <atlwin.h>

using namespace std;

namespace Plugin
{
	string initfile(int s);
	HANDLE hMapping;
	SPageFilePhysics* physicsData;
	std::fstream fs;
	std::string isway;
	std::string ipitch;
	std::string iroll;
	std::string isurge;
	std::string itime;
	std::string ibrake;
	std::string iaccel;
	std::string ispeed;
	bool flagSpeedSwitch = 0;
	bool flagRunning = 0;
	HWND TextBox;
	bool select;
	Fileio filevk;
	int selectflag = 0;
	extern string filename = "VW.csv";
	//ifstream Kfile("KYB.csv");
	ifstream Vfile("VW.csv");
	ifstream VW_File;
	//filecheck Fcheck;
	string inFilename;
	DLLEXP void __cdecl getPluginInfo(pluginInfo *info)
	{
		//Plugin::VW_File;
		info->processName = L"acs.exe, acs_pro.exe";
		info->bindTitle = L"AC KYB 2";
		info->version = L"1.0.3";
		info->manufacturer = L"AZAPA";
		info->url = L"https://www.AZAPA.CO.JP";
		info->supportConfigWindow = true;
		int msgboxID = MessageBox(
			NULL,
			L"Do you want to load KYB Data ?",
			L"Confirm Save As",
			MB_ICONQUESTION | MB_YESNO
		);
		if (msgboxID == IDYES) {
			MessageBox(TextBox, L"KYB data has been loaded", L"KYB DATA ", MB_ICONASTERISK | MB_OK);
			select = TRUE;
			selectflag = 0;
			//filename = file2.File_assign(0);
			filename = filevk.File_assign(0);
			//filename = initfile(0);
			VW_File.open(filename);
			


		}
		else if (msgboxID == IDNO) {
			MessageBox(TextBox, L"VM data has been loaded", L"VW DATA ", MB_OK);
			select = FALSE;
			selectflag = 1;
			filename = filevk.File_assign(1);
			//filename = initfile(1);
			VW_File.open(filename);
			
			
		}
		return;
	}

	DLLEXP void initialize()
	{
		fs.open("copy_test.csv", std::fstream::in | std::fstream::out | std::fstream::trunc);
		//ifstream ifile(filename);
		TCHAR szNamePyshics[] = TEXT("Local\\acpmf_physics");
		hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFilePhysics), szNamePyshics);
		physicsData = (SPageFilePhysics*)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, sizeof(SPageFilePhysics));
		return;
	}

	DLLEXP void shutdown()
	{
		UnmapViewOfFile(physicsData);
		CloseHandle(hMapping);
		return;
	}

	DLLEXP void __cdecl update(float delta, pluginData *data)
	{
		
	/*	if (physicsData->speedKmh < 10)
		{
			flagSpeedSwitch = 1;
		}*/
	
			fs << " beginning of while" << endl;
			while (VW_File.good()) {
				getline(VW_File, iroll, ',');  // read line collumn 1
				getline(VW_File, ipitch, '\n'); // read line ,  collumn 2
				//float Fsurge = stof(isurge);
				//float Fsway = stof(isway);
				float Froll = stof(iroll); // converting to float
				float Fpitch = stof(ipitch); // converting to float
				data->surge = 0;
				data->sway = 0;
				data->roll = Froll;  // injecting the roll data
				data->pitch = Fpitch; // injecting the pitch data
				fs << iroll << "," << ipitch << endl; // write a test file
				//Sleep(2); // sleep for 20 milliseconds
				Concurrency::wait(2);
			}
			fs << " END of while " << endl;
			inFilename = filevk.File_assign(0);
			VW_File.clear();
			VW_File.seekg(0, ios::beg);

		return;
	}
	 string initfile(int s) {
		string KYBfile = "KYB.csv";
		string VWfile = "VW.csv";
		VW_File.close();
		VW_File.clear();
		fs << "Init file ";
		if (s == 0)
		{
			fs << " s = 0";
			ifstream VW_File(KYBfile);
			return KYBfile;
		}
		if (s == 1)
		{
			fs << " s = 1";
			ifstream VW_File(VWfile);
			return VWfile;
		}
	}

	DLLEXP void openConfigWindow()
	{
		//TextBox = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
		string answer;
		MessageBox(NULL, L"Config feature does not supported.", L"Error - SharedMemory", MB_OK);
		answer=MessageBox(NULL, L"Choose Yes or No",L"MessageBox",MB_YESNO | MB_ICONQUESTION);
		return;
	}
}

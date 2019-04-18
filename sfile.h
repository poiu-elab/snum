#ifndef SFILE_H
#define SFILE_H
#include <iostream>
#include <Windows.h>
#include <WinBase.h>
#include <string>
#include "sdata.h"

#define BAD_POS 0xFFFFFFFF
#define SUCCESS 0
#define LINE_MAX_LEN 100
using namespace std;

typedef DWORD MMF_SHARE_MODE;
typedef DWORD MMF_ACCESS_MODE;
typedef DWORD MMF_FLAGS;

enum RUN_MODE {DEBUG, RUN};

class sfile {
private:
	char* mbuf;
	HANDLE mmhandle; // �ļ����
	HANDLE mmfm; // �ļ�ӳ��
	char* mmfm_base_address; // �ڴ�ӳ���ַ

	DWORD createFile();
	DWORD createFileMapping();
	void printError(char* errorType, DWORD errorMsg) {
		cout << errorType << errorMsg << endl;
	}

public:
	char* filename;
	RUN_MODE runMode;

	sfile() {}
	~sfile() {
		UnmapViewOfFile(this->mmfm_base_address);
		CloseHandle(this->mmfm);
		CloseHandle(this->mmhandle);
	}

	string init();
	//sfile(const char *filename, RUN_MODE runMode);
	
	 sdata readLine();
	 double* readLine(int n);
};
#endif //SFILE_H
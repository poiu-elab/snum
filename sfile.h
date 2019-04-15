#ifndef SFILE_H
#define SFILE_H
#include <iostream>
#include <Windows.h>
#include <WinBase.h>
#include <string>

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
	HANDLE mmhandle; // 文件句柄
	HANDLE mmfm; // 文件映射
	char* mmfm_base_address; // 内存映射地址
	RUN_MODE runMode = RUN;

	DWORD createFile();
	DWORD createFileMapping();
	void printError(char* errorType, DWORD errorMsg) {
		cout << errorType << errorMsg << endl;
	}

public:
	sfile();
	~sfile() {
		UnmapViewOfFile(this->mmfm_base_address);
		CloseHandle(this->mmfm);
		CloseHandle(this->mmhandle);
	}

	string init();
	char* filename;
	//sfile(const char *filename, RUN_MODE runMode);
	
	char* readLine();
};
#endif //SFILE_H
#include "sfile.h"

string sfile::init() {
	DWORD errorCode = createFile();
	if (NULL != errorCode) {
		printError("failed to create file handler:", errorCode);
		return "failed to create file handler";
	} else if (this->runMode == DEBUG)
		cout << "create mmf handle successfully" << endl;
	errorCode = createFileMapping();
	if (NULL != errorCode) {
		printError("failed to create file mapping:", errorCode);
		return "failed to create file mapping";
	}
	else if (this->runMode == DEBUG)
		cout << "create file mapping successfully" << endl;
	// ÆäËû¼ì²é
	return "";
}

DWORD sfile::createFile() {
	MMF_ACCESS_MODE access_mode = GENERIC_READ;
	MMF_SHARE_MODE share_mode = FILE_SHARE_READ;
	MMF_FLAGS flags = FILE_FLAG_SEQUENTIAL_SCAN;
	DWORD error_code;
	this->mmhandle = CreateFile(this->filename, access_mode, share_mode,
		NULL, OPEN_ALWAYS, flags, NULL);
	if (this->mmhandle == INVALID_HANDLE_VALUE) {
		error_code = GetLastError();
		return error_code;
	}
	DWORD high_size;
	DWORD file_size = GetFileSize(this->mmhandle, &high_size);
	if (file_size == BAD_POS && (error_code = GetLastError()) != SUCCESS) {
		CloseHandle(this->mmhandle);
		return error_code;
	}
	return NULL;
}

DWORD sfile::createFileMapping() {
	DWORD size_high = 0;
	this->mmfm = CreateFileMapping(this->mmhandle, NULL, PAGE_READONLY,
		0, 0, filename);
	DWORD error_code = GetLastError();
	if (SUCCESS != error_code)
		return error_code;
	if (this->mmfm == NULL) {
		if (this->mmhandle != INVALID_HANDLE_VALUE)
			CloseHandle(this->mmhandle);
		return error_code;
	}
	DWORD view_access = FILE_MAP_READ;
	this->mmfm_base_address = (char*)MapViewOfFile(this->mmfm, view_access, 0, 0, 0);
	if (this->mmfm_base_address == NULL) {
		error_code = GetLastError();
		if (error_code != SUCCESS)
			return error_code;
		else
			return error_code;
	}
	return NULL;
}

sdata sfile::readLine() {
	int len = 0, index = 0, sign = 1;
	sdata out;
	int curNum = 0;
	char curChar;
	while (len < LINE_MAX_LEN && *(this->mmfm_base_address + len) != '\n'
		&& *(this->mmfm_base_address + len)!= '\r') {
		if (*(this->mmfm_base_address + len) == ' ') {
			curNum *= sign;
			switch (index) {
				case 0: out.a = (curNum / 2048.0); break;
				case 1: out.b = (curNum / 2048.0); break;
				case 2: out.c = (curNum / 2048.0); break;
				case 3: out.d = curNum; break;
				case 4: out.e = curNum; break;
				default:break;
			}
			index++;
			curNum = 0;
			len++;
			sign = 1;
			continue;
		}
		curChar = *(this->mmfm_base_address + len);
		if (curChar == '-') {
			sign = -1;
		} else {
			curNum = curNum * 10 + (curChar- '0');
		}
		len++;
	}
	out.e = curNum;
	this->mmfm_base_address += len;
	while (*this->mmfm_base_address == '\n' || *this->mmfm_base_address == '\r'
		|| *this->mmfm_base_address == ' ') {
		this->mmfm_base_address++;
	}
	return out;
}
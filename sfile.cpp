#include "sfile.h"

sfile::sfile() {}

string sfile::init(const char *filename, RUN_MODE runMode) {
	this->filename = filename;
	this->runMode = runMode;
	DWORD errorCode = createFile();
	if (NULL != errorCode)
		printError("创建文件失败:", errorCode);
	else if (this->runMode == DEBUG)
		cout << "create mmf handle successfully" << endl;
	errorCode = createFileMapping();
	if (NULL != errorCode)
		printError("创建映射失败:", errorCode);
	else if (this->runMode == DEBUG)
		cout << "create file mapping successfully" << endl;
	// 其他检查
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

char* sfile::readLine() {
	int len = 0;
	char *out;
	while (len < LINE_MAX_LEN && *(this->mmfm_base_address + len) != '\n') {
		*(out + len) = *(this->mmfm_base_address + len);
		len++;
	}
	*(out + len) = '\0';
	return out;
}
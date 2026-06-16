#pragma once

#include "../Dacom/Dacom.hpp"
#include "FLCore/Dacom/IdaComponent.hpp"

#define SERIALMETHOD(method) LONG __stdcall method(void* lpContext = 0)

typedef struct IFileSystem* LPFILESYSTEM;
typedef long (__stdcall IFileSystem::*DAFILE_SERIAL_PROC)(void* lpContext);

#define CLSID_FileSystem "FileSystem"
#define IID_IFileSystem  DACOM_MAKE_IID("IFileSystem")

struct DAFILEDESC : public DACOMDESC
{
    LPCSTR lpImplementation;
    LPCSTR lpFileName;
    DWORD dwDesiredAccess;
    DWORD dwShareMode;
    LPSECURITY_ATTRIBUTES lpSecurityAttributes;
    DWORD dwCreationDistribution;
    DWORD dwFlagsAndAttributes;
    HANDLE hTemplateFile;
    LPFILESYSTEM lpParent;
    HANDLE hParent;
    HANDLE hFindFirst;

    DAFILEDESC(const char* _file_name = NULL, const char* _interface_name = CLSID_FileSystem)
        : DACOMDESC(_interface_name), lpImplementation(), lpFileName(_file_name),
          dwDesiredAccess(GENERIC_READ), dwShareMode(FILE_SHARE_READ), lpSecurityAttributes(),
          dwCreationDistribution(OPEN_EXISTING),
          dwFlagsAndAttributes(FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN), hTemplateFile(),
          lpParent(), hParent(), hFindFirst(INVALID_HANDLE_VALUE)
    {
        size = sizeof(*this);
    }
};
static_assert(sizeof(DAFILEDESC) == 52);

struct DACOM_NO_VTABLE IFileSystem : public IComponentFactory
{
    // *** IDAComponent methods ***

    DACOM_DEFMETHOD(QueryInterface)(const char* interface_name, void** instance) = 0;
    DACOM_DEFMETHOD_(u32, AddRef)(void) = 0;
    DACOM_DEFMETHOD_(u32, Release)(void) = 0;

    // *** IComponentFactory methods ***

    DACOM_DEFMETHOD(CreateInstance)(DACOMDESC* descriptor, void** instance) = 0;

    //
    // *** IFileSystem methods ***
    // Note: Windows types used below for optimum compatibility with Win32 file system API calls
    //

    DACOM_DEFMETHOD_(BOOL, CloseHandle)(HANDLE handle) = 0;
    DACOM_DEFMETHOD_(BOOL, ReadFile)(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,
                                     LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped = 0) = 0;
    DACOM_DEFMETHOD_(BOOL, WriteFile)(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite,
                                      LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped = 0) = 0;
    DACOM_DEFMETHOD_(BOOL, GetOverlappedResult)(HANDLE hFile, LPOVERLAPPED lpOverlapped,
                                                LPDWORD lpNumberOfBytesTransferred, BOOL bWait) = 0;
    DACOM_DEFMETHOD_(DWORD, SetFilePointer)(HANDLE hFile, LONG lDistanceToMove,
                                            PLONG lpDistanceToMoveHigh = 0,
                                            DWORD dwMoveMethod = FILE_BEGIN) = 0;
    DACOM_DEFMETHOD_(BOOL, SetEndOfFile)(HANDLE hFile = 0) = 0;
    DACOM_DEFMETHOD_(DWORD, GetFileSize)(HANDLE hFile = 0, LPDWORD lpFileSizeHigh = 0) = 0;
    DACOM_DEFMETHOD_(BOOL, LockFile)(HANDLE hFile, DWORD dwFileOffsetLow, DWORD dwFileOffsetHigh,
                                     DWORD nNumberOfBytesToLockLow, DWORD nNumberOfBytesToLockHigh) = 0;
    DACOM_DEFMETHOD_(BOOL, UnlockFile)(HANDLE hFile, DWORD dwFileOffsetLow, DWORD dwFileOffsetHigh,
                                       DWORD nNumberOfBytesToUnlockLow, DWORD nNumberOfBytesToUnlockHigh) = 0;
    DACOM_DEFMETHOD_(BOOL, GetFileTime)(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime,
                                        LPFILETIME lpLastWriteTime) = 0;
    DACOM_DEFMETHOD_(BOOL, SetFileTime)(HANDLE hFile, CONST FILETIME* lpCreationTime,
                                        CONST FILETIME* lpLastAccessTime,
                                        CONST FILETIME* lpLastWriteTime) = 0;
    DACOM_DEFMETHOD_(HANDLE, CreateFileMapping)(HANDLE hFile = 0,
                                                LPSECURITY_ATTRIBUTES lpFileMappingAttributes = 0,
                                                DWORD flProtect = PAGE_READONLY, DWORD dwMaximumSizeHigh = 0,
                                                DWORD dwMaximumSizeLow = 0, LPCTSTR lpName = 0) = 0;
    DACOM_DEFMETHOD_(LPVOID, MapViewOfFile)(HANDLE hFileMappingObject, DWORD dwDesiredAccess = FILE_MAP_READ,
                                            DWORD dwFileOffsetHigh = 0, DWORD dwFileOffsetLow = 0,
                                            DWORD dwNumberOfBytesToMap = 0) = 0;
    DACOM_DEFMETHOD_(BOOL, UnmapViewOfFile)(LPCVOID lpBaseAddress) = 0;
    DACOM_DEFMETHOD_(HANDLE, FindFirstFile)(LPCTSTR lpFileName, LPWIN32_FIND_DATA lpFindFileData) = 0;
    DACOM_DEFMETHOD_(BOOL, FindNextFile)(HANDLE hFindFile, LPWIN32_FIND_DATA lpFindFileData) = 0;
    DACOM_DEFMETHOD_(BOOL, FindClose)(HANDLE hFindFile) = 0;
    DACOM_DEFMETHOD_(BOOL, CreateDirectory)(LPCTSTR lpPathName,
                                            LPSECURITY_ATTRIBUTES lpSecurityAttributes = 0) = 0;
    DACOM_DEFMETHOD_(BOOL, RemoveDirectory)(LPCTSTR lpPathName) = 0;
    DACOM_DEFMETHOD_(DWORD, GetCurrentDirectory)(DWORD nBufferLength, LPTSTR lpBuffer) = 0;
    DACOM_DEFMETHOD_(BOOL, SetCurrentDirectory)(LPCTSTR lpPathName) = 0;
    DACOM_DEFMETHOD_(BOOL, DeleteFile)(LPCTSTR lpFileName) = 0;
    DACOM_DEFMETHOD_(BOOL, CopyFile)(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName,
                                     BOOL bFailIfExists) = 0;
    DACOM_DEFMETHOD_(BOOL, MoveFile)(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName) = 0;
    DACOM_DEFMETHOD_(DWORD, GetFileAttributes)(LPCTSTR lpFileName) = 0;
    DACOM_DEFMETHOD_(BOOL, SetFileAttributes)(LPCTSTR lpFileName, DWORD dwFileAttributes) = 0;
    DACOM_DEFMETHOD_(DWORD, GetLastError)(void) = 0;

    //---------------
    // IFileSystem extensions to WIN32 system
    //---------------

    DACOM_DEFMETHOD_(HANDLE, OpenChild)(DAFILEDESC* lpDesc) = 0;
    DACOM_DEFMETHOD_(DWORD, GetFilePosition)(HANDLE hFile = 0, PLONG pPositionHigh = 0) = 0;
    DACOM_DEFMETHOD_(LONG, GetFileName)(LPSTR lpBuffer, LONG lBufferSize) = 0;
    DACOM_DEFMETHOD_(DWORD, GetAccessType)(void) = 0;
    DACOM_DEFMETHOD(GetParentSystem)(LPFILESYSTEM* lplpFileSystem) = 0;
    DACOM_DEFMETHOD(SetPreference)(DWORD dwNumber, DWORD dwValue) = 0;
    DACOM_DEFMETHOD(GetPreference)(DWORD dwNumber, PDWORD pdwValue) = 0;
    DACOM_DEFMETHOD(ReadDirectoryExtension)(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,
                                            LPDWORD lpNumberOfBytesRead = 0, DWORD dwStartOffset = 0) = 0;
    DACOM_DEFMETHOD(WriteDirectoryExtension)(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite,
                                             LPDWORD lpNumberOfBytesWritten = 0, DWORD dwStartOffset = 0) = 0;
    DACOM_DEFMETHOD_(LONG, SerialCall)(LPFILESYSTEM lpSystem, DAFILE_SERIAL_PROC lpProc, void* lpContext) = 0;
    DACOM_DEFMETHOD_(BOOL, GetAbsolutePath)(char* lpOutput, LPCTSTR lpInput, LONG lSize) = 0;
};

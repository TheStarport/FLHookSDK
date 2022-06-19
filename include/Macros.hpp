#pragma once

#ifndef DLL
	#ifndef FLHOOK
		#define DLL __declspec(dllimport)
	#else
		#define DLL __declspec(dllexport)
	#endif
#endif

#ifndef FLHOOK
	#define EXTERN extern
#else
	#define EXTERN
#endif

#define HKHKSUCCESS(a) ((a) == HKE_OK)
#define HKSUCCESS(a) ((hkLastErr = (a)) == HKE_OK)

#define SRV_ADDR(a) ((char*)hModServer + (a))
#define DALIB_ADDR(a) ((char*)hModDaLib + (a))
#define FLSERVER_ADDR(a) ((char*)hProcFL + (a))
#define CONTENT_ADDR(a) ((char*)hModContent + (a))

#ifndef DISABLE_EXTENDED_EXCEPTION_LOGGING
	#pragma warning(disable : 4091)
	#include <DbgHelp.h>

struct SEHException
{
	SEHException(uint code, EXCEPTION_POINTERS* ep) : code(code), record(*ep->ExceptionRecord), context(*ep->ContextRecord) {}

	SEHException() = default;

	uint code;
	EXCEPTION_RECORD record;
	CONTEXT context;

	static void Translator(uint code, EXCEPTION_POINTERS* ep) { throw SEHException(code, ep); }
};

DLL void WriteMiniDump(SEHException* ex);
DLL void AddExceptionInfoLog();
DLL void AddExceptionInfoLog(SEHException* ex);
	#define TRY_HOOK \
		try          \
		{            \
			_set_se_translator(SEHException::Translator);
	#define CATCH_HOOK(e)                                                                                                                \
		}                                                                                                                                \
		catch (SEHException & ex)                                                                                                        \
		{                                                                                                                                \
			e;                                                                                                                           \
			AddBothLog(L"ERROR: SEH Exception in %s on line %d; minidump may contain more information.", stows(__FUNCTION__), __LINE__); \
			AddExceptionInfoLog(&ex);                                                                                                    \
		}                                                                                                                                \
		catch (std::exception & ex)                                                                                                      \
		{                                                                                                                                \
			e;                                                                                                                           \
			AddBothLog(L"ERROR: STL Exception in %s on line %d: %s.", stows(__FUNCTION__), __LINE__, stows(ex.what()));                  \
			AddExceptionInfoLog(0);                                                                                                      \
		}                                                                                                                                \
		catch (...)                                                                                                                      \
		{                                                                                                                                \
			e;                                                                                                                           \
			AddBothLog(L"ERROR: Exception in %s on line %d.", stows(__FUNCTION__), __LINE__);                                            \
			AddExceptionInfoLog(0);                                                                                                      \
		}

	#define LOG_EXCEPTION                                  \
	{                                                  \
		AddLog(LogType::Normal, LogLevel::Err, L"ERROR Exception in %s", stows(__FUNCTION__).c_str()); \
		AddExceptionInfoLog();                         \
	}
#else
	#define TRY_HOOK try
	#define CATCH_HOOK(e)                                                                            \
		catch (...)                                                                                  \
		{                                                                                            \
			e;                                                                                       \
			AddLog(LogType::Normal, LogLevel::Info, L"ERROR: Exception in %s", stows(__FUNCTION__)); \
		}
#endif

#define GetPluginClientData(id, info) ((&ClientInfo[(id)])->mapPluginData[(info)].data())

#define HkFunc(Func, clientId, ...)                                      \
	{                                                                    \
		if (HK_ERROR err; (err = Func(clientId, __VA_ARGS__)) != HKE_OK) \
		{                                                                \
			std::wstring errorString = HkErrGetText(err);                \
			PrintUserCmdText(clientId, L"ERR:" + errorString);           \
			return;                                                      \
		}                                                                \
	}

#define DefaultUserCmdHook(commands, returnCode) \
[](uint& clientId, const std::wstring& wscParam) { return DefaultUserCommandHandling(clientId, wscParam, UserCmds, returnCode); }
//////////////////////////////////////////////////////////////////////
//	Project FLCoreSDK v1.1, modified for use in FLHook Plugin version
//--------------------------
//
//	File:			FLCoreDALib.h
//	Module:			FLCoreDALib.lib
//	Description:	Interface to DALib.dll
//
//	Web: www.skif.be/flcoresdk.php
//
//
//////////////////////////////////////////////////////////////////////
#ifndef _FLCOREDALIB_H_
#define _FLCOREDALIB_H_

#include "FLCoreDefs.hpp"
#include <vector>

// #pragma comment( lib, "FLCoreDALib.lib" )

class IMPORT CDPClient
{
  public:
    CDPClient(const CDPClient&);
    CDPClient();
    virtual ~CDPClient();
    CDPClient& operator=(const CDPClient&);
    bool AddConnectAttempt(const unsigned short*, unsigned short*);
    void CancelEnums();
    void Cleanup();
    void Close();
    void DispatchMsgs(unsigned long);
    bool EnumerateHost(const unsigned short*, unsigned long, unsigned long, unsigned long, unsigned long);
    bool EnumerateHosts();
    struct IDirectPlay8Client* GetClient();
    long GetConnectResult();
    static unsigned long __cdecl GetLastMsgTimestamp();
    static unsigned long __cdecl GetLinkQuality();
    static unsigned long __cdecl GetPingDelay();
    static unsigned long __cdecl GetSendQueueSize();
    static bool __cdecl IsPingOutstanding();
    bool ProcessConnectAttempt();
    bool Send(unsigned char*, unsigned long);
    void SetGUID(_GUID&);
    static void __cdecl SetSourcePort(unsigned long);

  protected:
    bool ConnectToServer(const unsigned short*, const unsigned short*);
    static long __stdcall HandleClientMsg(void*, unsigned long, void*);
    static unsigned long m_dwLastMsgReceivedTime;
    static unsigned long m_dwLinkQuality;
    static unsigned long m_dwPingLastTime;
    static unsigned long m_dwPingReceiveCount;
    static unsigned long m_dwPingReceiveTime;
    static unsigned long m_dwPingSendCount;
    static unsigned long m_dwPingSendTime;
    static unsigned long m_dwRoundTripTime;
    static unsigned long m_dwSourcePort;

  public:
    unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CDPClientProxy
{
  public:
    CDPClientProxy(const CDPClientProxy&);
    CDPClientProxy();
    virtual ~CDPClientProxy();
    CDPClientProxy& operator=(const CDPClientProxy&);
    bool Disconnect();
    bool GetConnectionStats(struct _DPN_CONNECTION_INFO*);
    double GetLinkSaturation();
    unsigned int GetSendQBytes();
    unsigned int GetSendQSize();
    void OnMsgSent(unsigned long);
    bool Send(void*, unsigned long);
    bool SendMsgs();
    void UpdateQueueHistory();

  public:
    unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CDPMessage
{
  public:
    CDPMessage(const CDPMessage&);
    CDPMessage();
    virtual ~CDPMessage();
    CDPMessage& operator=(const CDPMessage&);
    unsigned char* GetData();
    const unsigned long GetSize();

  public:
    unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CDPMsgList
{
  public:
    CDPMsgList(const CDPMsgList&);
    CDPMsgList();
    virtual ~CDPMsgList();
    CDPMsgList& operator=(const CDPMsgList&);
    void Add(CDPMessage*);
    void CopyList(CDPMsgList&);
    void ExtractMsgs(unsigned long, CDPMsgList&);
    CDPMessage* GetNextMsg();
    void Lock();
    CDPMessage* PeekNextMsg();
    void SetEmptyEvent();
    void Unlock();
    void WaitForMsg(unsigned long);

  public:
    unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CDPServer
{
  public:
    CDPServer(const CDPServer&);
    CDPServer();
    virtual ~CDPServer();
    CDPServer& operator=(const CDPServer&);
    bool BeginHosting(unsigned int);
    static void __cdecl CrashCleanup();
    virtual CDPClientProxy* CreateClientProxy();
    void DisconnectClient(unsigned long);
    void DispatchMsgs();
    bool GetConnectionStats(_DPN_CONNECTION_INFO*);
    bool GetConnectionStats(CDPClientProxy*, _DPN_CONNECTION_INFO*);
    static unsigned long __cdecl GetLastMsgTimestamp();
    void GetPort(st6::vector<unsigned long>&);
    unsigned int GetSendQBytes(CDPClientProxy*);
    unsigned int GetSendQSize(CDPClientProxy*);
    bool SendTo(CDPClientProxy*, void*, unsigned long);
    bool SetEnumResponse(void*, unsigned long);
    void SetGUID(_GUID&);
    void SetMaxPlayers(int);
    void SetPassword(const unsigned short*);
    void SetSessionName(const unsigned short*);
    void StopHosting();

  protected:
    void GetHostAddresses();
    static long __stdcall HandleDPServerMsg(void*, unsigned long, void*);
    void ReleaseHostAddresses();
    void UpdateDescription();
    static unsigned long m_dwLastMsgReceivedTime;
    static CDPServer* m_pServer;

  public:
    unsigned char data[OBJECT_DATA_SIZE];
};

struct IGunConnection
{
    enum ConnectStatus
    {
    };
};

namespace Gun2
{
    struct GUNQueueMessage;
};

class IMPORT CGunWrapper
{
  public:
    CGunWrapper(const CGunWrapper&);
    CGunWrapper(const char*, _GUID&, const char*, unsigned long, unsigned short*);
    virtual ~CGunWrapper();
    CGunWrapper& operator=(const CGunWrapper&);
    void DispatchQueue();
    struct IGunBrowser* GetBrowser();
    IGunConnection* GetConnection();
    struct IGunHost* GetHost();
    IGunConnection::ConnectStatus GetStatus();
    virtual long __stdcall Read(Gun2::GUNQueueMessage*);
    static void __cdecl Shutdown();
    void Update();

  public:
    unsigned char data[OBJECT_DATA_SIZE];
};

struct IAlchemy;

enum class AnimationDirection
{
    Forwards = 0,
    Backwards = 1,
    Repeat = 2,
    Cycle = 4
};

struct AnimObject
{
    void* vtable;
    st6::map<uint, uint> map;
};

struct IAnimation2
{
    virtual void __stdcall func_00();
    virtual void __stdcall func_04();
    virtual void __stdcall func_08();
    virtual void __stdcall func_0c();
    virtual void __stdcall func_10();

    virtual float __stdcall TotalTime(long);

    virtual void __stdcall func_18();
    virtual void __stdcall func_1c();
    virtual float __stdcall GetFullAnimTime_unk(long id);

    virtual long __stdcall Open(AnimObject* animObj, long parentOrSelfIndex, LPCSTR animationName, int, int);
    virtual void __stdcall Close(long);
    virtual void __stdcall Play(long id,                      // id - Open's return value
                                AnimationDirection direction, // 1 = backwards, 2 = repeat, 4 = cycle
                                float,                        // start pos (-2 = normal, -1 = end)
                                float,                        // speed
                                float,                        // time to run (seconds)
                                float,                        // end pos
                                float,                        // unknown (apparently unused)
                                float);                       // unknown (apparently unused)

    virtual void __stdcall func_30();
    virtual void __stdcall func_34();

    virtual void __stdcall Stop(long); // flush?

    virtual void __stdcall func_3c();

    virtual float __stdcall CurrentTime(long);
};

struct IChannel;
struct ICOManager;
struct IFileSystem;
struct IDeformable;
struct IEngine2;
struct IEngine;
struct IFxEffectLibrary;
struct IFxRuntime;
struct IHardpoint;
struct IMatAnimLibrary;
struct IMaterialBatcher2;
struct IMaterialLibrary;
struct IRenderPipeline;
struct IRPDraw;
struct IRPIndexBuffer;
struct IRPVertexBuffer;
struct IRenderer2;
struct ISoundManager;
struct IStreamer2;
struct ITextureLibrary2;
struct IVMeshLibrary;
struct IVertexBufferManager;

namespace DALib
{
    IMPORT IAlchemy* Alchemy;
    IMPORT IAnimation2* Anim;
    IMPORT IChannel* Channel;
    IMPORT void __cdecl CloseData();
    IMPORT ICOManager* Dacom;
    IMPORT IFileSystem* Data;
    IMPORT IDeformable* Deform;
    IMPORT IEngine2* Engine2;
    IMPORT IEngine* Engine;
    IMPORT IFxEffectLibrary* FxEffectLibrary;
    IMPORT IFxRuntime* FxRuntime;
    IMPORT IHardpoint* Hardpoint;
    IMPORT IMatAnimLibrary* MatAnimLibrary;
    IMPORT IMaterialBatcher2* MaterialBatcher;
    IMPORT IMaterialLibrary* MaterialLib;
    IMPORT void __cdecl OpenData(const char*);
    IMPORT IRenderPipeline* Pipeline;
    IMPORT IRPDraw* RPDraw;
    IMPORT IRPIndexBuffer* RPIndexBuffer;
    IMPORT IRPVertexBuffer* RPVertexBuffer;
    IMPORT IRenderer2* Renderer;
    IMPORT void __cdecl Shutdown(HWND__*);
    IMPORT ISoundManager* Sound;
    IMPORT bool __cdecl Startup(HWND__*, const char*);
    IMPORT IStreamer2* Streamer;
    IMPORT ITextureLibrary2* TextureLib;
    IMPORT IVMeshLibrary* VMeshLibrary;
    IMPORT IVertexBufferManager* VertexBuffer;
}; // namespace DALib

class IMPORT IDPMsgHandler
{
  public:
    IDPMsgHandler(const IDPMsgHandler&);
    IDPMsgHandler();
    IDPMsgHandler& operator=(const IDPMsgHandler&);
    virtual void OnAddHost(struct _DPNMSG_ENUM_HOSTS_RESPONSE*);
    virtual void OnConnect(long);
    virtual void OnDisconnect();
    virtual void OnReceive(unsigned char*, unsigned long);

  public:
    unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT MD5Hash
{
  public:
    MD5Hash(const MD5Hash&);
    MD5Hash();
    virtual ~MD5Hash();
    MD5Hash& operator=(const MD5Hash&);
    bool AddData(void* const, unsigned long);
    const char* AsString();
    bool CalcValue();
    bool Compare(MD5Hash&);
    void FromString(const char*);
    unsigned char* GetStatePtr();

  protected:
    void Decode(unsigned long*, unsigned char*, unsigned long);
    void Encode(unsigned char*, unsigned long*, unsigned long);
    void Transform(unsigned char*);

  public:
    unsigned char data[OBJECT_DATA_SIZE];
};

IMPORT bool(__cdecl* CriticalWarningFn)(unsigned int, const char*);
IMPORT void(__cdecl* FatalErrorFn)(unsigned int, const char*);

#endif // _FLCOREDALIB_H_

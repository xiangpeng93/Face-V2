// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

#include "DetectFace.h"
#include "Recognize.h"
#include "Train.h"
#include "PersonManger.h"
#include "GroupManger.h"

enum CMDLIST{
	_CREATE,
	_DELETE,
	_ADD,
	_REMOVE,
	_PERSON,
	_GROUP
};
#if 1
#define FACEPLUS_API __declspec(dllexport)  
#else
#define FACEPLUS_API __declspec(dllimport)  
#endif

std::string g_message;

extern "C"
{
	FACEPLUS_API int testInt();
	FACEPLUS_API int testString(char *message);

	FACEPLUS_API int groupManger(int cmd, char * groupName);
	FACEPLUS_API int personManger(int cmd, char * personName, char* groupName, char * faceId);
	FACEPLUS_API int detectManger(char * url, char *result);
	FACEPLUS_API int trainManger(int cmd,char *name);
	FACEPLUS_API int recManger(int cmd, char *url, char *group, char *result);
	FACEPLUS_API int getMessage(char *message);
};
FACEPLUS_API int testInt(){
	return 0;
}

FACEPLUS_API int testString(char *message){
	memcpy(message, "222222222222222222222222221", sizeof("222222222222222222222222221"));
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		static int iResult = 0;
		static WSADATA wsaData;
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != NO_ERROR) {
			printf("WSAStartup failed: %d\n", iResult);
			return 1;
		}
	}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:

		WSACleanup();
		break;
	}
	return TRUE;
}

FACEPLUS_API int groupManger(int cmd, char * groupName)
{
	int nResult = 0;
	CGroupManger groupM(groupName);
	switch (cmd)
	{
	case _CREATE:
	{
					nResult = groupM._createGroup();
					g_message = groupM.m_recvMessage;
	}
		break;
	case _DELETE:
	{
					nResult = groupM._deleteGroup();
					g_message = groupM.m_recvMessage;
	}
		break;
	default:
		break;
	}
	return nResult;
}

FACEPLUS_API int personManger(int cmd, char * personName,char* groupName,char * faceId){
	int nResult = 0;
	CPersonManger personM(personName,groupName);
	
	switch (cmd)
	{
	case _CREATE:
	{
					nResult = personM._createPerson();
					g_message = personM.m_recvMessage;
	}
		break;
	case _DELETE:
	{
					nResult = personM._deletePerson();
					g_message = personM.m_recvMessage;
	}
		break;
	case _ADD:
	{
				 nResult = personM._addFace(faceId);
				 g_message = personM.m_recvMessage;
	}
		break;
	case _REMOVE:
	{
					nResult = personM._removeFace(faceId);
					g_message = personM.m_recvMessage;
	}
		break;
	default:
		break;
	}
	return nResult;
}

FACEPLUS_API int detectManger(char * url,char *result){
	CDetectFace detectFace(url);
	detectFace._detectFace();
	g_message = detectFace.m_recvMessage;
	memcpy(result, detectFace._getFaceId().c_str(), detectFace._getFaceId().length());
	return 0;
}

FACEPLUS_API int trainManger(int cmd, char *name)
{
	int nResult = 0;
	CTrain train;
	switch (cmd)
	{
	case _PERSON:
	{
					nResult = train._trainVerify(name);
					g_message = train.m_recvMessage;
	}
		break;
	case _GROUP:
	{
				   nResult = train._trainIdentify(name);
				   g_message = train.m_recvMessage;
	}	
		break;
	default:
		break;
	}
	return nResult;
}

FACEPLUS_API int recManger(int cmd, char *url,char *group,char *result){
	CRecognize rec;
	static std::string sResult;
	sResult = "";
	rec._identify(url, group);
	std::cout << rec._getResultRecg(GETIDENTIFYRESULT) << std::endl;
	std::cout << rec._getResultRecg(GETFACEID) << std::endl;
	sResult += rec._getResultRecg(GETIDENTIFYRESULT);
	rec._verify(rec._getResultRecg(GETFACEID), rec._getResultRecg(GETIDENTIFYRESULT));
	sResult += rec._getResultRecg(GETVERIFYRESULT);
	g_message = rec.m_recvMessage;

	memcpy(result, sResult.c_str(), sResult.length());
	return 0;
}


FACEPLUS_API int getMessage(char *message)
{
	if (!g_message.empty())
	{
		memcpy(message, g_message.c_str(), g_message.length());
		return 0;
	}
	else return -1;
}
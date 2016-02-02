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

#define FACEPLUS_API __declspec(dllexport)  
extern "C"
{
	FACEPLUS_API int testInt();
	FACEPLUS_API char* testString();

	FACEPLUS_API int groupManger(int cmd, char * groupName);
	FACEPLUS_API int personManger(int cmd, char * personName);
	FACEPLUS_API char* detectManger(char * url);
	FACEPLUS_API int trainManger(int cmd,char *name);
	FACEPLUS_API char* recManger(int cmd, char *url);


};
FACEPLUS_API int testInt(){
	return 0;
}

FACEPLUS_API char* testString(){
	return "1";
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
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
		nResult = groupM._createGroup();
		break;
	case _DELETE:
		nResult = groupM._deleteGroup();
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
		nResult = personM._createPerson();
		break;
	case _DELETE:
		nResult = personM._deletePerson();
		break;
	case _ADD:
		nResult = personM._addFace(faceId);
		break;
	case _REMOVE:
		nResult = personM._removeFace(faceId);
		break;
	default:
		break;
	}
	return nResult;
}

FACEPLUS_API char* detectManger(char * url){
	CDetectFace detectFace(url);
	detectFace._detectFace();
	return (char *)detectFace._getFaceId().c_str();
}

FACEPLUS_API int trainManger(int cmd, char *name)
{
	int nResult = 0;
	CTrain train;
	switch (cmd)
	{
	case _PERSON:
		nResult = train._trainVerify(name);
		break;
	case _GROUP:
		nResult = train._trainIdentify(name);
		break;
	default:
		break;
	}
	return nResult;
}

FACEPLUS_API char* recManger(int cmd, char *url,char *group){
	CRecognize rec;
	static char sResult[MAX_PATH] = { 0 };
	memset(sResult, 0, sizeof(sResult));
	rec._identify(url, group);
	std::cout << rec._getResultRecg(GETIDENTIFYRESULT) << std::endl;
	std::cout << rec._getResultRecg(GETFACEID) << std::endl;

	rec._verify(rec._getResultRecg(GETFACEID), rec._getResultRecg(GETIDENTIFYRESULT));
	strcpy(sResult, rec._getResultRecg(GETVERIFYRESULT));
	return sResult;
}
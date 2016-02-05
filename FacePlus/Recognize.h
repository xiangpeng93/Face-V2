#pragma once
#include "FacePlusPlusInterface.h"
#include "ParseJson.h"
enum REC_CMDLIST
{
	GETVERIFYRESULT,
	GETIDENTIFYRESULT,
	GETFACEID
};
class CRecognize :public CFacePlusPlusInterface
{
public:
	virtual int doAction_1(){ return 0; };
	virtual int doAction_2(){ return 0; };
	CRecognize();
	~CRecognize();
public:
	int _verify(std::string faceId, std::string personName);
	int _identify(std::string url, std::string groupName);
	char* _getResultRecg(int cmd);
public:
	Json::Value value;
};


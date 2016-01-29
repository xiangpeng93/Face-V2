#pragma once
#include "FacePlusPlusInterface.h"
class CDetectFace:public CFacePlusPlusInterface
{
public:
	CDetectFace(std::string detectUrl);
	~CDetectFace();
public:
	virtual int doAction_1(){ return _detectFace(); };
	virtual int doAction_2(){ return 0; };
	int _detectFace();
private:


	int _sendRequest(const char * request);
	int _recvRequest(const char * buffer);
public:
	std::string m_detectUrl;
};


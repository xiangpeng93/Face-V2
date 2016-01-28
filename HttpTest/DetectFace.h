#pragma once
#include "FacePlusPlusInterface.h"
class CDetectFace:public CFacePlusPlusInterface
{
public:
	CDetectFace();
	~CDetectFace();
public:
	int _detectFace();
private:
	int _sendRequest(const char * request);
	int _recvRequest(const char * buffer);
public:
	std::string m_personName;
	std::string m_groupName;
};


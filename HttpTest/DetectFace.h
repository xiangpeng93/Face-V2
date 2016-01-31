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
	std::string _getFaceId();
	
private:
	int _sendRequest(const char * request);
	int _recvRequest(const char * buffer);
public:
	std::string m_detectUrl;
	std::string m_revMessage;
public:
	void setDetectUrl(std::string destUrl){
		m_detectUrl.clear();
		m_revMessage.clear();
		m_detectUrl = destUrl;
	}
};


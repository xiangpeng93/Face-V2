#pragma once
#include "FacePlusPlusInterface.h"
class CDetectFace:public CFacePlusPlusInterface
{
public:
	CDetectFace();
	CDetectFace(std::string detectUrl);
	~CDetectFace();
public:
	virtual int doAction_1(){ return _detectFace(); };
	virtual int doAction_2(){ return 0; };
	int _detectFace();
	std::string _getFaceId();

public:
	std::string m_detectUrl;
public:
	void setDetectUrl(std::string destUrl){
		m_detectUrl.clear();
		m_recvMessage.clear();
		m_detectUrl = destUrl;
	}
};


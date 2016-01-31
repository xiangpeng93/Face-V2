#pragma once
#include "FacePlusPlusInterface.h"
class CTrain:public CFacePlusPlusInterface
{
public:
	CTrain();
	~CTrain();
public:
	virtual int doAction_1(){ return 0; };
	virtual int doAction_2(){ return 0; };
	int _trainVerify(std::string personName);
	int _trainIdentify(std::string guropName);
private:
	int _sendRequest(const char * request);
	int _recvRequest(const char * buffer);
public:
	std::string m_recvMessgae;
};


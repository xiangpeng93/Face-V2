#pragma once
#include "FacePlusPlusInterface.h"
class CRecognize:public CFacePlusPlusInterface
{
public:
	virtual int doAction_1(){ return 0; };
	virtual int doAction_2(){ return 0; };
	CRecognize();
	~CRecognize();
public:
	int _verify(std::string faceId,std::string personName);
	int _idefntify(std::string url, std::string groupName);

public:

};


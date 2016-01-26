#pragma once
#include "FacePlusPlusInterface.h"
class CCreateGroup : CFacePlusPlusInterface
{
public:
public:
	 int _sendRequest(char * request);
	 int _recvRequest(char * buffer);
public:
	std::string groupName;
};


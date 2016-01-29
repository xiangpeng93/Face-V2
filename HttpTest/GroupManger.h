#pragma once
#include "FacePlusPlusInterface.h"
class CGroupManger : CFacePlusPlusInterface
{
public:
	CGroupManger(std::string groupName)
	{
		m_groupName = groupName;
	}
public:
	virtual int doAction_1(){ return _createGroup(); };
	virtual int doAction_2(){ return _deleteGroup(); };
	virtual int _createGroup();
	virtual int _deleteGroup();
	virtual int _sendRequest(const char * request);
	virtual int _recvRequest(const char * buffer);
public:
	std::string m_groupName;
};


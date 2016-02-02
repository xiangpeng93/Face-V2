#pragma once
#include "FacePlusPlusInterface.h"
class CPersonManger:public CFacePlusPlusInterface
{
public:
	CPersonManger(std::string personName, std::string groupName)
	{
		m_personName = personName;
		m_groupName = groupName;
	}
	~CPersonManger(){
	};
public:
	virtual int doAction_1(){ return _createPerson(); };
	virtual int doAction_2(){ return _deletePerson(); };
	int _addFace(std::string faceId);
	int _addFace(std::string personName, std::string faceId);
	int _removeFace(std::string faceId);
	int _createPerson();
	int _createPerson(std::string personName);
	int _deletePerson();
	int _deletePerson(std::string personName);

public:
	std::string m_personName;
	std::string m_groupName;
};


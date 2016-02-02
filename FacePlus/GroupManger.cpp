#include "GroupManger.h"

//std::string CreateRequest = "/v2/group/create?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=created_by_Alice&group_name=";
//std::string DeleteRequest = "/v2/group/delete?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=created_by_Alice&group_name=";

int CGroupManger::_createGroup(){
	std::string CreateGroup = "/v2/group/create?";
	CreateGroup += "api_key=";
	CreateGroup += MY_API_KEY;
	CreateGroup += "&api_secret=";
	CreateGroup += MY_API_SECRET;
	CreateGroup += "&tag=created_by_XP";
	CreateGroup += "&group_name=";
	CreateGroup += m_groupName;

	return _sendRequest(CreateGroup.c_str());
}

int CGroupManger::_deleteGroup(){

	std::string DeleteGroup = "/v2/group/delete?";
	DeleteGroup += "api_key=";
	DeleteGroup += MY_API_KEY;
	DeleteGroup += "&api_secret=";
	DeleteGroup += MY_API_SECRET;
	DeleteGroup += "&tag=created_by_XP";
	DeleteGroup += "&group_name=";
	DeleteGroup += m_groupName;

	return _sendRequest(DeleteGroup.c_str());
}

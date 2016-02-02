#include "PersonManger.h"

std::string GroupRequest = "&group_name=";

/*
Person API to CreatePerson
https ://apicn.faceplusplus.com/v2/person/create?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=demotest&person_name=CL&group_name=AST_Family
*/
int CPersonManger::_createPerson(){
	std::string AddPersonRequest = "/v2/person/create?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=demotest&person_name=";

	AddPersonRequest += m_personName;
	AddPersonRequest += GroupRequest;
	AddPersonRequest += m_groupName;
	
	return _sendRequest(AddPersonRequest.c_str());
}

int CPersonManger::_createPerson(std::string personName){
	std::string AddPersonRequest = "/v2/person/create?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=demotest&person_name=";

	AddPersonRequest += personName;
	AddPersonRequest += GroupRequest;
	AddPersonRequest += m_groupName;

	return _sendRequest(AddPersonRequest.c_str());
}


/*
Person API to DeletePerson
https ://apicn.faceplusplus.com/v2/person/delete?api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&api_key=c499b2943a96babe258e8d4ed8098061&person_name=CL
*/

int CPersonManger::_deletePerson(){
	std::string DeletePersonRequest = "/v2/person/delete?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=demotest&person_name=";
	DeletePersonRequest += m_personName;
	DeletePersonRequest += GroupRequest;
	DeletePersonRequest += m_groupName;

	return _sendRequest(DeletePersonRequest.c_str());
}

int CPersonManger::_deletePerson(std::string personName){
	std::string DeletePersonRequest = "/v2/person/delete?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=demotest&person_name=";
	DeletePersonRequest += personName;
	DeletePersonRequest += GroupRequest;
	DeletePersonRequest += m_groupName;

	return _sendRequest(DeletePersonRequest.c_str());
}


//api_key = c499b2943a96babe258e8d4ed8098061
//api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH
//&tag=demotest&person_name=";
/*
Person API to AddFace
https://apicn.faceplusplus.com/v2/person/add_face?api_secret=YOUR_API_SECRET&face_id=1698e3320e1f75f63650e61d9e2ace53,13919c882327bdc55d7ba336e7cbf167&api_key=YOUR_API_KEY&person_name=NicolasCage
*/
int CPersonManger::_addFace(std::string faceId){
	std::string AddFaceRequest = "/v2/person/add_face?api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&face_id=";
	AddFaceRequest += faceId;
	AddFaceRequest += "&api_key=c499b2943a96babe258e8d4ed8098061&tag=demotest&person_name=";
	AddFaceRequest += m_personName;
	return _sendRequest(AddFaceRequest.c_str());
}

int CPersonManger::_addFace(std::string personName ,std::string faceId){
	std::string AddFaceRequest = "/v2/person/add_face?api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&face_id=";
	AddFaceRequest += faceId;
	AddFaceRequest += "&api_key=c499b2943a96babe258e8d4ed8098061&tag=demotest&person_name=";
	AddFaceRequest += personName;
	return _sendRequest(AddFaceRequest.c_str());
}

/*
Person API to RemoveFace
https://apicn.faceplusplus.com/v2/person/remove_face?api_secret=YOUR_API_SECRET&face_id=1698e3320e1f75f63650e61d9e2ace53,13919c882327bdc55d7ba336e7cbf167&api_key=YOUR_API_KEY&person_name=NicolasCage
*/
int CPersonManger::_removeFace(std::string faceId){
	std::string RemoveFaceRequest = "/v2/person/remove_face?api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&face_id=";
	RemoveFaceRequest += faceId;
	RemoveFaceRequest += "&api_key=c499b2943a96babe258e8d4ed8098061&tag=demotest&person_name=";
	RemoveFaceRequest += m_personName;

	return _sendRequest(RemoveFaceRequest.c_str());
}


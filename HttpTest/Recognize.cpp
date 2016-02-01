#include "Recognize.h"


CRecognize::CRecognize()
{
}


CRecognize::~CRecognize()
{
}

/*
verify face to person
https://apicn.faceplusplus.com/v2/recognition/verify?api_secret=YOUR_API_SECRET&face_id=7fa73e35a15a0521739a5256d25b6e02&api_key=YOUR_API_KEY&person_name=FanBingBing
*/
int CRecognize::_verify(std::string faceId, std::string personName){
	std::string TrainVerfy = "/v2/recognition/verify?api_secret=";
	TrainVerfy += MY_API_SECRET;
	TrainVerfy += "&face_id=";
	TrainVerfy += faceId;
	TrainVerfy += "&api_key=";
	TrainVerfy += MY_API_KEY;
	TrainVerfy += "&person_name=";
	TrainVerfy += personName;
	_sendRequest(TrainVerfy.c_str());

	return 0;
}

/*
verify face from group
https://apicn.faceplusplus.com/v2/recognition/identify?url=http%3A%2F%2Ffaceplusplus.com%2Fstatic%2Fimg%2Fdemo%2F1.jpg&api_secret=YOUR_API_SECRET&api_key=YOUR_API_KEY&group_name=DemoGroup
*/
int CRecognize::_idefntify(std::string url, std::string groupName){
	std::string TrainIdentify = "/v2/recognition/identify?";
	TrainIdentify += "url=";
	TrainIdentify += url;
	TrainIdentify += "&api_secret=";
	TrainIdentify += MY_API_SECRET;
	
	TrainIdentify += "&api_key=";
	TrainIdentify += MY_API_KEY;
	TrainIdentify += "&group_name=";
	TrainIdentify += groupName;
	_sendRequest(TrainIdentify.c_str());

	return 0;
}

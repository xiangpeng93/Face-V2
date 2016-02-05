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
int CRecognize::_identify(std::string url, std::string groupName){
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



char* CRecognize::_getResultRecg(int cmd)
{
	static char sResult[1024] = {0};
	memset(sResult, 0, sizeof(sResult));
	if (!m_recvMessage.empty())
	{
		CParseJson parseJs;
		Json::Value value;
		parseJs.getJsonValue(m_recvMessage, &value);
		switch (cmd)
		{
		case GETVERIFYRESULT:
			strcpy(sResult, (value)["is_same_person"].asString().c_str());
			break;
		case GETIDENTIFYRESULT:
			strcpy(sResult, (value)["face"][0]["candidate"][0]["person_name"].asString().c_str());
			break;
		case GETFACEID:
			strcpy(sResult, (value)["face"][0]["face_id"].asString().c_str());
			break;
		default:
			break;
		}
	}
	else
	{
		return sResult;
	}
	return sResult;
}
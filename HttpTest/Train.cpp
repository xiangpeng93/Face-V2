#include "Train.h"


CTrain::CTrain()
{
}


CTrain::~CTrain()
{
}

/*
train verify
https://apicn.faceplusplus.com/v2/train/verify?api_secret=YOUR_API_SECRET&api_key=YOUR_API_KEY&person_name=Demoperson
*/

int CTrain::_trainVerify(std::string personName)
{
	std::string TrainVerfy = "/v2/train/verify?api_secret=";
	TrainVerfy += MY_API_SECRET;
	TrainVerfy += "&api_key=";
	TrainVerfy += MY_API_KEY;
	TrainVerfy += "&person_name=";
	TrainVerfy += personName;
	_sendRequest(TrainVerfy.c_str());

	return 0;
}

/*
train identify
https://apicn.faceplusplus.com/v2/train/identify?api_secret=YOUR_API_SECRET&api_key=YOUR_API_KEY&group_name=DemoGroup
*/
int CTrain::_trainIdentify(std::string guropName)
{
	std::string TrainIdentify = "/v2/train/identify?api_secret=";
	TrainIdentify += MY_API_SECRET;
	TrainIdentify += "&api_key=";
	TrainIdentify += MY_API_KEY;
	TrainIdentify += "&group_name=";
	TrainIdentify += guropName;
	_sendRequest(TrainIdentify.c_str());

	return 0;
}


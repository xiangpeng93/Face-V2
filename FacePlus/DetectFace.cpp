#include "DetectFace.h"

#include <json/json.h>
#include <algorithm> // sort
#include <sstream>
#include <stdio.h>

#include "ParseJson.h"
/*Detect Face*/
//http ://apicn.faceplusplus.com/v2/detection/detect?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&url=http://img5.duitang.com/uploads/item/201501/13/20150113131306_XUzEV.thumb.700_0.jpeg&attribute=glass,pose,gender,age,race,smiling&async=false

/*
{
//592b7f135caa12848b4500d68574f137
//{
//	"face":[
//	{
//		"attribute": {
//			"age": {
//				"range": 5,
//					"value" : 24
//			},
//			"gender" : {
//					"confidence": 80.2836,
//						"value" : "Male"
//				},
//				"glass" : {
//						"confidence": 99.9957,
//							"value" : "None"
//					},
//					"pose" : {
//							"pitch_angle": {
//								"value": -0.000693
//							},
//							"roll_angle" : {
//									"value": 4.40446
//								},
//								"yaw_angle" : {
//										"value": -0.065706
//									}
//						},
//							"race": {
//							"confidence": 79.4215,
//								"value" : "Asian"
//						},
//						"smiling" : {
//								"value": 91.7591
//							}
//		},
//			"face_id": "592b7f135caa12848b4500d68574f137",
//			"position" : {
//			"center": {
//				"x": 48.427673,
//					"y" : 48.166667
//			},
//			"eye_left" : {
//					"x": 37.715094,
//						"y" : 40.526
//				},
//				"eye_right" : {
//						"x": 59.90587,
//							"y" : 41.884833
//					},
//					"height" : 34.666667,
//					"mouth_left" : {
//							"x": 38.067925,
//								"y" : 56.8105
//						},
//						"mouth_right" : {
//								"x": 56.57652,
//									"y" : 58.108667
//							},
//							"nose" : {
//									"x": 47.418868,
//										"y" : 51.295
//								},
//								"width" : 43.60587
//		},
//		"tag": ""
//	}
//	],
//		"img_height": 879,
//		"img_id" : "4ba48ae7c0c051b48b2d36206191b2f5",
//		"img_width" : 700,
//		"session_id" : "98cab9cb6410480d8809a9f4478c5a1b",
//		"url" : "http://img5.duitang.com/uploads/item/201501/13/20150113131306_XUzEV.thumb.700_0.jpeg"
//}
}
*/

std::string DetectFaceRequest = "/v2/detection/detect?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&url=";

CDetectFace::CDetectFace(std::string detectUrl)
{
	setDetectUrl(detectUrl);
}


CDetectFace::~CDetectFace()
{
}


int CDetectFace::_detectFace()
{
	std::string DetectFace = "/v2/detection/detect?";
	DetectFace += "api_key=";
	DetectFace += MY_API_KEY;
	DetectFace += "&api_secret=";
	DetectFace += MY_API_SECRET;
	DetectFace += "&url=";
	DetectFace += m_detectUrl;

	return _sendRequest(DetectFace.c_str());
}

std::string CDetectFace::_getFaceId(){
	if (!m_recvMessage.empty())
	{
		CParseJson parseJs; Json::Value root;
		return parseJs.parseString(m_recvMessage, &root,"face");
	}
	else return "";
}

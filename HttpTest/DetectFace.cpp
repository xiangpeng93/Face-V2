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
	return _sendRequest(m_detectUrl.c_str());
}

std::string CDetectFace::_getFaceId(){
	if (!m_revMessage.empty())
	{
		CParseJson parseJs; Json::Value root;
		return parseJs.parseString(m_revMessage, &root,"face");
	}
	else return "";
}

int CDetectFace::_sendRequest(const char * request)
{
	int iResult = 0;
	//char *sendbuf = "GET / HTTP/1.1\r\nAccept:*/*\r\nHost:apicn.faceplusplus.com/v2/group/create?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=created_by_Alice&group_name=AST_Family\r\nConnection:Close\r\n\r\n";
	//char *sendbuf = "GET /v2/group/create?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=created_by_Alice&group_name=AST_Family HTTP/1.1\r\nAccept:*/*\r\nHost:apicn.faceplusplus.com\r\nConnection:Close\r\n\r\n";
	//char *sendbuf = "GET / HTTP/1.1\r\nAccept:*/*\r\nHost:www.baidu.com\r\nConnection:Close\r\n\r\n";
	std::string sSendBuf = "GET ";
	sSendBuf += DetectFaceRequest;
	sSendBuf += request;
	sSendBuf += " HTTP/1.1\r\nAccept:*/*\r\nHost:";
	sSendBuf += HostPath;
	sSendBuf += "\r\nConnection:Close\r\n\r\n";

	//----------------------
	// Create a SOCKET for connecting to server
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	hostent *ht = gethostbyname(HostPath);
	char str[MAX_PATH];
	inet_ntop(ht->h_addrtype, ht->h_addr, str, sizeof(str));


	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port of the server to be connected to.
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr(str);
	clientService.sin_port = htons(80);

	//----------------------
	// Connect to server.
	iResult = connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService));
	if (iResult == SOCKET_ERROR) {
		closesocket(m_socket);
		printf("Unable to connect to server: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// Send an initial buffer
	iResult = send(m_socket, sSendBuf.c_str(), sSendBuf.length(), 0);
	//iResult = send(m_socket, sendbuf, strlen(sendbuf), 0);

	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		return 1;
	}

	printf("Bytes Sent: %ld\n", iResult);
	Sleep(1000);
	// shutdown the connection since no more data will be sent
	//iResult = shutdown(m_socket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		return 1;
	}
	Sleep(2000);
	_recvRequest("");
	return 0;
}

int CDetectFace::_recvRequest(const char * request)
{
	int iResult = 0;


	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	//system("pause");
	// Receive until the peer closes the connection
	std::string message;
	do {
		memset(recvbuf, '\0', recvbuflen);
		iResult = recv(m_socket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			printf("%s\n", recvbuf);
			message += recvbuf;
			//printf("Bytes received: %d\n", iResult);
		}
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());

	} while (iResult > 0);

	message.find("\r\n\r\n");
	
	message.erase(0, message.find("\r\n\r\n") + strlen("\r\n\r\n"));
	m_revMessage = message;
	int state = -1;
	do 
	{
		state = m_revMessage.find_first_of(("лл"));
		if (state != -1)
			m_revMessage.erase(state, 1);
	} while (state != -1);
	
	closesocket(m_socket);
	return 0;
}
#define WIN32_LEAN_AND_MEAN
#include <json/json.h>
#include <algorithm> // sort
#include <sstream>

#include <Windows.h>
#include <iostream>

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512

#include "GroupManger.h"
#include "PersonManger.h"
#include "DetectFace.h"
#include "ParseJson.h"
#include "Train.h"
#include "Recognize.h"

int __cdecl main() {

	//----------------------
	// Declare and initialize variables.
	//----------------------
	// Initialize Winsock

	//int exitCode = 0;
	//Options opts;
	//CParseJson parseJs;
	//try {
	//	char* filename[200];
	//	filename[1] = "E:\\test.json";
	//	int exitCode = parseJs.parseCommandLine(2, (const char **)filename, &opts);
	//	if (exitCode != 0) {
	//		printf("Failed to parse command-line.");
	//		return exitCode;
	//	}
	//	printf(opts.path.c_str());
	//}
	//catch (const std::exception& e) {
	//	printf("Unhandled exception:\n%s\n", e.what());
	//	return 1;
	//}
	//std::string input = parseJs.readInputTestFile("E:\\test.json");//opts.path.c_str());
	//if (input.empty()) {
	//	printf("Failed to read input or empty input: %s\n", opts.path.c_str());
	//	return 3;
	//}

	//Json::Value root;
	//exitCode = parseJs.parseAndSaveValueTree(
	//	input, "test", "input",
	//	opts.features, opts.parseOnly, &root);
	//if (exitCode || opts.parseOnly) {
	//	return exitCode;
	//}


	int iResult = 0;
	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	std::fstream img;
	std::string imgFile;
	img.open("C:\\Users\\dell\\Desktop\\Face++\\LH1.jpg");
	img >> imgFile;
	bool isOpen = img.is_open();
	//system("pause");
	CGroupManger create("Test2");
	create._createGroup();
	
	CDetectFace face("");
	face.setDetectUrl("http://b83.photo.store.qq.com/psb?/V12iVgOg4KFP1E/AmIY1pGrj0xPIPdwwq*YfalIPD*JBVmx5cGNpuSdkOg!/b/dFMAAAAAAAAA&bo=gAJVAwAAAAAFAPc!&rf=viewer_4");
	face._detectFace();
	std::string destFaceId1 = face._getFaceId();

	std::cout << std::endl << destFaceId1.c_str() << std::endl;

	//system("pause");
	//system("pause");
	CPersonManger person("test1", "Test2");
	person._createPerson("test1");
	person._createPerson("test2");
	person._createPerson("test3");
	person._createPerson("test4");

	if (1)
	{
		//system("pause");
	loop1:
		CDetectFace face("http://img5.duitang.com/uploads/item/201501/13/20150113131306_XUzEV.thumb.700_0.jpeg");
		face._detectFace();
		std::string faceID = face._getFaceId();
		std::cout << std::endl << faceID.c_str() << std::endl;
		if (faceID.empty())
		{
			goto loop1;
		}
		//system("pause");
		person._addFace("test1", faceID);
	}

	if (1)
	{
		//system("pause");
		loop2:
		CDetectFace face("http://www.nihaotw.com/ylxw/201601/W020160113386515150408.jpg");
		face._detectFace();
		std::string faceID = face._getFaceId();
		std::cout << std::endl << faceID.c_str() << std::endl;
		if (faceID.empty())
		{
			goto loop2;
		}
		//system("pause");
		person._addFace("test2", faceID);
	}

	if (1)
	{
		//system("pause");
	loop3:
		CDetectFace face("http://b.hiphotos.baidu.com/baike/c0%3Dbaike80%2C5%2C5%2C80%2C26/sign=5fbbaf53bf389b502cf2e800e45c8eb8/ac4bd11373f0820233c524724dfbfbedab641b23.jpg");
		face._detectFace();
		std::string faceID = face._getFaceId();
		std::cout << std::endl << faceID.c_str() << std::endl;

		if (faceID.empty())
		{
			goto loop3;
		}
		//system("pause");
		person._addFace("test3", faceID);
	}
	if (1)
	{
		//system("pause");
		loop4:
		CDetectFace face("http://g.hiphotos.baidu.com/baike/c0%3Dbaike272%2C5%2C5%2C272%2C90/sign=fb5b442d57da81cb5aeb8b9f330fbb73/4afbfbedab64034f2ec56edfa9c379310b551dda.jpg");
		face._detectFace();
		std::string faceID = face._getFaceId();
		if (faceID.empty())
		{
			goto loop4;
		}
		std::cout << std::endl << faceID.c_str() << std::endl;
		//system("pause");
		person._addFace("test4", faceID);
	}

	//system("pause");
	CTrain train;
	train._trainVerify("test1");
	train._trainIdentify("Test2");
	//system("pause");
	CRecognize recg;
	loop5:
	face.setDetectUrl("http://b352.photo.store.qq.com/psb?/V12iVgOg3whx7U/CJZ4xsusF1aJYP2qJbaiyu8cnUzBCvhdZ9KwZrD*014!/b/dGABAAAAAAAA&bo=lQHQAgAAAAAFB2I!&rf=viewer_4");
	face._detectFace();
	std::string destFaceId = face._getFaceId();
	if (destFaceId.empty())
	{
		goto loop5;
	}
	std::cout << std::endl << destFaceId.c_str() << std::endl;
	train._trainVerify("test2");
	system("pause");
	recg._verify(destFaceId, "test2");
	std::cout<<recg._getResultRecg(GETVERIFYRESULT) << std::endl;
	//recg._verify(destFaceId, person.m_personName);
	


	//http://b352.photo.store.qq.com/psb?/V12iVgOg3whx7U/CJZ4xsusF1aJYP2qJbaiyu8cnUzBCvhdZ9KwZrD*014!/b/dGABAAAAAAAA&bo=lQHQAgAAAAAFB2I!&rf=viewer_4
	

	system("pause");
	
	recg._identify("http://img5.duitang.com/uploads/item/201501/13/20150113131306_XUzEV.thumb.700_0.jpeg"/*http://a.hiphotos.baidu.com/image/pic/item/78310a55b319ebc4df65cc478726cffc1f1716ca.jpg*/, "Test2");
	system("pause");
	char result[1024] = {0};
	memset(result, 0, sizeof(result));
	std::cout << recg._getResultRecg(GETIDENTIFYRESULT) << std::endl;
	std::cout << recg._getResultRecg(GETFACEID) << std::endl;

	recg._verify(recg._getResultRecg(GETFACEID), recg._getResultRecg(GETIDENTIFYRESULT));
	std::cout << recg._getResultRecg(GETVERIFYRESULT) << std::endl;
	system("pause");
	memset(result, 0, sizeof(result));

	//recg._verify(destFaceId, person.m_personName);
	recg._identify("http://www.nihaotw.com/ylxw/201601/W020160113386515150408.jpg", "Test2");
	std::cout << recg._getResultRecg(GETIDENTIFYRESULT) << std::endl;
	std::cout << recg._getResultRecg(GETFACEID) << std::endl;

	recg._verify(recg._getResultRecg(GETFACEID), recg._getResultRecg(GETIDENTIFYRESULT));
	std::cout << recg._getResultRecg(GETVERIFYRESULT) << std::endl;
	system("pause");
	//system("pause");
	//person._removeFace(faceID);

	

	system("pause");
	person._deletePerson("test1");
	person._deletePerson("test2");
	person._deletePerson("test3");
	person._deletePerson("test4");
	//char *sendbuf = "GET / HTTP/1.1\r\nAccept:*/*\r\nHost:astmakerspace.org.cn\r\nConnection:Close\r\n\r\n";
	//char recvbuf[DEFAULT_BUFLEN];
	//int recvbuflen = DEFAULT_BUFLEN;
	//SOCKET ConnectSocket = INVALID_SOCKET;
	//struct sockaddr_in clientService;

	////----------------------
	//// Create a SOCKET for connecting to server
	//ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//if (ConnectSocket == INVALID_SOCKET) {
	//	printf("Error at socket(): %ld\n", WSAGetLastError());
	//	WSACleanup();
	//	return 1;
	//}

	//hostent *ht =  gethostbyname("astmakerspace.org.cn");
	//char str[MAX_PATH];
	//inet_ntop(ht->h_addrtype, ht->h_addr, str, sizeof(str));


	////----------------------
	//// The sockaddr_in structure specifies the address family,
	//// IP address, and port of the server to be connected to.
	//clientService.sin_family = AF_INET;
	//clientService.sin_addr.s_addr = inet_addr(str);
	//clientService.sin_port = htons(80);

	////----------------------
	//// Connect to server.
	//iResult = connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService));
	//if (iResult == SOCKET_ERROR) {
	//	closesocket(ConnectSocket);
	//	printf("Unable to connect to server: %ld\n", WSAGetLastError());
	//	WSACleanup();
	//	return 1;
	//}

	//// Send an initial buffer
	//iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	//if (iResult == SOCKET_ERROR) {
	//	printf("send failed: %d\n", WSAGetLastError());
	//	closesocket(ConnectSocket);
	//	WSACleanup();
	//	return 1;
	//}

	//printf("Bytes Sent: %ld\n", iResult);

	//// shutdown the connection since no more data will be sent
	//iResult = shutdown(ConnectSocket, SD_SEND);
	//if (iResult == SOCKET_ERROR) {
	//	printf("shutdown failed: %d\n", WSAGetLastError());
	//	closesocket(ConnectSocket);
	//	WSACleanup();
	//	return 1;
	//}

	//// Receive until the peer closes the connection
	//do {
	//	memset(recvbuf, 0, recvbuflen);
	//	iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
	//	if (iResult > 0)
	//	{

	//		printf("%s\n", recvbuf);
	//		printf("Bytes received: %d\n", iResult);
	//	}
	//	else if (iResult == 0)
	//		printf("Connection closed\n");
	//	else
	//		printf("recv failed: %d\n", WSAGetLastError());

	//} while (iResult > 0);

	//// cleanup

	system("pause");
	create._deleteGroup();


	WSACleanup();
	system("pause");
	return 0;
}
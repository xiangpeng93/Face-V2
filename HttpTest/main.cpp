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

int __cdecl main() {

	//----------------------
	// Declare and initialize variables.
	//----------------------
	// Initialize Winsock

	int exitCode = 0;
	Options opts;
	CParseJson parseJs;
	try {
		char* filename[200];
		filename[1] = "E:\\test.json";
		int exitCode = parseJs.parseCommandLine(2, (const char **)filename, &opts);
		if (exitCode != 0) {
			printf("Failed to parse command-line.");
			return exitCode;
		}
		printf(opts.path.c_str());
	}
	catch (const std::exception& e) {
		printf("Unhandled exception:\n%s\n", e.what());
		return 1;
	}
	std::string input = parseJs.readInputTestFile("E:\\test.json");//opts.path.c_str());
	if (input.empty()) {
		printf("Failed to read input or empty input: %s\n", opts.path.c_str());
		return 3;
	}

	Json::Value root;
	exitCode = parseJs.parseAndSaveValueTree(
		input, "test", "input",
		opts.features, opts.parseOnly, &root);
	if (exitCode || opts.parseOnly) {
		return exitCode;
	}


	int iResult = 0;
	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	CGroupManger create("Test1");
	create._createGroup();
	system("pause");
	CPersonManger person("test1", "Test1");
	person._createPerson();
	system("pause");
	person._deletePerson();

	CDetectFace face("http://img5.duitang.com/uploads/item/201501/13/20150113131306_XUzEV.thumb.700_0.jpeg&attribute=glass,pose,gender,age,race,smiling");
	face._detectFace();
	system("pause");
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
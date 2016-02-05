#pragma once
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 512

#define HostPath  "apicn.faceplusplus.com"

#define MY_API_SECRET "hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH"
#define MY_API_KEY "c499b2943a96babe258e8d4ed8098061"

class CFacePlusPlusInterface
{
public:
public:
	virtual int doAction_1() = 0;
	virtual int doAction_2() = 0;

	virtual int _sendRequest(const char * request){
		int iResult = 0;
		std::string sSendBuf = "GET ";
		sSendBuf += request;
		sSendBuf += " HTTP/1.1\r\nAccept:*/*\r\nHost:";
		sSendBuf += HostPath;
		sSendBuf += "\r\nConnection:Close\r\n\r\n";
		OutputDebugString(sSendBuf.c_str());

		//----------------------
		// Create a SOCKET for connecting to server
		m_socket = socket(AF_INET, SOCK_STREAM, 0);
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
		//Sleep(1000);
		// shutdown the connection since no more data will be sent
		//iResult = shutdown(m_socket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed: %d\n", WSAGetLastError());
			closesocket(m_socket);
			WSACleanup();
			return 1;
		}
		OutputDebugString("Send Success");

		_recvRequest("");
		return iResult;
	};
	virtual int _recvRequest(const char * buffer){
		int iResult = 0;
		char recvbuf[DEFAULT_BUFLEN];
		int recvbuflen = DEFAULT_BUFLEN;

		// Receive until the peer closes the connection
		std::string message;
		do {
			memset(recvbuf, 0, recvbuflen);
			iResult = recv(m_socket, recvbuf, recvbuflen, 0);
			if (iResult > 0)
			{
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
		m_recvMessage = message;
		int state = -1;
		do
		{
			state = m_recvMessage.find_first_of(("лл"));
			if (state != -1)
				m_recvMessage.erase(state, 1);
		} while (state != -1);
		std::cout << m_recvMessage.c_str() << std::endl;
		OutputDebugString(m_recvMessage.c_str());

		closesocket(m_socket);
		return iResult;
	};
public:
	std::string m_apiKey;
	std::string m_secretyKey;
	std::string m_recvMessage;

	SOCKET m_socket; 
	struct sockaddr_in clientService;
};


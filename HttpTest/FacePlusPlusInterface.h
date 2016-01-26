#pragma once
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <string>
// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 512
class CFacePlusPlusInterface
{
public:
	CFacePlusPlusInterface()
	{
		/*SOCKET socket, std::string apiKey, std::string secretKey
		m_socket = socket;
		m_apiKey = apiKey;
	    m_secretyKey = secretKey;*/
	};
	~CFacePlusPlusInterface()
	{
	};
public:
	virtual int _sendRequest(char * request) = 0;
	virtual int _recvRequest(char * buffer) = 0;
public:
	std::string m_apiKey;
	std::string m_secretyKey;
	SOCKET m_socket; 
	struct sockaddr_in clientService;
};


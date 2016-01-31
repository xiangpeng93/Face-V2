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

int CTrain::_sendRequest(const char * request)
{
	int iResult = 0;
	std::string sSendBuf = "GET ";
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
	iResult = shutdown(m_socket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		return 1;
	}

	_recvRequest("");
	return iResult;
}

int CTrain::_recvRequest(const char * buffer)
{
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
	m_recvMessgae = message;
	closesocket(m_socket);
	return iResult;
}

#include "PersonManger.h"

std::string GroupRequest = "&group_name=";

/*
Person API to CreatePerson
https ://apicn.faceplusplus.com/v2/person/create?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=demotest&person_name=CL&group_name=AST_Family
*/
int CPersonManger::_createPerson(){
	std::string AddPersonRequest = "/v2/person/create?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=demotest&person_name=";

	AddPersonRequest += m_personName;
	AddPersonRequest += GroupRequest;
	AddPersonRequest += m_groupName;
	
	return _sendRequest(AddPersonRequest.c_str());
}

int CPersonManger::_createPerson(std::string personName){
	std::string AddPersonRequest = "/v2/person/create?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=demotest&person_name=";

	AddPersonRequest += personName;
	AddPersonRequest += GroupRequest;
	AddPersonRequest += m_groupName;

	return _sendRequest(AddPersonRequest.c_str());
}


/*
Person API to DeletePerson
https ://apicn.faceplusplus.com/v2/person/delete?api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&api_key=c499b2943a96babe258e8d4ed8098061&person_name=CL
*/

int CPersonManger::_deletePerson(){
	std::string DeletePersonRequest = "/v2/person/delete?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=demotest&person_name=";
	DeletePersonRequest += m_personName;
	DeletePersonRequest += GroupRequest;
	DeletePersonRequest += m_groupName;

	return _sendRequest(DeletePersonRequest.c_str());
}

int CPersonManger::_deletePerson(std::string personName){
	std::string DeletePersonRequest = "/v2/person/delete?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=demotest&person_name=";
	DeletePersonRequest += personName;
	DeletePersonRequest += GroupRequest;
	DeletePersonRequest += m_groupName;

	return _sendRequest(DeletePersonRequest.c_str());
}


//api_key = c499b2943a96babe258e8d4ed8098061
//api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH
//&tag=demotest&person_name=";
/*
Person API to AddFace
https://apicn.faceplusplus.com/v2/person/add_face?api_secret=YOUR_API_SECRET&face_id=1698e3320e1f75f63650e61d9e2ace53,13919c882327bdc55d7ba336e7cbf167&api_key=YOUR_API_KEY&person_name=NicolasCage
*/
int CPersonManger::_addFace(std::string faceId){
	std::string AddFaceRequest = "/v2/person/add_face?api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&face_id=";
	AddFaceRequest += faceId;
	AddFaceRequest += "&api_key=c499b2943a96babe258e8d4ed8098061&tag=demotest&person_name=";
	AddFaceRequest += m_personName;
	return _sendRequest(AddFaceRequest.c_str());
}

int CPersonManger::_addFace(std::string personName ,std::string faceId){
	std::string AddFaceRequest = "/v2/person/add_face?api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&face_id=";
	AddFaceRequest += faceId;
	AddFaceRequest += "&api_key=c499b2943a96babe258e8d4ed8098061&tag=demotest&person_name=";
	AddFaceRequest += personName;
	return _sendRequest(AddFaceRequest.c_str());
}

/*
Person API to RemoveFace
https://apicn.faceplusplus.com/v2/person/remove_face?api_secret=YOUR_API_SECRET&face_id=1698e3320e1f75f63650e61d9e2ace53,13919c882327bdc55d7ba336e7cbf167&api_key=YOUR_API_KEY&person_name=NicolasCage
*/
int CPersonManger::_removeFace(std::string faceId){
	std::string RemoveFaceRequest = "/v2/person/remove_face?api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&face_id=";
	RemoveFaceRequest += faceId;
	RemoveFaceRequest += "&api_key=c499b2943a96babe258e8d4ed8098061&tag=demotest&person_name=";
	RemoveFaceRequest += m_personName;

	return _sendRequest(RemoveFaceRequest.c_str());
}


int CPersonManger::_sendRequest(const char * request)
{
	int iResult = 0;
	//char *sendbuf = "GET / HTTP/1.1\r\nAccept:*/*\r\nHost:apicn.faceplusplus.com/v2/group/create?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=created_by_Alice&group_name=AST_Family\r\nConnection:Close\r\n\r\n";
	//char *sendbuf = "GET /v2/group/create?api_key=c499b2943a96babe258e8d4ed8098061&api_secret=hHbxdSmNwgvCwWURtjweTRyGR5V_TmWH&tag=created_by_Alice&group_name=AST_Family HTTP/1.1\r\nAccept:*/*\r\nHost:apicn.faceplusplus.com\r\nConnection:Close\r\n\r\n";
	//char *sendbuf = "GET / HTTP/1.1\r\nAccept:*/*\r\nHost:www.baidu.com\r\nConnection:Close\r\n\r\n";
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
	Sleep(500);
	// shutdown the connection since no more data will be sent
	iResult = shutdown(m_socket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		return 1;
	}

	_recvRequest("");
	return 0;
}

int CPersonManger::_recvRequest(const char * buffer)
{
	int iResult = 0;


	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	std::fstream out("test.html");

	//system("pause");
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
	out << message.c_str();

	closesocket(m_socket);
	return 0;
}
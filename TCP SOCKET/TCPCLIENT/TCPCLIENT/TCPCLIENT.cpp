#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>

using namespace std;
int main()
{
    cout << "\t\t-----TCP SERVER-----" << endl;
    cout << endl;
    //local variable
    WSADATA Winsockdata;
    int iWsaStartup;
    int iWsaCleanup;

    SOCKET TCPClientSocket;
    int iCloseSocket;

    struct sockaddr_in TCPServerAdd;
    struct sockaddr_in TCPClientAdd;
    int iTCPClientAdd = sizeof(TCPClientAdd);

    int iConnect;
    int iListen;
    SOCKET sAcceptSocket;

    int iSend;
    char SenderBuffer[512] = "Hello from Server!";
    int iSenderBuffer = strlen(SenderBuffer) + 1;

    int iRecv;
    char RecvBuffer[512];
    int iRecvBuffer = strlen(RecvBuffer) + 1;

    //Step =1 WSAStartUp Fun 
    iWsaStartup = WSAStartup(MAKEWORD(2, 2), &Winsockdata);
    if (iWsaStartup != 0)
        cout << "WsaStartup Failed" << endl;
    cout << "WsaStartup Succes!" << endl;

    //Step -2 Fill the structure
    TCPServerAdd.sin_family = AF_INET;
    TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
    TCPServerAdd.sin_port = htons(8000);
    //Step -3 Socket Creation
    TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (TCPClientSocket == INVALID_SOCKET)
        cout << "TCP Client Socket Creation FAILED!" << WSAGetLastError() << endl;

    // STEP -4 Connetct Fun
    iConnect = connect(TCPClientSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
    if (iConnect == SOCKET_ERROR)
        cout << "Connection Failed & Error NO->" << WSAGetLastError() << endl;
    cout << "Connection Success" << endl;
    //STEP 4 - bind

    /*iBind = bind(TCPClientSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
    if (iBind == SOCKET_ERROR)
        cout << "Binding Failed & Error NO-> " << WSAGetLastError() << endl;
    cout << "Binding Success" << endl;

    //STEP 5 - Listen
    iListen = listen(TCPClientSocket, 2);
    if (iListen == SOCKET_ERROR)
        cout << "Listen Failed & Error NO->" << WSAGetLastError() << endl;
    cout << "Listen Success" << endl;

    //STEP 6 - Accept
    sAcceptSocket = accept(TCPClientSocket, (SOCKADDR*)&TCPClientAdd, &iTCPClientAdd);
    if (sAcceptSocket == INVALID_SOCKET)
        cout << "Accept Failed & Error NO ->" << WSAGetLastError();
    cout << "Connection Accepted" << endl;

    //STEP 7- Send Data to Client
    iSend = send(sAcceptSocket, SenderBuffer, iSenderBuffer, 0);
    if (iSend == SOCKET_ERROR)
        cout << "Sending Failed & Error NO ->" << WSAGetLastError() << endl;
    cout << "Data Sending Success" << endl;
    */
    //Step -8 Recv Data from Server
    iRecv = recv(TCPClientSocket, RecvBuffer, iRecvBuffer, 0);
    if (iRecv == SOCKET_ERROR)
        cout << "Receive Data Failed & Error NO ->" << WSAGetLastError() << endl;
    cout << "DATA RECEIVED ->" << RecvBuffer << endl;

    //STEP 7- Send Data to Server
    iSend = send(TCPClientSocket, SenderBuffer, iSenderBuffer, 0);
    if (iSend == SOCKET_ERROR)
        cout << "Sending Failed & Error NO ->" << WSAGetLastError() << endl;
    cout << "Data Sending Success" << endl;

    // STEP -9 Close Socket
    iCloseSocket = closesocket(TCPClientSocket);
    if (iCloseSocket == SOCKET_ERROR)
        cout << "Closing Client Failed & Error No ->" << WSAGetLastError() << endl;
    cout << "Closing Client Succes" << endl;

    //STEP -10 Cleanup from DLL
    iWsaCleanup = WSACleanup();
    if (iWsaCleanup == SOCKET_ERROR)
        cout << "Cleanup Failed & Error NO-> " << WSAGetLastError() << endl;
    cout << "Clean success" << endl;

    return 0;
}


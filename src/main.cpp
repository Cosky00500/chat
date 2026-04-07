#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

int main () {

    int porta;
    int inidirizzo = AF_INET;
    int ProtocolloU = SOCK_STREAM;
    int DispCollegabili = INADDR_ANY;

    WSADATA wsaData;
    int wsa = WSAStartup(MAKEWORD(2, 2), &wsaData);




}


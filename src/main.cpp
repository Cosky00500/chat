//g++ main.cpp -o main.exe -lws2_32

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

int main () {

    int porta;
    //tipo di indirizzo tipo IPV4
    int indirizzo = AF_INET;
    //se la connessione deve essere tcp o altro (udp)
    int ProtocolloU = SOCK_STREAM;
    //dispositivi collegabili
    int DispCollegabili = INADDR_ANY;

    std::cout << "scegli la porta da aprire: \n";
    std::cin >> porta;

    WSADATA wsaData;
    int wsa = WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    SOCKET ascolto = socket(indirizzo , ProtocolloU, 0);

    sockaddr_in servizio;
    servizio.sin_family = indirizzo;
    servizio.sin_addr.s_addr = DispCollegabili;
    servizio.sin_port = htons(porta);

    if(bind(ascolto,(SOCKADDR*)&servizio,sizeof(servizio))) {

        std::cout << "ERRORE" << WSAGetLastError << std::endl;

    }else {

        std::cout << "socket formato correttamente sulla porta:" << porta << std::endl;

    };

    closesocket(ascolto);
    WSACleanup();



}


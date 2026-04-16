//g++ main.cpp -o main.exe -lws2_32

#include <algorithm>
#include <mutex>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

std::mutex mtx;
std::vector<SOCKET> listaClient;

int gestisciClient (SOCKET socketClient) {

    char buffer [4096];
    std::cout <<"[SERVER] nuovo client connesso" << socketClient << std::endl;

    while (true)
    {

        ZeroMemory(buffer, 4096);

        int datiClient =recv(socketClient, buffer ,4096, 0) ;

        if (datiClient <= 0) {

            std::cout << "[SERVER] client" << socketClient << "disconnesso" << std::endl ;
        
            mtx.lock();
            listaClient.erase(std::remove(listaClient.begin(), listaClient.end(), socketClient), listaClient.end());
            mtx.unlock();

            closesocket(socketClient);

        };

        std::cout << "[CLIENT " << socketClient << "] " << std::string(buffer, 0 , datiClient) << std::endl;        

        std::string confermaRecezione = "messaggio ricevuto";
        send(socketClient, confermaRecezione.c_str(), confermaRecezione.length() +1 , 0);

    };
    
    closesocket(socketClient);

}


int main () {

    std::string pswdNS;
    int porta;
    int pswd;
    //tipo di indirizzo tipo IPV4
    int indirizzo = AF_INET;
    //se la connessione deve essere tcp o altro (udp)
    int ProtocolloU = SOCK_STREAM;
    //dispositivi collegabili
    int DispCollegabili = INADDR_ANY;

    std::cout << "scegli la porta da aprire: \n";
    std::cin >> porta;

    std::cout << "\n vuoi una password (rispondi SOLO con S o N)";
    std::cin >> pswdNS;

    if (pswdNS != "S"){
        std::cout << "scegli la password";
        std::cin >> pswd;
    };

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

    listen(ascolto, SOMAXCONN);

    while(true){

        
        SOCKET socketClient = accept(ascolto, NULL, NULL); 
        if(socketClient != INVALID_SOCKET){

            mtx.lock();
            listaClient.push_back(socketClient);
            mtx.unlock();

            std::thread t(gestisciClient, socketClient);
            
            t.detach();


    }};

    closesocket(ascolto);
    WSACleanup();
    return 0;

}


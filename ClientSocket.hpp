#pragma once 

#include "Socket.hpp" 

class ClientSocket : public Socket
{
public:
    ~ClientSocket()
    {
        listenerThread.join();
        writerThread.join();

        Cleanup();
    }
    ClientSocket(const std::string& userName_) : Socket()
    {
        userName = userName_;

        Init();
    }
private:
    void Init()
    {
        //serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // loopback address -> basicallay connect to self // loopback address -> basicallay connect to self

        switch (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr))
        {
        case 0:
            std::cerr << "You messed up" << std::endl;
            std::cerr << "Incorrect input to inet_pton" << std::endl;
            throw std::exception("Invalid address");
            break;

        case -1:
            std::cerr << "it just failed" << std::endl;
            _ = WSAGetLastError();
            throw std::exception("Invalid address");
            break;

        default:
            break;
        }

        if (connect(socket_, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) // connecting to server
        {
            std::cerr << "Couldn connect to server" << std::endl;
            Cleanup();
            throw std::exception("Couldn connect to server");
        }

        send(socket_, userName.c_str(), (int)userName.size(), 0);
        std::cout << "Should be connected to the server ^^" << std::endl;
    }
public:
    void Run() override
    {
        listenerThread = std::thread(
            [=]()
            {
                Listen();
            }
        );

        writerThread = std::thread(
            [=]()
            {
                Write();
            }
        );
    }

    void Write()
    {
        char dataBuffer[BUFFER_SIZE];
        _ = memset(dataBuffer, 0, BUFFER_SIZE);

        std::cin.ignore(); // clears cin s buffer

        while (true)
        {
            char userInput[BUFFER_SIZE];
            
            std::cout << userName << ": ";
            std::cin.getline(userInput, BUFFER_SIZE);

            if (userInput == ":q") { break; } // ^^ we be WIMing

            send(socket_, userInput, BUFFER_SIZE, 0);
        }
    }

    void Listen()
    {
        char dataBuffer[BUFFER_SIZE];
        _ = memset(dataBuffer, 0, BUFFER_SIZE);

        while (true)
        {
            if (recv(socket_, dataBuffer, BUFFER_SIZE, 0) > 0)
            {
                std::cout << "\r" << dataBuffer << std::endl;
                std::cout << userName << ": ";
                _ = memset(dataBuffer, 0, BUFFER_SIZE);
            }
        }
    }
private:
    std::string userName;
    std::thread listenerThread;
    std::thread writerThread;
};

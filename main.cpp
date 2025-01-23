#include "Socket.hpp"
#include "ClientSocket.hpp"
#include "ServerSocket.hpp"


int main()
{
	std::cout << "Choose your role:\n - Server (1)\n - Client (Whatever)\n" << std::endl;
	int role;
	std::cin >> role;

	bool isServer = role == 1;

	std::string username;
	if (!isServer)
	{
		std::cout << "Enter your username: " << std::endl;
		std::cin >> username;
	}

	Socket* socket_ = (isServer ? (Socket*)new ServerSocket() : (Socket*)new ClientSocket(username));

	socket_->Run();

	while (true) { }


	delete socket_;

	return 0;
}
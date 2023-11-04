#include <iostream>

#include "WsaStartup.hxx"
#include "TcpSockAddr.hxx"
#include "Socket.hxx"
#include "Server.hxx"
#include "Tools.hxx"

#include <json.hpp>

static unsigned short verbose = 1;


int main()
{
	try
	{
		tnbLib::WsaStartup::verbose = verbose;
		tnbLib::WsaStartup wsa;

		auto address = std::make_shared<tnbLib::TcpSockAddr>();

		tnbLib::Socket::verbose = verbose;
		const auto listen = std::make_shared<tnbLib::Socket>(address);

		tnbLib::Tools::Bind(listen);
		tnbLib::Tools::Listen(listen);

		const auto server = std::make_shared<tnbLib::Server>();

		std::cout << "i'm waiting..." << std::endl;
		const auto client = tnbLib::Tools::Accept(listen);

		while (true)
		{
			
			std::cout << "I accepted the connection..." << std::endl;
			auto message = tnbLib::Tools::Receive(client);

			//std::cout << "MESSAGE : " << message << std::endl;

			auto [command, value] = tnbLib::Tools::ParseMessage(message);

			//std::cout << std::endl;
			std::cout << "command: " << command.stream << std::endl;
			std::cout << "value: " << value.stream << std::endl;
			//std::cout << std::endl;

			server->Construct(command.stream, value.stream);
			server->SendObj(client);

			if (command.stream == "EXIT")
			{
				std::cout << "The server is closed by the client!" << std::endl;
				break;
			}
		}
	}
	catch (...)
	{
		std::cout << " Error in running the server." << std::endl;
		return 0;

	}

	//std::system("pause");
	return 0;

}
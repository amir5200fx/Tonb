#include <TnbError.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif


#include <Server.hxx>
#include <Server_Ws2.hxx>
#include <Server_SockAddr_TCP.hxx>
#include <Server_Socket.hxx>
#include <Server_Tools.hxx>
#include <Server_WsaStartup.hxx>



#include <iostream>

static unsigned short verbose = 1;

int main()
{
	tnbLib::FatalError.throwExceptions();
	try
	{
		tnbLib::Server_WsaStartup::verbose = verbose;
		tnbLib::Server_WsaStartup wsa;

		auto address = std::make_shared<tnbLib::Server_SockAddr_TCP>();

		tnbLib::Server_Socket::verbose = verbose;
		const auto listen = std::make_shared<tnbLib::Server_Socket>(address);

		tnbLib::Server_Tools::Bind(listen);
		tnbLib::Server_Tools::Listen(listen);

		const auto server = std::make_shared<tnbLib::Server>();

		std::cout << "i'm waiting..." << std::endl;
		const auto client = tnbLib::Server_Tools::Accept(listen);

		while (true)
		{
			std::cout << "I accepted the connection..." << std::endl;
			auto message = tnbLib::Server_Tools::Receive(client);

			//std::cout << "MESSAGE : " << message << std::endl;

			auto [command, flag, sense, value] = tnbLib::Server_Tools::ParseMessage(message);

			std::cout << "\n===========================================\n";
			std::cout << "command: " << command.stream << "\n";
			//std::cout << "flag: " << flag.stream << "\n";
			//std::cout << "empty? " << sense.stream << "\n";
			//std::cout << "value: " << value.stream << "\n";
			std::cout << "===========================================\n";

			server->Construct(command, flag, sense, value);

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
	return 0;
}
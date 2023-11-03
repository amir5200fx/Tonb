#include "Tools.hxx"

#include <thread>

#include "SockAddr.hxx"
#include "Socket.hxx"
#include "ServError.hxx"
#include "Server.hxx"

#include <json.hpp>

const std::string tnbLib::Tools::END_MESSAGE = ";;$";

std::string tnbLib::Tools::EndMessageChars(const std::string& theMessage)
{
	if (theMessage.size() < 3)
	{
		return {};
	}
	const auto n = static_cast<int>(theMessage.size());
	std::string message;
	for (int i = n - 3; i < theMessage.size(); i++)
	{
		message.push_back(theMessage.at(i));
	}
	return std::move(message);
}

std::string tnbLib::Tools::RemoveEndChars(const std::string& theMessage)
{
	std::string message;
	for (int i = 0; i < theMessage.size() - 3; i++)
	{
		message.push_back(theMessage.at(i));
	}
	return std::move(message);
}

bool tnbLib::Tools::IsEnded(const std::string& theMessage)
{
	if (EndMessageChars(theMessage) == END_MESSAGE)
	{
		return true;
	}
	return false;
}

void tnbLib::Tools::WaitAMoment()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void tnbLib::Tools::Bind(const std::shared_ptr<Socket>& theSocket)
{
	addrinfo* addr = theSocket->Address()->Address();
	const int result = bind(theSocket->Descriptor(), addr->ai_addr, static_cast<int>(addr->ai_addrlen));
	if (result == SOCKET_ERROR)
	{
		throw ServError("bind failed with error: " + std::to_string(WSAGetLastError()));
	}
}

void tnbLib::Tools::Listen(const std::shared_ptr<Socket>& theSocket)
{
	const int result = listen(theSocket->Descriptor(), SOMAXCONN);
	if (result == SOCKET_ERROR)
	{
		throw ServError("listen failed with error: " + std::to_string(WSAGetLastError()));
	}
}

std::shared_ptr<tnbLib::Socket>
tnbLib::Tools::Accept(const std::shared_ptr<Socket>& theSocket)
{
	auto clientSocket = accept(theSocket->Descriptor(), NULL, NULL);
	return std::make_shared<Socket>(clientSocket);
}

std::string tnbLib::Tools::Receive(const std::shared_ptr<Socket>& theSocket)
{
	constexpr auto DEFAULT_BUFLEN = 512;
	int iResult = 0;
	std::string message;
	do
	{
		char recvbuf[DEFAULT_BUFLEN];
		constexpr int recvbuflen = DEFAULT_BUFLEN;

		iResult = recv(theSocket->Descriptor(), recvbuf, recvbuflen, 0);
		WaitAMoment();

		if (iResult > 0)
		{
			//std::cout << "Getting the message.." << std::endl;
			message += RetrieveMessage(recvbuf, iResult);
			if (IsEnded(message))
			{
				message = RemoveEndChars(message);
				break;
			}
		}
	}
	while (iResult >= 0);
	return std::move(message);
}

std::string tnbLib::Tools::RetrieveMessage(char* theMessage, int theLen)
{
	std::string result;
	for (int i = 0; i < theLen; i++)
		result += theMessage[i];
	return std::move(result);
}

std::pair<tnbLib::Tools::Command, tnbLib::Tools::Value>
tnbLib::Tools::ParseMessage(const std::string& theMessage)
{
	//std::cout << "message = " << theMessage << std::endl;
	nlohmann::json jsonData = nlohmann::json::parse(theMessage);
	Command command{ jsonData.at(Server::REQUEST) };
	Value value{ jsonData.at(Server::VALUE) };
	return { std::move(command), std::move(value) };
}


#pragma once
#ifndef _Tools_Header
#define _Tools_Header

#include <memory>
#include <string>

namespace tnbLib
{

	class Socket;

	class Tools
	{

	public:

		struct Command
		{
			std::string stream;
		};

		struct Value
		{
			std::string stream;
		};

		static const std::string END_MESSAGE;

		static std::string EndMessageChars(const std::string& theMessage);
		static std::string RemoveEndChars(const std::string& theMessage);
		static bool IsEnded(const std::string& theMessage);

		static void WaitAMoment();

		static void Bind(const std::shared_ptr<Socket>&);
		static void Listen(const std::shared_ptr<Socket>&);
		static std::shared_ptr<Socket> Accept(const std::shared_ptr<Socket>&);
		static std::string Receive(const std::shared_ptr<Socket>&);
		static std::string RetrieveMessage(char* theMessage, int theLen);

		static std::pair<Command, Value> ParseMessage(const std::string& theMessage);

		static void ThrowError(const std::string& message);

	};
}

#endif

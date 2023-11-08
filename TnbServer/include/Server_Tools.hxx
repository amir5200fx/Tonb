#pragma once
#ifndef _Server_Tools_Header
#define _Server_Tools_Header

#include <Server_Module.hxx>
#include <Server.hxx>

#include <memory>
#include <string>

namespace tnbLib
{

	// Forward Declarations
	class Server_Socket;

	class Server_Tools
	{

	public:


		static TnbServer_EXPORT std::string EndMessageChars(const std::string& theMessage);
		static TnbServer_EXPORT std::string RemoveEndChars(const std::string& theMessage);
		static TnbServer_EXPORT bool IsEnded(const std::string& theMessage);

		static TnbServer_EXPORT void WaitAMoment();

		static TnbServer_EXPORT void Bind(const std::shared_ptr<Server_Socket>&);
		static TnbServer_EXPORT void Listen(const std::shared_ptr<Server_Socket>&);
		static TnbServer_EXPORT std::shared_ptr<Server_Socket> Accept(const std::shared_ptr<Server_Socket>&);
		static TnbServer_EXPORT std::string Receive(const std::shared_ptr<Server_Socket>&);
		static TnbServer_EXPORT std::string RetrieveMessage(const char* theMessage, int theLen);

		static TnbServer_EXPORT std::tuple<Server::Command, Server::Flag, Server::Emptiness, Server::Value> ParseMessage(const std::string& theMessage);

		static TnbServer_EXPORT void ThrowError(const std::string& message);
		
	};
}

#endif
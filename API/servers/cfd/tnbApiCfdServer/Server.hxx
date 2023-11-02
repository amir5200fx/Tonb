#pragma once
#ifndef _Server_Header
#define _Server_Header

#include "Objects/Object/Server_Object.hxx"

#include <memory>
#include <map>

namespace tnbLib
{

	class Socket;

	class Server
	{

	public:

		enum class objects
		{
			real = 0,
			integer,
			vector,
			axis,
			segment,
			exit
		};

	private:

		/*Private Data*/

		std::shared_ptr<Server_Object> theObj_;
		std::string theCommand_;
		

		// Private functions and operators

		void CreateReal(const std::string&);
		void CreateInt(const std::string&);
		void CreateVec(const std::string&);
		void CreateAxis(const std::string&);
		void CraeteSegment(const std::string&);

	public:

		static std::map<std::string, objects> Commands;
		static const std::string REQUEST;
		static const std::string RESPONSE;
		static const std::string VALUE;

		// default constructor

		Server() = default;

		// constructors


		// Public functions and operators

		void Construct(const std::string& theCommand, const std::string& theValue);
		void SendObj(const std::shared_ptr<Socket>&) const;

	};

}

#endif

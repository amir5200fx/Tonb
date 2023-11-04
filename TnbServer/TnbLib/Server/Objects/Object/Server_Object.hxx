#pragma once
#ifndef _Server_Object_Header
#define _Server_Object_Header

#include <string>
#include <sstream>

namespace tnbLib
{

	class Server_Object
	{

		/*Private Data*/

	protected:

		std::stringstream theStream_;

		// default constructor

		Server_Object()
		{}

		// constructors

	public:

		static const std::string RESPONSE;
		static const std::string VALUE;
		static const std::string SENSE;

		enum class RespType
		{
			good = 0,
			bad,
			warning
		};

		// Public functions and operators

		const auto& Stream() const { return theStream_; }

		virtual void Construct(const std::string& theValue) = 0;

		static std::string GetRespType(const RespType);
		
	};
}

#endif
#pragma once
#ifndef _Server_Object_Header
#define _Server_Object_Header

#include <Server_Module.hxx>
#include <Server_Macros.hxx>

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

		static TnbServer_EXPORT const std::string RESPONSE;
		static TnbServer_EXPORT const std::string VALUE;
		static TnbServer_EXPORT const std::string SENSE;

		enum class RespType
		{
			good = 0,
			bad,
			warning
		};

		// Public functions and operators

		const auto& Stream() const { return theStream_; }

		virtual void Construct(const std::string& theValue) = 0;

		static TnbServer_EXPORT std::string GetRespType(const RespType);
		
	};
}

#endif
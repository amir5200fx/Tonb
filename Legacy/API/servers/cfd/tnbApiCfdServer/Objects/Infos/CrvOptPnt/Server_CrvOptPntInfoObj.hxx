#pragma once
#ifndef _Server_CrvOptPntInfoObj_Header
#define _Server_CrvOptPntInfoObj_Header

#include "../../Object/Server_Object.hxx"

namespace tnbLib
{

	class Server_CrvOptPntInfoObj
		: public Server_Object
	{

		/*Private Data*/

	public:

		struct Params
		{
			static const std::string tol;
			static const std::string under_relax;
			static const std::string max_lev;
		};

		static const std::string commandName;

		// default constructor

		Server_CrvOptPntInfoObj()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;
	};
}

#endif
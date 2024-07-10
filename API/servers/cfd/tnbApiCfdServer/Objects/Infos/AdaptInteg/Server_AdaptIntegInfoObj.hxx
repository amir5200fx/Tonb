#pragma once
#ifndef _Server_AdaptIntegInfoObj_Header
#define _Server_AdaptIntegInfoObj_Header

#include "../../Object/Server_Object.hxx"

namespace tnbLib
{

	class Server_AdaptIntegInfoObj
		: public Server_Object
	{

		/*Private Data*/

	public:

		struct Params
		{
			static const std::string tol;
			static const std::string max_nb_iters;
			static const std::string min_nb_iters;
		};

		static const std::string commandName;

		// default constructor

		Server_AdaptIntegInfoObj()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;
	};
}

#endif
#pragma once
#ifndef _Server_BisectSolverInfoObj_Header
#define _Server_BisectSolverInfoObj_Header

#include "../../Object/Server_Object.hxx"

namespace tnbLib
{

	class Server_BisectSolverInfoObj
		: public Server_Object
	{

		/*Private Data*/

	public:

		struct Params
		{
			static const std::string tol;
			static const std::string delta;
			static const std::string max_nb_iters;
		};

		static const std::string commandName;

		// default constructor

		Server_BisectSolverInfoObj()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;
	};
}

#endif
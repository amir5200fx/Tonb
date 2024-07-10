#pragma once
#ifndef _Server_NewtonSolverInfoObj_Header
#define _Server_NewtonSolverInfoObj_Header

#include "../../Object/Server_Object.hxx"

namespace tnbLib
{

	class Server_NewtonSolverInfoObj
		: public Server_Object
	{

		/*Private Data*/

	public:

		struct Params
		{
			static const std::string tol;
			static const std::string small;
			static const std::string zero;
			static const std::string under_relax;
			static const std::string max_nb_iters;
		};

		static const std::string commandName;

		// default constructor

		Server_NewtonSolverInfoObj()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;
	};
}

#endif
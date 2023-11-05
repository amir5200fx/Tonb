#pragma once
#ifndef _Server_NumObj_NewtonNonLinSolver_Info_Header
#define _Server_NumObj_NewtonNonLinSolver_Info_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_NumObj_NewtonNonLinSolver_Info
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

		static const std::string command_name;

		// default constructor

		Server_NumObj_NewtonNonLinSolver_Info()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;
	};
}

#endif

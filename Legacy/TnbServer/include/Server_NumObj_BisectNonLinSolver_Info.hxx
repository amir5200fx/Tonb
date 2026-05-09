#pragma once
#ifndef _Server_NumObj_BisectNonLinSolver_Info_Header
#define _Server_NumObj_BisectNonLinSolver_Info_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_NumObj_BisectNonLinSolver_Info
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

		static const std::string command_name;

		// default constructor

		Server_NumObj_BisectNonLinSolver_Info()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;
	};
}

#endif

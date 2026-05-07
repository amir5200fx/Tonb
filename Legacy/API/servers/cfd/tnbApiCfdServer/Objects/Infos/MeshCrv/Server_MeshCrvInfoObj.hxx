#pragma once
#ifndef _Server_MeshCrvInfoObj_Header
#define _Server_MeshCrvInfoObj_Header

#include "../../Object/Server_Object.hxx"

namespace tnbLib
{

	class Server_MeshCrvInfoObj
		: public Server_Object
	{

		/*Private Data*/

	public:

		struct Params
		{
			static const std::string under_relax;
			static const std::string max_lev;
			static const std::string ignore_non_convg;
			static const std::string overall_integ_info;
			static const std::string newton_integ_info;
			static const std::string iter_info;
			static const std::string corr_info;
			static const std::string bisect_info;
		};

		static const std::string commandName;

		// default constructor

		Server_MeshCrvInfoObj()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;
	};
}

#endif
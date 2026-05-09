#pragma once
#ifndef _Server_Cad2dObj_Discret_Info_Header
#define _Server_Cad2dObj_Discret_Info_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_Cad2dObj_Discret_Info
		: public Server_Object
	{

	public:
		struct Params
		{
			static const std::string target;
			static const std::string min_size;
			static const std::string angle;
			static const std::string nb_samples;
			static const std::string nb_inits;
			static const std::string max_nb_subs;
		};

		static const std::string command_name;

		Server_Cad2dObj_Discret_Info() = default;

		void Construct(const std::string& theValue) override;
		
	};
}


#endif
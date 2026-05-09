#pragma once
#ifndef _Server_ToolsObj_DiscrtShape2d_Header
#define _Server_ToolsObj_DiscrtShape2d_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_ToolsObj_DiscrtShape2d
		: public Server_Object
	{

	public:
		struct Params
		{
			static const std::string approx;
			static const std::string angle;
			static const std::string min_size;
			static const std::string max_nb_subdivide;
			static const std::string int_nb_subdivide;
			static const std::string nb_samples;
		};

		static TnbServer_EXPORT const std::string command_name;

		// default constructor

		Server_ToolsObj_DiscrtShape2d()
			= default;

		// Public functions and operators

		TnbServer_EXPORT void Construct(const std::string&) override;
		
	};
}

#endif
#pragma once
#ifndef _Server_Mesh2dObj_Header
#define _Server_Mesh2dObj_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	defineTnbServerObject(Server_Mesh2dObj_MetricPrcsr_Settings);

	class Server_Mesh2dObj_MetricPrcsr
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string size_fun;
			static const std::string dim;
			static const std::string settings;
		};

		static const std::string command_name;

		Server_Mesh2dObj_MetricPrcsr() = default;

		void Construct(const std::string& theValue) override;
	};

	class Server_Mesh2dObj_RefValues
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string base_size;
			static const std::string growth_rate;
			static const std::string boundary_growth_rate;
			static const std::string size_adapt_method;
			static const std::string size_type;
			static const std::string min_size;
			static const std::string target_size;
			static const std::string curvature_status;
			static const std::string span_angle;
			static const std::string area;
		};

		static const std::string command_name;

		Server_Mesh2dObj_RefValues() = default;

		void Construct(const std::string& theValue) override;
	};


}

#endif
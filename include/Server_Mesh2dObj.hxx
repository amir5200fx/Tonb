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

	class Server_Mesh2dObj_Mesh_Curve_Settings
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string length_integ;
			static const std::string iter_integ;
			static const std::string newton_solver;
			static const std::string opt_point;
			static const std::string bisect_solver;

			static const std::string length_max_lev_sub;
			static const std::string ur;
			static const std::string ignore_non_conv;
		};

		static const std::string command_name;

		Server_Mesh2dObj_Mesh_Curve_Settings() = default;

		void Construct(const std::string& theValue) override;
	};

	class Server_Mesh2dObj_Mesh_Curve
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string curve;
			static const std::string metrics;
			static const std::string settings;
		};

		static const std::string command_name;

		Server_Mesh2dObj_Mesh_Curve() = default;

		void Construct(const std::string& theValue) override;
	};

	class Server_Mesh2dObj_SoluData
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string curve_settings;
			static const std::string metric_settings;
			static const std::string size_fun;
			static const std::string area;
			static const std::string node_gen;
		};

		static const std::string command_name;

		Server_Mesh2dObj_SoluData() = default;

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
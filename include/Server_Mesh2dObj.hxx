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

	class Server_Mesh2dObj_Mesh_Curve_OptPoint
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string tol;
			static const std::string ur;
			static const std::string max_lev;
		};

		static const std::string command_name;

		Server_Mesh2dObj_Mesh_Curve_OptPoint() = default;

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

	defineTnbServerObject(Server_Mesh2dObj_SoluData_ExportMeshToPlt);

	class Server_Mesh2dObj_Region
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string solu_data;
			static const std::string tol;
		};

		static const std::string command_name;

		Server_Mesh2dObj_Region() = default;

		void Construct(const std::string& theValue) override;
	};

	defineTnbServerObject(Server_Mesh2dObj_BndMesh);

	defineTnbServerObject(Server_Mesh2dObj_NodeGen_Std);

	class Server_Mesh2dObj_Mesh
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string solu_data;
			static const std::string node_gen;
		};

		static const std::string command_name;

		Server_Mesh2dObj_Mesh() = default;

		void Construct(const std::string& theValue) override;
	};

	defineTnbServerObject(Server_Mesh2dObj_Mesh_QualFun_Vlrms2Ratio);

	defineTnbServerObject(Server_Mesh2dObj_Mesh_LaplacSmooth_AdjEdgesFun);

	class Server_Mesh2dObj_LaplacSmooth
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string solu_data;
			static const std::string qual_fun;
			static const std::string avg_fun;
			static const std::string nb_iters;
			static const std::string ur;
		};

		static const std::string command_name;

		Server_Mesh2dObj_LaplacSmooth() = default;

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

	class Server_Mesh2dObj_BndLayer_F1
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(solu_data);
			defineTnbServerParam(thick);
			defineTnbServerParam(curves);
			defineTnbServerParam(rate);
			defineTnbServerParam(cluster_size);
			defineTnbServerParam(first_layer);
			defineTnbServerParam(chevron_angle);
		};

		constructTnbServerObject(Server_Mesh2dObj_BndLayer_F1);
	};

	defineTnbServerObject(Server_Mesh2dObj_ExportToFEA);

	class Server_Mesh2dObj_Extrude_FEA
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(fea_mesh);
			defineTnbServerParam(extrusion);
			defineTnbServerParam(title);
		};

		constructTnbServerObject(Server_Mesh2dObj_Extrude_FEA);
	};

	defineTnbServerObject(Server_Mesh2dObj_ExportToPlt);

	
}

#endif
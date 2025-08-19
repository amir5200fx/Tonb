#pragma once
#ifndef _Server_Geo2dObj_BndBox_Header
#define _Server_Geo2dObj_BndBox_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_Geo2dObj_BndBox_Create
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string p0;
			static const std::string p1;
		};

		static const std::string command_name;

		Server_Geo2dObj_BndBox_Create() = default;

		void Construct(const std::string& theValue) override;
		
	};

	class Server_Geo2dObj_BndBox_PntList
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string pnt_list;
			static const std::string offset;
		};

		static const std::string command_name;

		Server_Geo2dObj_BndBox_PntList() = default;

		void Construct(const std::string& theValue) override;
	};

	class Server_Geo2dObj_BndBox_Curve
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string curve;
			static const std::string offset;
		};

		static const std::string command_name;

		Server_Geo2dObj_BndBox_Curve() = default;

		void Construct(const std::string& theValue) override;
	};

	class Server_Geo2dObj_BndBox_CrvList
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string cuvre_list;
			static const std::string offset;
		};

		static const std::string command_name;

		Server_Geo2dObj_BndBox_CrvList() = default;

		void Construct(const std::string& theValue) override;
	};

	class Server_Geo2dObj_BndBox_Area
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string area;
			static const std::string offset;
		};

		static const std::string command_name;

		Server_Geo2dObj_BndBox_Area() = default;

		void Construct(const std::string& theValue) override;
	};

	class Server_Geo2dObj_BndBox_AreaList
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string area_list;
			static const std::string offset;
		};

		static const std::string command_name;

		Server_Geo2dObj_BndBox_AreaList() = default;

		void Construct(const std::string& theValue) override;
		
	};

	defineTnbServerObject(Server_Geo2dObj_BndBox_GetDia);

	defineTnbServerObject(Server_Geo2dObj_BndBox_GetCorners);

	defineTnbServerObject(Server_Geo2dObj_BndBox_GetLengths);

	defineTnbServerObject(Server_Geo2dObj_BndBox_GetP0);
	defineTnbServerObject(Server_Geo2dObj_BndBox_GetP1);

	class Server_Geo2dObj_BndBox_Expand
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string bnd_box;
			static const std::string offset;
		};

		static const std::string command_name;

		Server_Geo2dObj_BndBox_Expand() = default;

		void Construct(const std::string& theValue) override;
	};
}

#endif
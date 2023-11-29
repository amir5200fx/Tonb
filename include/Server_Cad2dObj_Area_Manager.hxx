#pragma once
#ifndef _Server_Cad2dObj_Area_Manager_Header
#define _Server_Cad2dObj_Area_Manager_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	defineTnbServerObject(Server_Cad2dObj_Area_Manager_Segments);

	class Server_Cad2dObj_Area_Manager_Segments_CombineBlocks
		: public Server_Object
	{

	public:
		struct Params
		{
			static const std::string blocks;
			static const std::string area;
			static const std::string new_name;
		};

		static const std::string command_name;

		Server_Cad2dObj_Area_Manager_Segments_CombineBlocks() = default;

		void Construct(const std::string& theValue) override;

	};

	class Server_Cad2dObj_Area_Manager_CombineAll
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(area);
			defineTnbServerParam(name);
		};

		constructTnbServerObject(Server_Cad2dObj_Area_Manager_CombineAll);
	};

	class Server_Cad2dObj_Area_Manager_Segments_BlockCurves
		: public Server_Object
	{

	public:
		struct Params
		{
			static const std::string block_name;
			static const std::string area;
		};

		static const std::string command_name;

		Server_Cad2dObj_Area_Manager_Segments_BlockCurves() = default;

		void Construct(const std::string& theValue) override;
		
	};

	class Server_Cad2dObj_Area_Manager_Segments_SplitBlock
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string curve_ids;
			static const std::string new_name;
			static const std::string block_name;
			static const std::string area;
		};

		static const std::string command_name;

		Server_Cad2dObj_Area_Manager_Segments_SplitBlock() = default;

		void Construct(const std::string& theValue) override;
		
	};

	class Server_Cad2dObj_Area_Manager_Segments_RenameBlock
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string new_name;
			static const std::string block_name;
			static const std::string area;
		};

		static const std::string command_name;

		Server_Cad2dObj_Area_Manager_Segments_RenameBlock() = default;

		void Construct(const std::string& theValue) override;
		
	};



}

#endif
#pragma once
#ifndef _Server_Cad2dObj_Area_F1_Header
#define _Server_Cad2dObj_Area_F1_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_Cad2dObj_Area_F1
		: public Server_Object
	{

	public:
		struct Params
		{
			static const std::string name;
			static const std::string curve_list;
		};

		static const std::string command_name;

		Server_Cad2dObj_Area_F1() = default;

		void Construct(const std::string& theValue) override;
		void MakeEmpty() override;

	};

	defineTnbServerObject(Server_Cad2dObj_Area_GetNbCorners);
	defineTnbServerObject(Server_Cad2dObj_Area_GetNbSegments);
	defineTnbServerObject(Server_Cad2dObj_Area_ExportToPlt);

	defineTnbServerObject(Server_Cad2dObj_Area_GetCurves);

	defineTnbServerObject(Server_Cad2dObj_Area_GetOuterPolygon);

	class Server_Cad2dObj_Area_Trsf
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(trsf);
			defineTnbServerParam(area);
		};
		constructTnbServerObject(Server_Cad2dObj_Area_Trsf);
	};
	
}


#endif
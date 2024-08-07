#pragma once
#ifndef _Server_Cad2dObj_Segment2d_F1_Header
#define _Server_Cad2dObj_Segment2d_F1_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_Cad2dObj_Segment2d_F1
		: public Server_Object
	{

	public:
		struct Params
		{
			static const std::string p0;
			static const std::string p1;
			static const std::string name;
		};

		static const std::string command_name;

		Server_Cad2dObj_Segment2d_F1() = default;

		void Construct(const std::string& theValue) override;

	};
}


#endif

#pragma once
#ifndef _Server_Cad2dObj_PrjPntCrv_Header
#define _Server_Cad2dObj_PrjPntCrv_Header

#include <Server_Object.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	class Server_Cad2dObj_PrjPntCrv
		: public Server_Object
	{

	public:

		struct Values
		{
			Pnt2d pnt_on_crv;
			Pnt2d pnt;
			Standard_Real u;

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned short file_version)
			{
				ar& pnt_on_crv;
				ar& pnt;
				ar& u;
			}
		};

		struct Params
		{
			static const std::string curve;
			static const std::string pnt;
			static const std::string tol;
		};

		Server_Cad2dObj_PrjPntCrv() = default;

		void Construct(const std::string& theValue) override;
		void MakeEmpty() override;

	};
}

#endif
#pragma once
#ifndef _Server_Cad2dObj_CalcCrvLength_Header
#define _Server_Cad2dObj_CalcCrvLength_Header

#include <Server_Object.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>

namespace tnbLib
{
	class Server_Cad2dObj_CalcCrvLength
		: public Server_Object
	{

	public:
		struct Values
		{
			std::shared_ptr<NumAlg_AdaptiveInteg_Info> integ_info;
			int max_nb_subs;
			bool ignore_non_conv;
			bool shut_up_warnings;
			int verbose;

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned short file_version)
			{
				ar& integ_info;
				ar& max_nb_subs;
				ar& ignore_non_conv;
				ar& shut_up_warnings;
				ar& verbose;
			}
		};

		struct Params
		{
			static const std::string curve;
			static const std::string lower;
			static const std::string upper;
			static const std::string info;
		};

		static const std::string command_name;

		Server_Cad2dObj_CalcCrvLength() = default;

		void Construct(const std::string& theValue) override;

	};
}

#endif
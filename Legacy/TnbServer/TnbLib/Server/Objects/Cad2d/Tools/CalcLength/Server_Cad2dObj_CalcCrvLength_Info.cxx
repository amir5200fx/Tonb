#include <Server_Cad2dObj_CalcCrvLength_Info.hxx>

#include <json.hpp>

const std::string tnbLib::Server_Cad2dObj_CalcCrvLength_Info::Params::integ("integ");
const std::string tnbLib::Server_Cad2dObj_CalcCrvLength_Info::Params::max_nb_subs("max_nb_subs");
const std::string tnbLib::Server_Cad2dObj_CalcCrvLength_Info::Params::ignore_non_conv("ignore_non_conv");
const std::string tnbLib::Server_Cad2dObj_CalcCrvLength_Info::Params::shut_up_warnings("shut_up_warnings");
const std::string tnbLib::Server_Cad2dObj_CalcCrvLength_Info::Params::verbose("verbose");

void tnbLib::Server_Cad2dObj_CalcCrvLength_Info::Construct(const std::string& theValue)
{
	std::shared_ptr<NumAlg_AdaptiveInteg_Info> integ;
	int max_nb_subs = 0;
	std::string ignore_non_conv;
	std::string shut_up_warnings;
	int verbose = 0;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(integ);
		}
		{
			loadTnbServerObject(max_nb_subs);
		}
		{
			ignore_non_conv = loader.at(Params::ignore_non_conv).get<std::string>();
		}
		{
			shut_up_warnings = loader.at(Params::shut_up_warnings).get<std::string>();
		}
		{
			loadTnbServerObject(verbose);
		}
	}
	try
	{
		Server_Cad2dObj_CalcCrvLength::Values ref{
			std::move(integ),
				max_nb_subs,
				(ignore_non_conv == "yes" ? true : false),
				(shut_up_warnings == "yes" ? true : false),
				verbose
		};
		auto value = std::make_shared<Server_Cad2dObj_CalcCrvLength::Values>(std::move(ref));
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

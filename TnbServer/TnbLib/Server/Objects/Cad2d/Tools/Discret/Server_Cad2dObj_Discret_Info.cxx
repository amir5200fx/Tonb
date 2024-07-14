#include <Server_Cad2dObj_Discret_Info.hxx>

#include <Geo_ApprxCurve_Info.hxx>
#include <Geo_Tools.hxx>
#include <json.hpp>

const std::string tnbLib::Server_Cad2dObj_Discret_Info::Params::target = "target";
const std::string tnbLib::Server_Cad2dObj_Discret_Info::Params::min_size = "min_size";
const std::string tnbLib::Server_Cad2dObj_Discret_Info::Params::angle = "angle";
const std::string tnbLib::Server_Cad2dObj_Discret_Info::Params::nb_samples = "nb_samples";
const std::string tnbLib::Server_Cad2dObj_Discret_Info::Params::nb_inits = "nb_inits";
const std::string tnbLib::Server_Cad2dObj_Discret_Info::Params::max_nb_subs = "max_nb_subs";

void tnbLib::Server_Cad2dObj_Discret_Info::Construct(const std::string& theValue)
{
	double target = 0;
	double min_size = 0;
	double angle = 0;
	int nb_samples = 0;
	int nb_inits = 0;
	int max_nb_subs = 0;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(target);
		}
		{
			loadTnbServerObject(min_size);
		}
		{
			loadTnbServerObject(angle);
		}
		{
			loadTnbServerObject(nb_samples);
		}
		{
			loadTnbServerObject(nb_inits);
		}
		{
			loadTnbServerObject(max_nb_subs);
		}
	}
	auto value = std::make_shared<Geo_ApprxCurve_Info>();
	value->SetApprox(target);
	value->SetAngle(angle);
	value->SetMinSize(min_size);
	value->SetNbSamples(nb_samples);
	value->SetInitNbSubdivision(nb_inits);
	value->SetMaxNbSubdivision(max_nb_subs);
	streamGoodTnbServerObject(value);
}

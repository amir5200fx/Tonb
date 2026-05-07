#include <Server_ToolsObj_DiscrtShape2d.hxx>

#include <Geo_ApprxCurve_Info.hxx>
#include <Global_File.hxx>
#include <json.hpp>

const std::string tnbLib::Server_ToolsObj_DiscrtShape2d::Params::angle = "tools_discrete_shape_2d_angle";
const std::string tnbLib::Server_ToolsObj_DiscrtShape2d::Params::approx = "tools_discrete_shape_2d_approx";
const std::string tnbLib::Server_ToolsObj_DiscrtShape2d::Params::int_nb_subdivide = "tools_discrete_shape_2d_int_nb_subdivide";
const std::string tnbLib::Server_ToolsObj_DiscrtShape2d::Params::max_nb_subdivide = "tools_discrete_shape_2d_max_nb_subdivide";
const std::string tnbLib::Server_ToolsObj_DiscrtShape2d::Params::min_size = "tools_discrete_shape_2d_min_size";
const std::string tnbLib::Server_ToolsObj_DiscrtShape2d::Params::nb_samples = "tools_discrete_shape_2d_nb_samples";

void tnbLib::Server_ToolsObj_DiscrtShape2d::Construct(const std::string& theValue)
{
	double angle = 0;
	double approx = 0;
	double min_size = 0;
	int int_nb_subdivide = 0;
	int max_nb_subdivide = 0;
	int nb_samples = 0;
	{
		defineTnbServerParser(theValue);
		// loading the value of the angle:
		{
			loadTnbServerObject(angle);
		}
		// loading the value of the approx:
		{
			loadTnbServerObject(approx);
		}
		// loading the value of the min_size:
		{
			loadTnbServerObject(min_size);
		}
		// loading the value of the int_nb_subdivide
		{
			loadTnbServerObject(int_nb_subdivide);
		}
		// loading the value of the max_nb_subdivide
		{
			loadTnbServerObject(max_nb_subdivide);
		}
		// loading the value of the nb_samples
		{
			loadTnbServerObject(nb_samples);
		}
	}
	auto value = std::make_shared<Geo_ApprxCurve_Info>();
	value->SetAngle(angle);
	value->SetApprox(approx);
	value->SetInitNbSubdivision(int_nb_subdivide);
	value->SetMaxNbSubdivision(max_nb_subdivide);
	value->SetMinSize(min_size);
	value->SetNbSamples(nb_samples);
	streamGoodTnbServerObject(value);
}

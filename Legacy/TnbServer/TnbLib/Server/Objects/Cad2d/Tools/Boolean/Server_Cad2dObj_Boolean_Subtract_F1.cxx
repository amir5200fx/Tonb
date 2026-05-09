#include <Server_Cad2dObj_Boolean_Subtract_F1.hxx>

#include <Server_Error.hxx>
#include <Cad2d_Boolean.hxx>
#include <Cad2d_Plane.hxx>

#include <json.hpp>

const std::string tnbLib::Server_Cad2dObj_Boolean_Subtract_F1::Params::area = "area";
const std::string tnbLib::Server_Cad2dObj_Boolean_Subtract_F1::Params::name = "name";
const std::string tnbLib::Server_Cad2dObj_Boolean_Subtract_F1::Params::target = "target";
const std::string tnbLib::Server_Cad2dObj_Boolean_Subtract_F1::Params::tol = "tol";

void tnbLib::Server_Cad2dObj_Boolean_Subtract_F1::Construct(const std::string& theValue)
{
	double tol = 0;
	std::shared_ptr<Cad2d_Plane> area;
	std::shared_ptr<Cad2d_Plane> target;
	std::string name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(tol);
		}
		{
			loadTnbServerObject(area);
		}
		{
			loadTnbServerObject(target);
		}
		{
			name = loader.at(Params::name).get<std::string>();
		}
	}
	try
	{
		const auto results = Cad2d_Boolean::Subtract(target, area, tol);
		if (results.empty())
		{
			std::shared_ptr<Cad2d_Plane> value;
			streamWarningTnbServerObject(value, "no intersection has been found.");
		}
		else
		{
			if (results.size() != 1)
			{
				throw Server_Error("Multiple areas result is not supported.");
			}
			streamGoodTnbServerObject(results.at(0));
		}
	}
	catchTnbServerErrors()
}

void tnbLib::Server_Cad2dObj_Boolean_Subtract_F1::MakeEmpty()
{
	std::shared_ptr<Cad2d_Plane> value;
	streamGoodTnbServerObject(value);
}

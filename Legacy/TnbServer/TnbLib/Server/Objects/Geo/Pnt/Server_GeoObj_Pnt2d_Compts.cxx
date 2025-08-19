#include <Server_GeoObj_Pnt2d_Compts.hxx>

#include <Pnt2d.hxx>

#include <json.hpp>

void tnbLib::Server_GeoObj_Pnt2d_Compts::Construct(const std::string& theValue)
{
	double x = 0;
	double y = 0;
	{
		std::stringstream stream;
		stream << theValue;
		TNB_iARCH_FILE_TYPE ia(stream);
		Pnt2d value;
		ia >> value;
		x = value.X();
		y = value.Y();
	}
	nlohmann::json jData;
	jData["u0"] = x;
	jData["u1"] = y;
	std::stringstream stream;
	stream << jData;
	{
		nlohmann::json jData1;
		jData1[SENSE] = GetRespType(RespType::good);
		jData1[VALUE] = stream.str();
		theStream_ << jData1;
	}
}

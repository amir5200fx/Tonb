#include <Server_GeoObj_Vec2d_F1.hxx>

#include <Vec2d.hxx>
#include <Global_File.hxx>
#include <json.hpp>

const std::string tnbLib::Server_GeoObj_Vec2d_F1::Params::u = "u";
const std::string tnbLib::Server_GeoObj_Vec2d_F1::Params::v = "v";

void tnbLib::Server_GeoObj_Vec2d_F1::Construct(const std::string& theValue)
{
	double u = 0, v = 0;
	{
		nlohmann::json loader = nlohmann::json::parse(theValue);
		// loading the value of u:
		{
			std::stringstream stream;
			stream << loader.at(Params::u).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> u;
		}
		// loading the value of v:
		{
			std::stringstream stream;
			stream << loader.at(Params::v).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> v;
		}
	}
	// streaming the value
	std::stringstream stream;
	auto value = Vec2d(u, v);
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << value;
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}

implementTnbServerConstruction(Server_GeoObj_Vec2d_Cmpts)
{
	Vec2d d;
	{
		loadNonJSONTnbServer(d);
	}
	nlohmann::json jData;
	jData["u0"] = d.X();
	jData["u1"] = d.Y();
	std::stringstream stream;
	stream << jData;
	{
		nlohmann::json jData1;
		jData1[SENSE] = GetRespType(RespType::good);
		jData1[VALUE] = stream.str();
		theStream_ << jData1;
	}
}

implementTnbServerParam(Server_GeoObj_Vec2d_DotProduct, u0, "u0");
implementTnbServerParam(Server_GeoObj_Vec2d_DotProduct, u1, "u1");

implementTnbServerConstruction(Server_GeoObj_Vec2d_DotProduct)
{
	Vec2d u0, u1;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(u0);
		}
		{
			loadTnbServerObject(u1);
		}
		auto value = u0.Dot(u1);
		streamGoodTnbServerObject(value);
	}
}

implementTnbServerParam(Server_GeoObj_Vec2d_CrossProduct, u0, "u0");
implementTnbServerParam(Server_GeoObj_Vec2d_CrossProduct, u1, "u1");

implementTnbServerConstruction(Server_GeoObj_Vec2d_CrossProduct)
{
	Vec2d u0, u1;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(u0);
		}
		{
			loadTnbServerObject(u1);
		}
		auto value = u0.Crossed(u1);
		streamGoodTnbServerObject(value);
	}
}
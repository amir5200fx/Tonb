#include "Server_DirObj.hxx"

#include "../../Server.hxx"

#include <Dir2d.hxx>
#include <Global_File.hxx>
#include <json.hpp>

const std::string tnbLib::Server_DirObj::Params::u = "u";
const std::string tnbLib::Server_DirObj::Params::v = "v";

#include <Standard_Failure.hxx>

void tnbLib::Server_DirObj::Construct(const std::string& theValue)
{
	double u = 0, v = 0;
	{
		nlohmann::json loader = nlohmann::json::parse(theValue);
		// loading the value of x:
		{
			std::stringstream stream;
			stream << loader.at(Params::u).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> u;
		}
		// loading the value of y:
		{
			std::stringstream stream;
			stream << loader.at(Params::v).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> v;
		}
	}
	// streaming the value
	nlohmann::json jData;
	try
	{
		std::stringstream stream;
		auto value = Dir2d(u, v);
		TNB_oARCH_FILE_TYPE oa(stream);
		oa << value;
		jData[SENSE] = GetRespType(RespType::good);
		jData[VALUE] = stream.str();
	}
	catch (Standard_Failure& x)
	{
		jData[SENSE] = GetRespType(RespType::bad);
		jData[VALUE] = x.GetMessageString();
	}
	theStream_ << jData;
}

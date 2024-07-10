#include <Server_GlobalObj_Real.hxx>

#include <Global_File.hxx>
#include <json.hpp>

void tnbLib::Server_GlobalObj_Real::Construct(const std::string& theValue)
{
	std::stringstream stream;
	auto value = std::stod(theValue);
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << value;
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}

void tnbLib::Server_GlobalObj_Real_First::Construct(const std::string& theValue)
{
	auto value = RealFirst();
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = value;
	theStream_ << jData;
}

void tnbLib::Server_GlobalObj_Real_Last::Construct(const std::string& theValue)
{
	auto value = RealLast();
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = value;
	theStream_ << jData;
}


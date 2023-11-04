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

#include <Server_GlobalObj_Busy.hxx>

#include <Global_File.hxx>
#include <json.hpp>

void tnbLib::Server_GlobalObj_Busy::Construct(const std::string& theValue)
{
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = "im busy";
	theStream_ << jData;
}

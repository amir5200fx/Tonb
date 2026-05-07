#include "Server_ExitObj.hxx"

#include <Global_File.hxx>
#include <json.hpp>

void tnbLib::Server_ExitObj::Construct(const std::string&)
{
	std::stringstream stream;
	auto value = 0;
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << value;
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = std::to_string(0);
	theStream_ << jData;
}

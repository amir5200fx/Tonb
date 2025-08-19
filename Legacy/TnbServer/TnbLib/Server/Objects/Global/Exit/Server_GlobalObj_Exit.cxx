#include <Server_GlobalObj_Exit.hxx>

#include <Global_File.hxx>
#include <json.hpp>

void tnbLib::Server_GlobalObj_Exit::Construct(const std::string& theValue)
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

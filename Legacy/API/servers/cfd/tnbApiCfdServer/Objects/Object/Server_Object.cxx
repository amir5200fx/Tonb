#include "Server_Object.hxx"

#include <vector>

const std::string tnbLib::Server_Object::RESPONSE("resp");
const std::string tnbLib::Server_Object::SENSE("sense");
const std::string tnbLib::Server_Object::VALUE("value");

static const std::vector<std::string> RespTypesStrings = { "good", "bad", "warning" };

std::string tnbLib::Server_Object::GetRespType(const RespType theResp)
{
	return RespTypesStrings[static_cast<size_t>(theResp)];
}

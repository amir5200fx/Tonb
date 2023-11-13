#include <Server_Object.hxx>

#include <vector>

const std::string tnbLib::Server_Object::RESPONSE("resp");
const std::string tnbLib::Server_Object::SENSE("sense");
const std::string tnbLib::Server_Object::VALUE("value");
const std::string tnbLib::Server_Object::SERVER_MSG = "servmsg";

static const std::vector<std::string> RespTypesStrings = { "good", "bad", "warning" };

void tnbLib::Server_Object::MakeEmpty()
{
	// empty body
}

std::string tnbLib::Server_Object::GetRespType(const RespType theResp)
{
	return RespTypesStrings[static_cast<size_t>(theResp)];
}

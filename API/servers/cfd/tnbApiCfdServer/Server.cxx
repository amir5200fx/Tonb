#include "Server.hxx"

#include "Objects/Real/Server_RealObj.hxx"
#include "Objects/Int/Server_IntObj.hxx"
#include "Objects/Point/Server_PntObj.hxx"
#include "Objects/Dir/Server_DirObj.hxx"
#include "Objects/Vec/Server_VecObj.hxx"
#include "Objects/Axis/Server_AxisObj.hxx"
#include "Objects/Exit/Server_ExitObj.hxx"
#include "ServError.hxx"
#include "Socket.hxx"
#include "Tools.hxx"

#include <json.hpp>

const std::string tnbLib::Server::REQUEST = "req";
const std::string tnbLib::Server::RESPONSE = "resp";
const std::string tnbLib::Server::VALUE = "value";

void tnbLib::Server::CreateReal(const std::string& theValue)
{
	theObj_ = std::make_shared<Server_RealObj>();
	theObj_->Construct(theValue);
}

void tnbLib::Server::CreateInt(const std::string& theValue)
{
	theObj_ = std::make_shared<Server_IntObj>();
	theObj_->Construct(theValue);
}

void tnbLib::Server::CreatePnt(const std::string& theValue)
{
	theObj_ = std::make_shared<Server_PntObj>();
	theObj_->Construct(theValue);
}

void tnbLib::Server::CreateVec(const std::string& theValue)
{
	theObj_ = std::make_shared<Server_VecObj>();
	theObj_->Construct(theValue);
}

void tnbLib::Server::CreateDir(const std::string& theValue)
{
	theObj_ = std::make_shared<Server_DirObj>();
	theObj_->Construct(theValue);
}

void tnbLib::Server::CreateAxis(const std::string& theValue)
{
	theObj_ = std::make_shared<Server_AxisObj>();
	theObj_->Construct(theValue);
}

void tnbLib::Server::Construct
(
	const std::string& theCommand, 
	const std::string& theValue
)
{
	theCommand_ = theCommand;
	switch (Commands.at(theCommand))
	{
	case objects::integer:
	{
		CreateInt(theValue);
		break;
	}
	case objects::real:
	{
		CreateReal(theValue);
		break;
	}
	case objects::point:
	{
		CreatePnt(theValue);
		break;
	}
	case objects::dir:
	{
		CreateDir(theValue);
		break;
	}
	case objects::vector:
	{
		CreateVec(theValue);
		break;
	}
	case objects::axis:
	{
		CreateAxis(theValue);
		break;
	}
	case objects::exit:
	{
		theObj_ = std::make_shared<Server_ExitObj>();
		theObj_->Construct(theValue);
		break;
	}
	default:
	{
		throw ServError("No object constructor is existed for the command: " + theCommand);
	}
	}
}

void tnbLib::Server::SendObj(const std::shared_ptr<Socket>& theSocket) const
{
	int iSendResult = -1;
	while (iSendResult == -1)
	{
		std::stringstream stream;
		auto message = theObj_->Stream().str();
		nlohmann::json jData;
		jData[RESPONSE] = message;
		jData[REQUEST] = theCommand_;
		stream << jData;
		message = stream.str();
		message += Tools::END_MESSAGE;
		//std::cout << "sending message: " << message << std::endl;
		iSendResult = send(theSocket->Descriptor(), message.c_str(), static_cast<int>(message.size()), 0);
		Tools::WaitAMoment();
	}
	//std::cout << "the message has been sent!" << std::endl;
}

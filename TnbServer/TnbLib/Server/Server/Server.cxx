#include <Server.hxx>

#include <Server_Object.hxx>
#include <Server_Socket.hxx>
#include <Server_Tools.hxx>
#include <Server_Error.hxx>

#include <sstream>
#include <json.hpp>

const std::string tnbLib::Server::END_MESSAGE = ";;$";

const std::string tnbLib::Server::REQUEST = "req";
const std::string tnbLib::Server::RESPONSE = "resp";
const std::string tnbLib::Server::VALUE = "value";

void tnbLib::Server::Construct(const std::string& theCommand, const std::string& theValue)
{
	theCommand_ = theCommand;
	switch (Commands.at(theCommand))
	{

		// Global objects
		switchToMakeTnbServerObject(objects::make_int, create_int, theValue)
		switchToMakeTnbServerObject(objects::make_real, create_real, theValue)

		// geometric objects
		switchToMakeTnbServerObject(objects::make_pnt_2d, create_pnt_2d, theValue)
		switchToMakeTnbServerObject(objects::make_vec_2d_f1, create_vec_2d_f1, theValue)
		switchToMakeTnbServerObject(objects::make_dir_2d_f1, create_dir_2d_f1, theValue)
		switchToMakeTnbServerObject(objects::make_axis_2d, create_axis_2d, theValue)

		// cad objects
		switchToMakeTnbServerObject(objects::make_circle_2d_f1, make_circle_2d_f1, theValue)
		default:
			throw Server_Error("No object constructor is existed for the command: " + theCommand);
	}
}

void tnbLib::Server::SendObj(const std::shared_ptr<Server_Socket>& theSocket) const
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
		message += END_MESSAGE;
		//std::cout << "sending message: " << message << std::endl;
		iSendResult = send(theSocket->Descriptor(), message.c_str(), static_cast<int>(message.size()), 0);
		Server_Tools::WaitAMoment();
	}
}

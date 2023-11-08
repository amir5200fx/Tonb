#include <iostream>
#include <Server.hxx>

#include <Server_Object.hxx>
#include <Server_Socket.hxx>
#include <Server_Tools.hxx>
#include <Server_Error.hxx>

#include <sstream>
#include <json.hpp>

const std::string tnbLib::Server::END_MESSAGE = ";;$";

const std::string tnbLib::Server::REQUEST = "req";
const std::string tnbLib::Server::FLAG = "flag";
const std::string tnbLib::Server::RESPONSE = "resp";
const std::string tnbLib::Server::VALUE = "value";
const std::string tnbLib::Server::EMPTINESS = "empt";

void tnbLib::Server::Construct(const Command& theCommand, const Flag& theFlag, const Emptiness& theSense, const Value& theValue)
{
	theCommand_ = theCommand.stream;
	theFlag_ = theFlag.stream;
	const auto& value = theValue.stream;
	const auto& sense = theSense.stream;
	switch (Commands.at(theCommand_))
	{

		// Global objects
		switchToMakeTnbServerObject(objects::make_int, create_int, value, sense)
		switchToMakeTnbServerObject(objects::make_real, create_real, value, sense)
		switchToMakeTnbServerObject(objects::make_bool, create_bool, value, sense)

		// geometric objects
		switchToMakeTnbServerObject(objects::make_pnt_2d_f1, create_pnt_2d_f1, value, sense)
		switchToMakeTnbServerObject(objects::make_vec_2d_f1, create_vec_2d_f1, value, sense, sense)
		switchToMakeTnbServerObject(objects::make_dir_2d_f1, create_dir_2d_f1, value, sense, sense)
		switchToMakeTnbServerObject(objects::make_axis_2d_f1, create_axis_2d_f1, value, sense)

		switchToMakeTnbServerObject(objects::make_pnt_2d_list, make_pnt_2d_list, value, sense)

		// cad objects
		switchToMakeTnbServerObject(objects::make_circle_2d_f1, make_circle_2d_f1, value, sense)
		switchToMakeTnbServerObject(objects::make_rectangular_2d_f1, make_rectangular_2d_f1, value, sense)
		switchToMakeTnbServerObject(objects::make_segment_2d_f1, make_segment_2d_f1, value, sense)

		switchToMakeTnbServerObject(objects::make_curve_2d_list, make_curve_2d_list, value, sense)
		switchToMakeTnbServerObject(objects::make_area_2d, make_area_2d, value, sense)

		switchToMakeTnbServerObject(objects::make_interpl_curve_2d, make_interpl_curve_2d, value, sense)

		// tools
		switchToMakeTnbServerObject(objects::make_discrete_shape_info_2d, make_discrete_shape_info_2d, value, sense)
		switchToMakeTnbServerObject(objects::do_discret_2d, do_discret_2d, value, sense)
		switchToMakeTnbServerObject(objects::do_boolean_sub_2d, do_boolean_sub_2d, value, sense)
		// make an exit
		switchToMakeTnbServerObject(objects::exit, exit, value, sense)
		default:
			throw Server_Error("No object constructor is existed for the command: " + theCommand_);
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
		jData[REQUEST] = theCommand_;
		jData[FLAG] = theFlag_;
		jData[RESPONSE] = message;
		stream << jData;
		message = stream.str();
		message += END_MESSAGE;
		//std::cout << "sending message: " << message << std::endl;
		iSendResult = send(theSocket->Descriptor(), message.c_str(), static_cast<int>(message.size()), 0);
		Server_Tools::WaitAMoment();
	}
}

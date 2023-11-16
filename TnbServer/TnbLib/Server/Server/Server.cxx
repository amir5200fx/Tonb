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

		switchToMakeTnbServerObject(objects::retrv_compts_pnt_2d, retv_compts_pnt_2d, value, sense)

		switchToMakeTnbServerObject(objects::make_pnt_2d_list, make_pnt_2d_list, value, sense)

		// cad objects
		switchToMakeTnbServerObject(objects::retv_first_parameter_curve_2d, retv_first_parameter_curve_2d, value, sense)
		switchToMakeTnbServerObject(objects::retv_last_parameter_curve_2d, retv_last_parameter_curve_2d, value, sense)
		switchToMakeTnbServerObject(objects::calc_pnt_curve_2d, calc_pnt_curve_2d, value, sense)
		switchToMakeTnbServerObject(objects::prj_pnt_curve_2d, prj_pnt_curve_2d, value, sense)
		switchToMakeTnbServerObject(objects::rev_curve_2d, rev_curve_2d, value, sense)
		switchToMakeTnbServerObject(objects::make_circle_2d_f1, make_circle_2d_f1, value, sense)
		switchToMakeTnbServerObject(objects::make_rectangular_2d_f1, make_rectangular_2d_f1, value, sense)
		switchToMakeTnbServerObject(objects::make_segment_2d_f1, make_segment_2d_f1, value, sense)

			switchToMakeTnbServerObject(objects::retv_area_2d_blocks, retv_area_2d_blocks, value, sense)
			switchToMakeTnbServerObject(objects::retv_area_2d_block_curves, retv_area_2d_block_curves, value, sense)
			switchToMakeTnbServerObject(objects::combine_area_2d_blocks, combine_area_2d_blocks, value, sense)
	case objects::split_area_2d_block: { std::cout << "selected RIGHT" << std::endl; split_area_2d_block(value, sense); break; }
		switchToMakeTnbServerObject(objects::rename_area_2d_block, rename_area_2d_block, value, sense)

			switchToMakeTnbServerObject(objects::make_curve_2d_list, make_curve_2d_list, value, sense)
			switchToMakeTnbServerObject(objects::make_area_2d, make_area_2d, value, sense)

			switchToMakeTnbServerObject(objects::make_interpl_curve_2d, make_interpl_curve_2d, value, sense)


			// geo lib

			switchToMakeTnbServerObject(objects::make_bnd_box_2d, make_bnd_box_2d, value, sense)
			switchToMakeTnbServerObject(objects::calc_bnd_box_2d_pnt_list, calc_bnd_box_2d_pnt_list, value, sense)
			switchToMakeTnbServerObject(objects::calc_bnd_box_2d_curve, calc_bnd_box_2d_curve, value, sense)
			switchToMakeTnbServerObject(objects::calc_bnd_box_2d_crv_list, calc_bnd_box_2d_crv_list, value, sense)
			switchToMakeTnbServerObject(objects::calc_bnd_box_2d_area, calc_bnd_box_2d_area, value, sense)
			switchToMakeTnbServerObject(objects::calc_bnd_box_2d_area_list, calc_bnd_box_2d_area_list, value, sense)


		switchToMakeTnbServerObject(objects::do_bnd_box_2d_expand, do_bnd_box_2d_expand, value, sense)
		switchToMakeTnbServerObject(objects::get_bnd_box_2d_dia, get_bnd_box_2d_dia, value, sense)
		switchToMakeTnbServerObject(objects::get_bnd_box_2d_lengths, get_bnd_box_2d_lengths, value, sense)

		switchToMakeTnbServerObject(objects::make_size_map_2d_uniform, make_size_map_2d_uniform, value, sense)
			// Mesh lib
			switchToMakeTnbServerObject(objects::make_mesh_ref_values_2d, make_mesh_ref_values_2d, value, sense)
		switchToMakeTnbServerObject(objects::make_metric_prcsr_2d_settings, make_metric_prcsr_2d_settings, value, sense)
		switchToMakeTnbServerObject(objects::make_metric_prcsr_2d, make_metric_prcsr_2d, value, sense)
		// Num lib

		switchToMakeTnbServerObject(objects::make_num_adapt_integ, make_num_adapt_integ, value, sense)

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

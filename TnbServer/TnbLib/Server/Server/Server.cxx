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
	//std::cout << "I recieved the command!\n";
	theCommand_ = theCommand.stream;
	theFlag_ = theFlag.stream;
	const auto& value = theValue.stream;
	const auto& sense = theSense.stream;
	switch (Commands.at(theCommand_))
	{

		// Global objects
		switchToMakeTnbServerObject(objects::make_int, create_int, value, sense)
		switchToMakeTnbServerObject(objects::make_real, create_real, value, sense)
		switchToMakeTnbServerObject(objects::make_real_first, make_real_first, value, sense)
		switchToMakeTnbServerObject(objects::make_real_last, make_real_last, value, sense)
		switchToMakeTnbServerObject(objects::make_bool, create_bool, value, sense)

		// geometric objects
		switchToMakeTnbServerObject(objects::make_pnt_2d_f1, create_pnt_2d_f1, value, sense)
		switchToMakeTnbServerObject(objects::make_vec_2d_f1, create_vec_2d_f1, value, sense, sense)
		switchToMakeTnbServerObject(objects::make_dir_2d_f1, create_dir_2d_f1, value, sense, sense)
		switchToMakeTnbServerObject(objects::make_axis_2d_f1, create_axis_2d_f1, value, sense)

		switchToMakeTnbServerObject(objects::retrv_compts_pnt_2d, retv_compts_pnt_2d, value, sense)
		switchToMakeTnbServerObject(objects::retv_compts_vec_2d, retv_compts_vec_2d, value, sense)
		switchToMakeTnbServerObject(objects::pnt_2d_trsf, pnt_2d_trsf, value, sense)

		switchToMakeTnbServerObject(objects::make_pnt_2d_list, make_pnt_2d_list, value, sense)

		switchToMakeTnbServerObject(objects::make_ray_2d_f1, make_ray_2d_f1, value, sense)


		// transformatiosn

		switchToMakeTnbServerObject(objects::make_trsf_2d, make_trsf_2d, value, sense)
		switchToMakeTnbServerObject(objects::trsf_2d_mirror_by_pnt, trsf_2d_mirror_by_pnt, value, sense)
		switchToMakeTnbServerObject(objects::trsf_2d_mirror_by_axis, trsf_2d_mirror_by_axis, value, sense)
		switchToMakeTnbServerObject(objects::trsf_2d_rotation, trsf_2d_rotation, value, sense)
		switchToMakeTnbServerObject(objects::trsf_2d_scale, trsf_2d_scale, value, sense)
		switchToMakeTnbServerObject(objects::trsf_2d_transform_from_s1_to_s2, trsf_2d_transform_from_s1_to_s2, value, sense)
		switchToMakeTnbServerObject(objects::trsf_2d_transform_to, trsf_2d_transform_to, value, sense)
		switchToMakeTnbServerObject(objects::trsf_2d_translation, trsf_2d_translation, value, sense)
		switchToMakeTnbServerObject(objects::trsf_2d_values, trsf_2d_values, value, sense)
		// cad objects
		switchToMakeTnbServerObject(objects::retv_first_parameter_curve_2d, retv_first_parameter_curve_2d, value, sense)
		switchToMakeTnbServerObject(objects::retv_last_parameter_curve_2d, retv_last_parameter_curve_2d, value, sense)
		switchToMakeTnbServerObject(objects::calc_pnt_curve_2d, calc_pnt_curve_2d, value, sense)
		switchToMakeTnbServerObject(objects::calc_d1_curve_2d, calc_d1_curve_2d, value, sense)
		switchToMakeTnbServerObject(objects::prj_pnt_curve_2d, prj_pnt_curve_2d, value, sense)
		switchToMakeTnbServerObject(objects::rev_curve_2d, rev_curve_2d, value, sense)
		switchToMakeTnbServerObject(objects::trim_curve_2d, trim_curve_2d, value, sense)
		switchToMakeTnbServerObject(objects::set_name_curve_2d, set_name_curve_2d, value, sense)
		switchToMakeTnbServerObject(objects::make_circle_2d_f1, make_circle_2d_f1, value, sense)
		switchToMakeTnbServerObject(objects::make_ellipse_2d_f1, make_ellipse_2d_f1, value, sense)
		switchToMakeTnbServerObject(objects::make_rectangular_2d_f1, make_rectangular_2d_f1, value, sense)
		switchToMakeTnbServerObject(objects::make_segment_2d_f1, make_segment_2d_f1, value, sense)
		switchToMakeTnbServerObject(objects::curve_2d_get_iden, curve_2d_get_iden, value, sense)

			switchToMakeTnbServerObject(objects::retv_area_2d_blocks, retv_area_2d_blocks, value, sense)
			switchToMakeTnbServerObject(objects::retv_area_2d_block_curves, retv_area_2d_block_curves, value, sense)
			switchToMakeTnbServerObject(objects::combine_area_2d_blocks, combine_area_2d_blocks, value, sense)
		switchToMakeTnbServerObject(objects::combine_all_area_blocks, combine_all_area_blocks, value, sense)
	case objects::split_area_2d_block: { split_area_2d_block(value, sense); break; }
		switchToMakeTnbServerObject(objects::rename_area_2d_block, rename_area_2d_block, value, sense)
		switchToMakeTnbServerObject(objects::area_get_curves, area_get_curves, value, sense)
		switchToMakeTnbServerObject(objects::area_2d_get_outer_poly, area_2d_get_outer_poly, value, sense)
		switchToMakeTnbServerObject(objects::area_2d_trsf, area_2d_trsf, value, sense)

			switchToMakeTnbServerObject(objects::make_curve_2d_list, make_curve_2d_list, value, sense)
			switchToMakeTnbServerObject(objects::make_area_2d, make_area_2d, value, sense)

			switchToMakeTnbServerObject(objects::make_interpl_curve_2d, make_interpl_curve_2d, value, sense)


			// geo lib

		switchToMakeTnbServerObject(objects::calc_ray_2d_int_pnt, calc_ray_2d_int_pnt, value, sense)

		switchToMakeTnbServerObject(objects::vec2d_dot, vec2d_dot, value, sense)
		switchToMakeTnbServerObject(objects::vec2d_cross, vec2d_cross, value, sense)



			switchToMakeTnbServerObject(objects::make_bnd_box_2d, make_bnd_box_2d, value, sense)
			switchToMakeTnbServerObject(objects::calc_bnd_box_2d_pnt_list, calc_bnd_box_2d_pnt_list, value, sense)
			switchToMakeTnbServerObject(objects::calc_bnd_box_2d_curve, calc_bnd_box_2d_curve, value, sense)
			switchToMakeTnbServerObject(objects::calc_bnd_box_2d_crv_list, calc_bnd_box_2d_crv_list, value, sense)
			switchToMakeTnbServerObject(objects::calc_bnd_box_2d_area, calc_bnd_box_2d_area, value, sense)
			switchToMakeTnbServerObject(objects::calc_bnd_box_2d_area_list, calc_bnd_box_2d_area_list, value, sense)

		switchToMakeTnbServerObject(objects::poly_2d_rev, poly_2d_rev, value, sense)

		switchToMakeTnbServerObject(objects::do_bnd_box_2d_expand, do_bnd_box_2d_expand, value, sense)
		switchToMakeTnbServerObject(objects::get_bnd_box_2d_dia, get_bnd_box_2d_dia, value, sense)
		switchToMakeTnbServerObject(objects::get_bnd_box_2d_lengths, get_bnd_box_2d_lengths, value, sense)
		switchToMakeTnbServerObject(objects::get_bnd_box_2d_p0, get_bnd_box_2d_p0, value, sense)
		switchToMakeTnbServerObject(objects::get_bnd_box_2d_p1, get_bnd_box_2d_p1, value, sense)
		switchToMakeTnbServerObject(objects::get_bnd_box_2d_corners, get_bnd_box_2d_corners, value, sense)

		switchToMakeTnbServerObject(objects::make_size_map_2d_uniform, make_size_map_2d_uniform, value, sense)

		// adaptive size map stuff
		switchToMakeTnbServerObject(objects::make_size_map_2d_vol_f1, make_size_map_2d_vol_f1, value, sense)
		switchToMakeTnbServerObject(objects::make_size_map_2d_vol_f2, make_size_map_2d_vol_f2, value, sense)
		
		switchToMakeTnbServerObject(objects::make_size_map_2d_adaptive, make_size_map_2d_adaptive, value, sense)

		switchToMakeTnbServerObject(objects::make_vol_size_map_2d_ctrl, make_vol_size_map_2d_ctrl, value, sense)
			switchToMakeTnbServerObject(objects::make_bnd_size_map_2d_ctrl, make_bnd_size_map_2d_ctrl, value, sense)

		switchToMakeTnbServerObject(objects::perform_size_map_2d_adaptive, perform_size_map_2d_adaptive, value, sense)
		switchToMakeTnbServerObject(objects::vol_size_map_2d_ctrl_import_shape, vol_size_map_2d_ctrl_import_shape, value, sense)
		switchToMakeTnbServerObject(objects::vol_size_map_2d_ctrl_get_condition, vol_size_map_2d_ctrl_get_condition, value, sense)
		switchToMakeTnbServerObject(objects::vol_size_map_2d_ctrl_get_values, vol_size_map_2d_ctrl_get_values, value, sense)
		switchToMakeTnbServerObject(objects::vol_size_map_2d_ctrl_values_set_gr, vol_size_map_2d_ctrl_values_set_gr, value, sense)
switchToMakeTnbServerObject(objects::vol_size_map_2d_ctrl_values_get_size, vol_size_map_2d_ctrl_values_get_size, value, sense)
switchToMakeTnbServerObject(objects::vol_size_map_2d_ctrl_size_value_target, vol_size_map_2d_ctrl_size_value_target, value, sense)
switchToMakeTnbServerObject(objects::vol_size_map_2d_ctrl_size_value_type, vol_size_map_2d_ctrl_size_value_type, value, sense)
		switchToMakeTnbServerObject(objects::make_approx_curve_2d_settings, make_approx_curve_2d_settings, value, sense)

		// Mesh lib
			switchToMakeTnbServerObject(objects::make_mesh_ref_values_2d, make_mesh_ref_values_2d, value, sense)
		switchToMakeTnbServerObject(objects::make_metric_prcsr_2d_settings, make_metric_prcsr_2d_settings, value, sense)
		switchToMakeTnbServerObject(objects::make_metric_prcsr_2d, make_metric_prcsr_2d, value, sense)

		switchToMakeTnbServerObject(objects::make_mesh_curve_2d_opt_point_settings, make_mesh_curve_2d_opt_point_settings, value, sense)
		switchToMakeTnbServerObject(objects::make_mesh_curve_2d_settings, make_mesh_curve_2d_settings, value, sense)
		switchToMakeTnbServerObject(objects::do_mesh_curve_2d, do_mesh_curve_2d, value, sense)

		switchToMakeTnbServerObject(objects::make_mesh_2d_solu_data, make_mesh_2d_solu_data, value, sense)
		switchToMakeTnbServerObject(objects::make_mesh_2d_region, make_mesh_2d_region, value, sense)
		switchToMakeTnbServerObject(objects::make_mesh_2d_node_gen_std, make_mesh_2d_node_gen_std, value, sense)
		switchToMakeTnbServerObject(objects::do_mesh_2d_bnd, do_mesh_2d_bnd, value, sense)
		switchToMakeTnbServerObject(objects::do_mesh_2d, do_mesh_2d, value, sense)
		switchToMakeTnbServerObject(objects::do_mesh_2d_laplac_smooth, do_mesh_2d_laplac_smooth, value, sense)

		switchToMakeTnbServerObject(objects::do_mesh_2d_bnd_layer_f1, do_mesh_2d_bnd_layer_f1, value, sense)

		switchToMakeTnbServerObject(objects::extrude_mesh_2d_fea, extrude_mesh_2d_fea, value, sense)
		switchToMakeTnbServerObject(objects::make_size_map_2d_ctrl_vol, make_size_map_2d_ctrl_vol, value, sense)
		switchToMakeTnbServerObject(objects::make_size_map_2d_ctrl_bnd, make_size_map_2d_ctrl_bnd, value, sense)

		// post mesh

		switchToMakeTnbServerObject(objects::make_mesh_2d_qual_fun_vlrms2ratio, make_mesh_2d_qual_fun_vlrms2ratio, value, sense)
		switchToMakeTnbServerObject(objects::make_mesh_2d_laplac_smooth_ang_fun_adj_edges, make_mesh_2d_laplac_smooth_ang_fun_adj_edges, value, sense)

		// Num lib

		switchToMakeTnbServerObject(objects::make_num_adapt_integ, make_num_adapt_integ, value, sense)
		switchToMakeTnbServerObject(objects::make_num_newton_solver, make_num_newton_solver, value, sense)
			switchToMakeTnbServerObject(objects::make_num_bisect_solver, make_num_bisect_solver, value, sense)

		// tools
		switchToMakeTnbServerObject(objects::make_discrete_shape_info_2d, make_discrete_shape_info_2d, value, sense)
		switchToMakeTnbServerObject(objects::do_discret_2d, do_discret_2d, value, sense)
		switchToMakeTnbServerObject(objects::do_boolean_sub_2d, do_boolean_sub_2d, value, sense)

		// io
		switchToMakeTnbServerObject(objects::export_tri_2d_to_plt, export_tri_2d_to_plt, value, sense)
		switchToMakeTnbServerObject(objects::export_curve_2d_to_plt, export_curve_2d_to_plt, value, sense)
		switchToMakeTnbServerObject(objects::export_area_to_plt, export_area_to_plt, value, sense)
		//switchToMakeTnbServerObject(objects::export_mesh_2d_to_plt, export_mesh_2d_to_plt, value, sense)
		switchToMakeTnbServerObject(objects::export_mesh_2d_solu_data_to_plt, export_mesh_2d_solu_data_to_plt, value, sense)
		switchToMakeTnbServerObject(objects::export_mesh_2d_to_fea, export_mesh_2d_to_fea, value, sense)
		switchToMakeTnbServerObject(objects::export_mesh_fv_to_unv, export_mesh_fv_to_unv, value, sense)

		switchToMakeTnbServerObject(objects::load_openfoam_init_cnds, load_openfoam_init_cnds, value, sense)
		switchToMakeTnbServerObject(objects::load_openfoam_bcs, load_openfoam_bcs, value, sense)
		switchToMakeTnbServerObject(objects::write_openfoam_init_cnds, write_openfoam_init_cnds, value, sense)
		switchToMakeTnbServerObject(objects::write_openfoam_bcs, write_openfoam_bcs, value, sense)
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

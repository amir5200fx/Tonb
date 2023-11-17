#include <Server.hxx>

std::map<std::string, tnbLib::Server::objects> tnbLib::Server::Commands;

using namespace tnbLib;

#include <Server_GlobalObj_Int.hxx>
#include <Server_GlobalObj_Real.hxx>
#include <Server_GlobalObj_Bool.hxx>
#include <Server_GeoObj_Pnt2d_F1.hxx>
#include <Server_GeoObj_Pnt2d_Compts.hxx>
#include <Server_GeoObj_Vec2d_F1.hxx>
#include <Server_GeoObj_Dir2d_F1.hxx>
#include <Server_GeoObj_Axis2d_F1.hxx>

// the interger object
defineAndRegisterTnbServerObject(Server_GlobalObj_Int, Server::objects::make_int, "make_int");
defineAndRegisterTnbServerObject(Server_GlobalObj_Real, Server::objects::make_real, "make_real");
defineAndRegisterTnbServerObject(Server_GlobalObj_Bool, Server::objects::make_bool, "make_bool");
defineAndRegisterTnbServerObject(Server_GeoObj_Pnt2d_F1, Server::objects::make_pnt_2d_f1, "make_pnt_2d_f1");
defineAndRegisterTnbServerObject(Server_GeoObj_Vec2d_F1, Server::objects::make_vec_2d_f1, "make_vec_2d_f1");
defineAndRegisterTnbServerObject(Server_GeoObj_Dir2d_F1, Server::objects::make_dir_2d_f1, "make_dir_2d_f1");
defineAndRegisterTnbServerObject(Server_GeoObj_Axis2d_F1, Server::objects::make_axis_2d_f1, "make_axis_2d_f1");

defineAndRegisterTnbServerObject(Server_GeoObj_Pnt2d_Compts, Server::objects::retrv_compts_pnt_2d, "retrv_compts_pnt_2d");

#include <Server_GeoObj_Pnt2d_List.hxx>
defineAndRegisterTnbServerObject(Server_GeoObj_Pnt2d_List, Server::objects::make_pnt_2d_list, "make_pnt_2d_list");

#include <Server_Cad2dObj_Discret_Info.hxx>
#include <Server_Cad2dObj_Discret.hxx>
#include <Server_Cad2dObj_Boolean_Subtract_F1.hxx>
defineAndRegisterTnbServerObject(Server_Cad2dObj_Discret_Info, Server::objects::make_discrete_shape_info_2d, "make_discrete_shape_info_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Discret, Server::objects::do_discret_2d, "do_discret_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Boolean_Subtract_F1, Server::objects::do_boolean_sub_2d, "do_boolean_sub_2d");

#include <Server_Cad2dObj_Segment2d_F1.hxx>
#include <Server_Cad2dObj_Circle_F1.hxx>
#include <Server_Cad2dObj_Rectangular_F1.hxx>
#include <Server_Cad2dObj_Interpl_F1.hxx>
#include <Server_Cad2dObj_Curve_List.hxx>
#include <Server_Cad2dObj_PrjPntCrv.hxx>
#include <Server_Cad2dObj_FirstParCurve.hxx>
#include <Server_Cad2dObj_LastParCurve.hxx>
#include <Server_Cad2dObj_CalcPntOnCurve.hxx>
#include <Server_Cad2dObj_RevCrv.hxx>
#include <Server_Cad2dObj_Area_F1.hxx>
#include <Server_Cad2dObj_Area_Manager.hxx>
defineAndRegisterTnbServerObject(Server_Cad2dObj_Circle_F1, Server::objects::make_circle_2d_f1, "make_circle_2d_f1");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Rectangular_F1, Server::objects::make_rectangular_2d_f1, "make_rectangular_2d_f1");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Interpl_F1, Server::objects::make_interpl_curve_2d, "make_interpl_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Segment2d_F1, Server::objects::make_segment_2d_f1, "make_segment_2d_f1");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Curve_List, Server::objects::make_curve_2d_list, "make_curve_2d_list");
defineAndRegisterTnbServerObject(Server_Cad2dObj_FirstParCurve, Server::objects::retv_first_parameter_curve_2d, "retv_first_parameter_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_LastParCurve, Server::objects::retv_last_parameter_curve_2d, "retv_last_parameter_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_CalcPntOnCurve, Server::objects::calc_pnt_curve_2d, "calc_pnt_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_PrjPntCrv, Server::objects::prj_pnt_curve_2d, "prj_pnt_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_RevCrv, Server::objects::rev_curve_2d, "make_rev_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_F1, Server::objects::make_area_2d, "make_area_2d");

defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_Manager_Segments, Server::objects::retv_area_2d_blocks, "retv_area_2d_blocks");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_Manager_Segments_BlockCurves, Server::objects::retv_area_2d_block_curves, "retv_area_2d_block_curves");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_Manager_Segments_CombineBlocks, Server::objects::combine_area_2d_blocks, "combine_area_2d_blocks");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_Manager_Segments_RenameBlock, Server::objects::rename_area_2d_block, "rename_area_2d_block");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_Manager_Segments_SplitBlock, Server::objects::split_area_2d_block, "split_area_2d_block");

// geo lib
#include <Server_Geo2dObj_BndBox.hxx>
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_Create, Server::objects::make_bnd_box_2d, "make_bnd_box_2d");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_PntList, Server::objects::calc_bnd_box_2d_pnt_list, "calc_bnd_box_2d_pnt_list");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_Curve, Server::objects::calc_bnd_box_2d_curve, "calc_bnd_box_2d_curve");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_CrvList, Server::objects::calc_bnd_box_2d_crv_list, "calc_bnd_box_2d_crv_list");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_Area, Server::objects::calc_bnd_box_2d_area, "calc_bnd_box_2d_area");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_AreaList, Server::objects::calc_bnd_box_2d_area_list, "calc_bnd_box_2d_area_list");

defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_Expand, Server::objects::do_bnd_box_2d_expand, "do_bnd_box_2d_expand");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_GetDia, Server::objects::get_bnd_box_2d_dia, "get_bnd_box_2d_dia");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_GetLengths, Server::objects::get_bnd_box_2d_lengths, "get_bnd_box_2d_lengths");

#include <Server_Geo2dObj.hxx>
defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_Uniform, Server::objects::make_size_map_2d_uniform, "make_size_map_2d_uniform");

// mesh lib

#include <Server_Mesh2dObj.hxx>
defineAndRegisterTnbServerObject(Server_Mesh2dObj_RefValues, Server::objects::make_mesh_ref_values_2d, "make_mesh_ref_values_2d");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_MetricPrcsr_Settings, Server::objects::make_metric_prcsr_2d_settings, "make_metric_prcsr_2d_settings");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_MetricPrcsr, Server::objects::make_metric_prcsr_2d, "make_metric_prcsr_2d");

defineAndRegisterTnbServerObject(Server_Mesh2dObj_Mesh_Curve_OptPoint, Server::objects::make_mesh_curve_2d_opt_point_settings, "make_mesh_curve_2d_opt_point_settings");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_Mesh_Curve_Settings, Server::objects::make_mesh_curve_2d_settings, "make_mesh_curve_2d_settings");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_Mesh_Curve, Server::objects::do_mesh_curve_2d, "do_mesh_curve_2d");

defineAndRegisterTnbServerObject(Server_Mesh2dObj_SoluData, Server::objects::make_mesh_2d_solu_data, "make_mesh_2d_solu_data");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_Region, Server::objects::make_mesh_2d_region, "make_mesh_2d_region");

// Num lib
#include <Server_NumObj_AdaptInteg_Info.hxx>
#include <Server_NumObj_NewtonNonLinSolver_Info.hxx>
#include <Server_NumObj_BisectNonLinSolver_Info.hxx>
defineAndRegisterTnbServerObject(Server_NumObj_AdaptInteg_Info, Server::objects::make_num_adapt_integ, "make_num_adapt_integ");
defineAndRegisterTnbServerObject(Server_NumObj_NewtonNonLinSolver_Info, Server::objects::make_num_newton_solver, "make_num_newton_solver");
defineAndRegisterTnbServerObject(Server_NumObj_BisectNonLinSolver_Info, Server::objects::make_num_bisect_solver, "make_num_bisect_solver");

#include <Server_GlobalObj_Exit.hxx>
defineAndRegisterTnbServerObject(Server_GlobalObj_Exit, Server::objects::exit, "EXIT");
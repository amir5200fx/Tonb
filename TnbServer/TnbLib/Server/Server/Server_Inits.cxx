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

#include <Server_GlobalObj_Exit.hxx>
defineAndRegisterTnbServerObject(Server_GlobalObj_Exit, Server::objects::exit, "EXIT");
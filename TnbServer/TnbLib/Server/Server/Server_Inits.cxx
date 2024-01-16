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
#include <Server_GeoObj_Ray2d.hxx>
#include <Server_MeshObj.hxx>
#include <Server_GeoObj_Ray2d.hxx>

// the interger object
defineAndRegisterTnbServerObject(Server_GlobalObj_Int, Server::objects::make_int, "make_int");
defineAndRegisterTnbServerObject(Server_GlobalObj_Real, Server::objects::make_real, "make_real");
defineAndRegisterTnbServerObject(Server_GlobalObj_Real_First, Server::objects::make_real_first, "make_real_first");
defineAndRegisterTnbServerObject(Server_GlobalObj_Real_Last, Server::objects::make_real_last, "make_real_last");
defineAndRegisterTnbServerObject(Server_GlobalObj_Bool, Server::objects::make_bool, "make_bool");
defineAndRegisterTnbServerObject(Server_GeoObj_Pnt2d_F1, Server::objects::make_pnt_2d_f1, "make_pnt_2d_f1");
defineAndRegisterTnbServerObject(Server_GeoObj_Vec2d_F1, Server::objects::make_vec_2d_f1, "make_vec_2d_f1");
defineAndRegisterTnbServerObject(Server_GeoObj_Dir2d_F1, Server::objects::make_dir_2d_f1, "make_dir_2d_f1");
defineAndRegisterTnbServerObject(Server_GeoObj_Axis2d_F1, Server::objects::make_axis_2d_f1, "make_axis_2d_f1");

defineAndRegisterTnbServerObject(Server_GeoObj_Ray2d, Server::objects::make_ray_2d, "make_ray_2d");

defineAndRegisterTnbServerObject(Server_GeoObj_Pnt2d_Compts, Server::objects::retrv_compts_pnt_2d, "retrv_compts_pnt_2d");
defineAndRegisterTnbServerObject(Server_GeoObj_Vec2d_Cmpts, Server::objects::retv_compts_vec_2d, "retv_compts_vec_2d");

defineAndRegisterTnbServerObject(Server_GeoObj_Ray2d, Server::objects::make_ray_2d_f1, "make_ray_2d_f1");
defineAndRegisterTnbServerObject(Server_GeoObj_Ray2d_Int, Server::objects::calc_ray_2d_int_pnt, "calc_ray_2d_int_pnt");

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
#include <Server_Cad2dObj_Ellipse_F1.hxx>
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
#include <Server_Cad2dObj_Curve.hxx>
defineAndRegisterTnbServerObject(Server_Cad2dObj_Circle_F1, Server::objects::make_circle_2d_f1, "make_circle_2d_f1");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Ellipse_F1, Server::objects::make_ellipse_2d_f1, "make_ellipse_2d_f1");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Rectangular_F1, Server::objects::make_rectangular_2d_f1, "make_rectangular_2d_f1");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Interpl_F1, Server::objects::make_interpl_curve_2d, "make_interpl_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Segment2d_F1, Server::objects::make_segment_2d_f1, "make_segment_2d_f1");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Curve_List, Server::objects::make_curve_2d_list, "make_curve_2d_list");
defineAndRegisterTnbServerObject(Server_Cad2dObj_FirstParCurve, Server::objects::retv_first_parameter_curve_2d, "retv_first_parameter_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_LastParCurve, Server::objects::retv_last_parameter_curve_2d, "retv_last_parameter_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_CalcPntOnCurve, Server::objects::calc_pnt_curve_2d, "calc_pnt_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Curve_D1, Server::objects::calc_d1_curve_2d, "calc_d1_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_PrjPntCrv, Server::objects::prj_pnt_curve_2d, "prj_pnt_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_RevCrv, Server::objects::rev_curve_2d, "make_rev_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Curve_Trim, Server::objects::trim_curve_2d, "trim_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Curve_SetName, Server::objects::set_name_curve_2d, "set_name_curve_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Curve_GetIdent, Server::objects::curve_2d_get_iden, "curve_2d_get_iden");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_F1, Server::objects::make_area_2d, "make_area_2d");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_GetCurves, Server::objects::area_get_curves, "area_get_curves");

defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_Manager_Segments, Server::objects::retv_area_2d_blocks, "retv_area_2d_blocks");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_Manager_Segments_BlockCurves, Server::objects::retv_area_2d_block_curves, "retv_area_2d_block_curves");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_Manager_Segments_CombineBlocks, Server::objects::combine_area_2d_blocks, "combine_area_2d_blocks");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_Manager_CombineAll, Server::objects::combine_all_area_blocks, "combine_all_area_blocks");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_Manager_Segments_RenameBlock, Server::objects::rename_area_2d_block, "rename_area_2d_block");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_Manager_Segments_SplitBlock, Server::objects::split_area_2d_block, "split_area_2d_block");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_GetOuterPolygon, Server::objects::area_2d_get_outer_poly, "area_2d_get_outer_poly");

// geo lib

defineAndRegisterTnbServerObject(Server_GeoObj_Ray2d_Intersect, Server::objects::calc_ray_2d_intsect, "calc_ray_2d_intsect");

#include <Server_Geo2dObj_BndBox.hxx>
#include <Server_Geo2dObj.hxx>

defineAndRegisterTnbServerObject(Server_Geo2dObj_RevPoly, Server::objects::poly_2d_rev, "poly_2d_rev");

defineAndRegisterTnbServerObject(Server_GeoObj_Vec2d_DotProduct, Server::objects::vec2d_dot, "vec2d_dot");
defineAndRegisterTnbServerObject(Server_GeoObj_Vec2d_CrossProduct, Server::objects::vec2d_cross, "vec2d_cross");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_Create, Server::objects::make_bnd_box_2d, "make_bnd_box_2d");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_PntList, Server::objects::calc_bnd_box_2d_pnt_list, "calc_bnd_box_2d_pnt_list");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_Curve, Server::objects::calc_bnd_box_2d_curve, "calc_bnd_box_2d_curve");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_CrvList, Server::objects::calc_bnd_box_2d_crv_list, "calc_bnd_box_2d_crv_list");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_Area, Server::objects::calc_bnd_box_2d_area, "calc_bnd_box_2d_area");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_AreaList, Server::objects::calc_bnd_box_2d_area_list, "calc_bnd_box_2d_area_list");

defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_Expand, Server::objects::do_bnd_box_2d_expand, "do_bnd_box_2d_expand");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_GetDia, Server::objects::get_bnd_box_2d_dia, "get_bnd_box_2d_dia");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_GetLengths, Server::objects::get_bnd_box_2d_lengths, "get_bnd_box_2d_lengths");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_GetP0, Server::objects::get_bnd_box_2d_p0, "get_bnd_box_2d_p0");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_GetP1, Server::objects::get_bnd_box_2d_p1, "get_bnd_box_2d_p1");
defineAndRegisterTnbServerObject(Server_Geo2dObj_BndBox_GetCorners, Server::objects::get_bnd_box_2d_corners, "get_bnd_box_2d_corners");


defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_Volume_F1, Server::objects::make_size_map_2d_vol_f1, "make_size_map_2d_vol_f1");
defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_Volume_F2, Server::objects::make_size_map_2d_vol_f2, "make_size_map_2d_vol_f2");

defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_Uniform, Server::objects::make_size_map_2d_uniform, "make_size_map_2d_uniform");

defineAndRegisterTnbServerObject(Server_Geo2dObj_ApproxCrv, Server::objects::make_approx_curve_2d_settings, "make_approx_curve_2d_settings");

defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_BndControl, Server::objects::make_size_map_2d_ctrl_bnd, "make_size_map_2d_ctrl_bnd");
defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_VolControl, Server::objects::make_size_map_2d_ctrl_vol, "make_size_map_2d_ctrl_vol");

defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_Adaptive, Server::objects::make_size_map_2d_adaptive, "make_size_map_2d_adaptive");
defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_MakeVol, Server::objects::make_vol_size_map_2d_ctrl, "make_vol_size_map_2d_ctrl");
defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_MakeBnd, Server::objects::make_bnd_size_map_2d_ctrl, "make_bnd_size_map_2d_ctrl");
defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_Adapt_Perform, Server::objects::perform_size_map_2d_adaptive, "perform_size_map_2d_adaptive");

defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_ImptVol, Server::objects::vol_size_map_2d_ctrl_import_shape, "vol_size_map_2d_ctrl_import_shape");
defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_Vol_GetCond, Server::objects::vol_size_map_2d_ctrl_get_condition, "vol_size_map_2d_ctrl_get_condition");
defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_Vol_GetValues, Server::objects::vol_size_map_2d_ctrl_get_values, "vol_size_map_2d_ctrl_get_values");
defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_Vol_ValuesGr, Server::objects::vol_size_map_2d_ctrl_values_set_gr, "vol_size_map_2d_ctrl_values_set_gr");
defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_Vol_GetSurfSize, Server::objects::vol_size_map_2d_ctrl_values_get_size, "vol_size_map_2d_ctrl_values_get_size");
defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_Vol_SetTargetSize, Server::objects::vol_size_map_2d_ctrl_size_value_target, "vol_size_map_2d_ctrl_size_value_target");
defineAndRegisterTnbServerObject(Server_Geo2dObj_SizeMap_Vol_SetValueType, Server::objects::vol_size_map_2d_ctrl_size_value_type, "vol_size_map_2d_ctrl_size_value_type");
// mesh lib

#include <Server_Mesh2dObj.hxx>
defineAndRegisterTnbServerObject(Server_Mesh2dObj_RefValues, Server::objects::make_mesh_ref_values_2d, "make_mesh_ref_values_2d");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_MetricPrcsr_Settings, Server::objects::make_metric_prcsr_2d_settings, "make_metric_prcsr_2d_settings");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_MetricPrcsr, Server::objects::make_metric_prcsr_2d, "make_metric_prcsr_2d");

defineAndRegisterTnbServerObject(Server_Mesh2dObj_Mesh_Curve_OptPoint, Server::objects::make_mesh_curve_2d_opt_point_settings, "make_mesh_curve_2d_opt_point_settings");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_Mesh_Curve_Settings, Server::objects::make_mesh_curve_2d_settings, "make_mesh_curve_2d_settings");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_Mesh_Curve, Server::objects::do_mesh_curve_2d, "do_mesh_curve_2d");

defineAndRegisterTnbServerObject(Server_Mesh2dObj_BndLayer_F1, Server::objects::do_mesh_2d_bnd_layer_f1, "do_mesh_2d_bnd_layer_f1");

defineAndRegisterTnbServerObject(Server_Mesh2dObj_SoluData, Server::objects::make_mesh_2d_solu_data, "make_mesh_2d_solu_data");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_Region, Server::objects::make_mesh_2d_region, "make_mesh_2d_region");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_NodeGen_Std, Server::objects::make_mesh_2d_node_gen_std, "make_mesh_2d_node_gen_std");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_BndMesh, Server::objects::do_mesh_2d_bnd, "do_mesh_2d_bnd");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_Mesh, Server::objects::do_mesh_2d, "do_mesh_2d");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_LaplacSmooth, Server::objects::do_mesh_2d_laplac_smooth, "do_mesh_2d_laplac_smooth");

defineAndRegisterTnbServerObject(Server_Mesh2dObj_Extrude_FEA, Server::objects::extrude_mesh_2d_fea, "extrude_mesh_2d_fea");
// Post mesh
defineAndRegisterTnbServerObject(Server_Mesh2dObj_Mesh_QualFun_Vlrms2Ratio, Server::objects::make_mesh_2d_qual_fun_vlrms2ratio, "make_mesh_2d_qual_fun_vlrms2ratio");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_Mesh_LaplacSmooth_AdjEdgesFun, Server::objects::make_mesh_2d_laplac_smooth_ang_fun_adj_edges, "make_mesh_2d_laplac_smooth_ang_fun_adj_edges");

// Num lib
#include <Server_NumObj_AdaptInteg_Info.hxx>
#include <Server_NumObj_NewtonNonLinSolver_Info.hxx>
#include <Server_NumObj_BisectNonLinSolver_Info.hxx>
defineAndRegisterTnbServerObject(Server_NumObj_AdaptInteg_Info, Server::objects::make_num_adapt_integ, "make_num_adapt_integ");
defineAndRegisterTnbServerObject(Server_NumObj_NewtonNonLinSolver_Info, Server::objects::make_num_newton_solver, "make_num_newton_solver");
defineAndRegisterTnbServerObject(Server_NumObj_BisectNonLinSolver_Info, Server::objects::make_num_bisect_solver, "make_num_bisect_solver");

#include <Server_Cad2dObj_Curve.hxx>
#include <Server_FoamObj.hxx>
// io
//defineAndRegisterTnbServerObject(Server_Geo2dObj_ExportMeshToPlt, Server::objects::export_tri_2d_to_plt, "export_mesh_2d_to_plt");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Curve_ExportToPlt, Server::objects::export_curve_2d_to_plt, "export_curve_2d_to_plt");
defineAndRegisterTnbServerObject(Server_Cad2dObj_Area_ExportToPlt, Server::objects::export_area_to_plt, "export_area_to_plt");
//defineAndRegisterTnbServerObject(Server_Mesh2dObj_ExportToPlt, Server::objects::export_mesh_2d_to_plt, "export_mesh_2d_to_plt");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_SoluData_ExportMeshToPlt, Server::objects::export_mesh_2d_solu_data_to_plt, "export_mesh_2d_solu_data_to_plt");
defineAndRegisterTnbServerObject(Server_Mesh2dObj_ExportToFEA, Server::objects::export_mesh_2d_to_fea, "export_mesh_2d_to_fea");
defineAndRegisterTnbServerObject(Server_MeshObj_ExportFvToUNV, Server::objects::export_mesh_fv_to_unv, "export_mesh_fv_to_unv");
defineAndRegisterTnbServerObject(Server_FoamObj_LoadInitCs, Server::objects::load_openfoam_init_cnds, "load_openfoam_init_cnds");
defineAndRegisterTnbServerObject(Server_FoamObj_LoadBcs, Server::objects::load_openfoam_bcs, "load_openfoam_bcs");
defineAndRegisterTnbServerObject(Server_FoamObj_WriteInitCs, Server::objects::write_openfoam_init_cnds, "write_openfoam_init_cnds");
defineAndRegisterTnbServerObject(Server_FoamObj_WriteBcs, Server::objects::write_openfoam_bcs, "write_openfoam_bcs");

#include <Server_GlobalObj_Exit.hxx>
defineAndRegisterTnbServerObject(Server_GlobalObj_Exit, Server::objects::exit, "EXIT");
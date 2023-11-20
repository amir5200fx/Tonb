#include <Server.hxx>

using namespace tnbLib;

#include <Server_GlobalObj_Int.hxx>
createTnbServerObject(create_int, Server_GlobalObj_Int)

#include <Server_GlobalObj_Real.hxx>
createTnbServerObject(create_real, Server_GlobalObj_Real)

#include <Server_GlobalObj_Bool.hxx>
createTnbServerObject(create_bool, Server_GlobalObj_Bool)

#include <Server_GeoObj_Pnt2d_F1.hxx>
#include <Server_GeoObj_Pnt2d_Compts.hxx>
createTnbServerObject(create_pnt_2d_f1, Server_GeoObj_Pnt2d_F1)
createTnbServerObject(retv_compts_pnt_2d, Server_GeoObj_Pnt2d_Compts)

#include <Server_GeoObj_Pnt2d_List.hxx>
createTnbServerObject(make_pnt_2d_list, Server_GeoObj_Pnt2d_List)

#include <Server_GeoObj_Vec2d_F1.hxx>
createTnbServerObject(create_vec_2d_f1, Server_GeoObj_Vec2d_F1)

#include <Server_GeoObj_Dir2d_F1.hxx>
createTnbServerObject(create_dir_2d_f1, Server_GeoObj_Dir2d_F1)

#include <Server_GeoObj_Axis2d_F1.hxx>
createTnbServerObject(create_axis_2d_f1, Server_GeoObj_Axis2d_F1)

#include <Server_Cad2dObj_Segment2d_F1.hxx>
#include <Server_Cad2dObj_Circle_F1.hxx>
#include <Server_Cad2dObj_Rectangular_F1.hxx>
#include <Server_Cad2dObj_PrjPntCrv.hxx>
#include <Server_Cad2dObj_Curve_List.hxx>
#include <Server_Cad2dObj_Area_F1.hxx>
#include <Server_Cad2dObj_FirstParCurve.hxx>
#include <Server_Cad2dObj_LastParCurve.hxx>
#include <Server_Cad2dObj_CalcPntOnCurve.hxx>
#include <Server_Cad2dObj_RevCrv.hxx>
#include <Server_Cad2dObj_Area_Manager.hxx>
createTnbServerObject(make_circle_2d_f1, Server_Cad2dObj_Circle_F1)
createTnbServerObject(make_rectangular_2d_f1, Server_Cad2dObj_Rectangular_F1)
createTnbServerObject(make_segment_2d_f1, Server_Cad2dObj_Segment2d_F1)
createTnbServerObject(make_curve_2d_list, Server_Cad2dObj_Curve_List)
createTnbServerObject(retv_first_parameter_curve_2d, Server_Cad2dObj_FirstParCurve)
createTnbServerObject(retv_last_parameter_curve_2d, Server_Cad2dObj_LastParCurve)
createTnbServerObject(calc_pnt_curve_2d, Server_Cad2dObj_CalcPntOnCurve)
createTnbServerObject(prj_pnt_curve_2d, Server_Cad2dObj_PrjPntCrv)
createTnbServerObject(rev_curve_2d, Server_Cad2dObj_RevCrv)
createTnbServerObject(make_area_2d, Server_Cad2dObj_Area_F1)

createTnbServerObject(retv_area_2d_blocks, Server_Cad2dObj_Area_Manager_Segments)
createTnbServerObject(retv_area_2d_block_curves, Server_Cad2dObj_Area_Manager_Segments_BlockCurves)
createTnbServerObject(combine_area_2d_blocks, Server_Cad2dObj_Area_Manager_Segments_CombineBlocks)
void Server::split_area_2d_block(const std::string& theValue, const std::string& theSense)
{
	if (theSense == "no")
	{
		theObj_ = std::make_shared<Server_Cad2dObj_Area_Manager_Segments_SplitBlock>();
		theObj_->Construct(theValue);
	}
	else
	{
		theObj_ = std::make_shared<Server_Cad2dObj_Area_Manager_Segments_SplitBlock>();
		theObj_->MakeEmpty();
	}
}
createTnbServerObject(rename_area_2d_block, Server_Cad2dObj_Area_Manager_Segments_RenameBlock)

#include <Server_Cad2dObj_Interpl_F1.hxx>
#include <Server_Cad2dObj_Discret_Info.hxx>
#include <Server_Cad2dObj_Discret.hxx>
#include <Server_Cad2dObj_Boolean_Subtract_F1.hxx>
createTnbServerObject(make_interpl_curve_2d, Server_Cad2dObj_Interpl_F1)
createTnbServerObject(make_discrete_shape_info_2d, Server_Cad2dObj_Discret_Info)
createTnbServerObject(do_discret_2d, Server_Cad2dObj_Discret)
createTnbServerObject(do_boolean_sub_2d, Server_Cad2dObj_Boolean_Subtract_F1)

// geo lib
#include <Server_Geo2dObj_BndBox.hxx>
createTnbServerObject(make_bnd_box_2d, Server_Geo2dObj_BndBox_Create)
createTnbServerObject(calc_bnd_box_2d_pnt_list, Server_Geo2dObj_BndBox_PntList)
createTnbServerObject(calc_bnd_box_2d_curve, Server_Geo2dObj_BndBox_Curve)
createTnbServerObject(calc_bnd_box_2d_crv_list, Server_Geo2dObj_BndBox_CrvList)
createTnbServerObject(calc_bnd_box_2d_area, Server_Geo2dObj_BndBox_Area)
createTnbServerObject(calc_bnd_box_2d_area_list, Server_Geo2dObj_BndBox_AreaList)

createTnbServerObject(do_bnd_box_2d_expand, Server_Geo2dObj_BndBox_Expand)
createTnbServerObject(get_bnd_box_2d_dia, Server_Geo2dObj_BndBox_GetDia)
createTnbServerObject(get_bnd_box_2d_lengths, Server_Geo2dObj_BndBox_GetLengths)

#include <Server_Geo2dObj.hxx>
createTnbServerObject(make_size_map_2d_uniform, Server_Geo2dObj_SizeMap_Uniform)

// Mesh lib
#include <Server_Mesh2dObj.hxx>
createTnbServerObject(make_mesh_ref_values_2d, Server_Mesh2dObj_RefValues)
createTnbServerObject(make_metric_prcsr_2d_settings, Server_Mesh2dObj_MetricPrcsr_Settings)
createTnbServerObject(make_metric_prcsr_2d, Server_Mesh2dObj_MetricPrcsr)

createTnbServerObject(make_mesh_curve_2d_opt_point_settings, Server_Mesh2dObj_Mesh_Curve_OptPoint)
createTnbServerObject(make_mesh_curve_2d_settings, Server_Mesh2dObj_Mesh_Curve_Settings)
createTnbServerObject(do_mesh_curve_2d, Server_Mesh2dObj_Mesh_Curve)

createTnbServerObject(make_mesh_2d_solu_data, Server_Mesh2dObj_SoluData)
createTnbServerObject(make_mesh_2d_region, Server_Mesh2dObj_Region)
createTnbServerObject(make_mesh_2d_node_gen_std, Server_Mesh2dObj_NodeGen_Std)
createTnbServerObject(do_mesh_2d_bnd, Server_Mesh2dObj_BndMesh)
createTnbServerObject(do_mesh_2d, Server_Mesh2dObj_Mesh)
createTnbServerObject(do_mesh_2d_laplac_smooth, Server_Mesh2dObj_LaplacSmooth)

// post mesh
createTnbServerObject(make_mesh_2d_qual_fun_vlrms2ratio, Server_Mesh2dObj_Mesh_QualFun_Vlrms2Ratio)
createTnbServerObject(make_mesh_2d_laplac_smooth_ang_fun_adj_edges, Server_Mesh2dObj_Mesh_LaplacSmooth_AdjEdgesFun)

// Num lib
#include <Server_NumObj_AdaptInteg_Info.hxx>
#include <Server_NumObj_NewtonNonLinSolver_Info.hxx>
#include <Server_NumObj_BisectNonLinSolver_Info.hxx>
createTnbServerObject(make_num_adapt_integ, Server_NumObj_AdaptInteg_Info)
createTnbServerObject(make_num_newton_solver, Server_NumObj_NewtonNonLinSolver_Info)
createTnbServerObject(make_num_bisect_solver, Server_NumObj_BisectNonLinSolver_Info)

#include <Server_GlobalObj_Exit.hxx>
createTnbServerObject(exit, Server_GlobalObj_Exit)
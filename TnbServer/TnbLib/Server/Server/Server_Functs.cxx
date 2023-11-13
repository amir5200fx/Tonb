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

#include <Server_GlobalObj_Exit.hxx>
createTnbServerObject(exit, Server_GlobalObj_Exit)
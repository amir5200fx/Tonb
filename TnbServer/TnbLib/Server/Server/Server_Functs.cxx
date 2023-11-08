#include <Server.hxx>

using namespace tnbLib;

#include <Server_GlobalObj_Int.hxx>
createTnbServerObject(create_int, Server_GlobalObj_Int)

#include <Server_GlobalObj_Real.hxx>
createTnbServerObject(create_real, Server_GlobalObj_Real)

#include <Server_GlobalObj_Bool.hxx>
createTnbServerObject(create_bool, Server_GlobalObj_Bool)

#include <Server_GeoObj_Pnt2d_F1.hxx>
createTnbServerObject(create_pnt_2d_f1, Server_GeoObj_Pnt2d_F1)

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
#include <Server_Cad2dObj_Curve_List.hxx>
#include <Server_Cad2dObj_Area_F1.hxx>
createTnbServerObject(make_circle_2d_f1, Server_Cad2dObj_Circle_F1)
createTnbServerObject(make_rectangular_2d_f1, Server_Cad2dObj_Rectangular_F1)
createTnbServerObject(make_segment_2d_f1, Server_Cad2dObj_Segment2d_F1)
createTnbServerObject(make_curve_2d_list, Server_Cad2dObj_Curve_List)
createTnbServerObject(make_area_2d, Server_Cad2dObj_Area_F1)

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
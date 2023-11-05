#include <Server.hxx>

std::map<std::string, tnbLib::Server::objects> tnbLib::Server::Commands;

using namespace tnbLib;

#include <Server_GlobalObj_Int.hxx>
#include <Server_GlobalObj_Real.hxx>
#include <Server_GeoObj_Pnt2d.hxx>
#include <Server_GeoObj_Vec2d_F1.hxx>
#include <Server_GeoObj_Dir2d_F1.hxx>
#include <Server_GeoObj_Axis2d.hxx>

// the interger object
defineAndRegisterTnbServerObject(Server_GlobalObj_Int, Server::objects::make_int, "make_int");
defineAndRegisterTnbServerObject(Server_GlobalObj_Real, Server::objects::make_real, "make_real");
defineAndRegisterTnbServerObject(Server_GeoObj_Pnt2d, Server::objects::make_pnt_2d, "make_pnt_2d");
defineAndRegisterTnbServerObject(Server_GeoObj_Vec2d_F1, Server::objects::make_vec_2d_f1, "make_vec_2d_f1");
defineAndRegisterTnbServerObject(Server_GeoObj_Dir2d_F1, Server::objects::make_dir_2d_f1, "make_dir_2d_f1");
defineAndRegisterTnbServerObject(Server_GeoObj_Axis2d, Server::objects::make_axis_2d, "make_axis_2d");

#include <Server_ToolsObj_DiscrtShape2d.hxx>
defineAndRegisterTnbServerObject(Server_ToolsObj_DiscrtShape2d, Server::objects::make_discrete_shape_info_2d, "make_tools_discrete_shape_info_2d");

#include <Server_Cad2dObj_Circle_F1.hxx>
defineAndRegisterTnbServerObject(Server_Cad2dObj_Circle_F1, Server::objects::make_circle_2d_f1, "make_circle_2d_f1");
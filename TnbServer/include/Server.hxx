#pragma once
#ifndef _Server_Header
#define _Server_Header

#include <Server_Module.hxx>

#include <memory>
#include <map>

#include "Server_Macros.hxx"

namespace tnbLib
{

	// Forward Declarations
	class Server_Object;
	class Server_Socket;

	class Server
	{

	public:

		enum class objects
		{
			make_real = 0,
			make_int,
			make_bool,
			make_vec_2d_f1,
			make_dir_2d_f1,
			make_axis_2d_f1,
			make_pnt_2d_f1,
			make_pnt_3d,

			retrv_compts_pnt_2d,
			retrv_compts_vec_2d,
			retrv_compts_dir_2d,

			make_pnt_2d_list,

			make_segment_2d_f1,
			make_circle_2d_f1,
			make_rectangular_2d_f1,

			make_curve_2d_list,
			retv_first_parameter_curve_2d,
			retv_last_parameter_curve_2d,
			calc_pnt_curve_2d,
			prj_pnt_curve_2d,
			rev_curve_2d,

			retv_area_2d_blocks,
			retv_area_2d_block_curves,
			combine_area_2d_blocks,
			split_area_2d_block,
			rename_area_2d_block,

			make_area_2d,

			make_interpl_curve_2d,

			make_discrete_shape_info_2d,
			do_discret_2d,
			do_boolean_sub_2d,

			// geo lib

			make_bnd_box_2d,
			calc_bnd_box_2d_pnt_list,
			calc_bnd_box_2d_curve,
			calc_bnd_box_2d_crv_list,
			calc_bnd_box_2d_area,
			calc_bnd_box_2d_area_list,

			do_bnd_box_2d_expand,
			get_bnd_box_2d_dia,
			get_bnd_box_2d_lengths,

			make_size_map_2d_uniform,

			// mesh lib

			make_mesh_ref_values_2d,
			make_metric_prcsr_2d_settings,
			make_metric_prcsr_2d,

			make_mesh_curve_2d_opt_point_settings,
			make_mesh_curve_2d_settings,
			do_mesh_curve_2d,

			make_mesh_2d_solu_data,
			make_mesh_2d_region,
			make_mesh_2d_node_gen_std,
			do_mesh_2d_bnd,
			do_mesh_2d,
			do_mesh_2d_laplac_smooth,

			// post mesh

			make_mesh_2d_qual_fun_vlrms2ratio,
			make_mesh_2d_laplac_smooth_ang_fun_adj_edges,

			// num lib

			make_num_adapt_integ,
			make_num_newton_solver,
			make_num_bisect_solver,
			
			exit
		};

		struct Command
		{
			std::string stream;
		};

		struct Value
		{
			std::string stream;
		};

		struct Flag
		{
			std::string stream;
		};

		struct Emptiness
		{
			std::string stream;
		};

	private:

		/*Private Data*/

		std::shared_ptr<Server_Object> theObj_;
		std::string theCommand_;
		std::string theFlag_;


		// Private functions and operators

		// global functions
		void create_real(const std::string&, const std::string&);
		void create_int(const std::string&, const std::string&);
		void create_bool(const std::string&, const std::string&);

		// geometrical functions
		void create_pnt_2d_f1(const std::string&, const std::string&);
		void create_pnt_3d(const std::string&, const std::string&);
		void create_vec_2d_f1(const std::string&, const std::string&);
		void create_vec_3d(const std::string&, const std::string&);
		void create_dir_2d_f1(const std::string&, const std::string&);
		void create_dir_3d(const std::string&, const std::string&);
		void create_axis_2d_f1(const std::string&, const std::string&);

		declareTnbServerFunction(retv_compts_pnt_2d);
		declareTnbServerFunction(retv_compts_vec_2d);
		declareTnbServerFunction(retv_compts_dir_2d);

		void make_pnt_2d_list(const std::string&, const std::string&);

		// cad functions
		void make_segment_2d_f1(const std::string&, const std::string&);
		void make_Segment_3d(const std::string&, const std::string&);

		declareTnbServerFunction(retv_first_parameter_curve_2d);
		declareTnbServerFunction(retv_last_parameter_curve_2d);
		declareTnbServerFunction(calc_pnt_curve_2d);
		declareTnbServerFunction(prj_pnt_curve_2d);
		declareTnbServerFunction(rev_curve_2d);
		void make_curve_2d_list(const std::string&, const std::string&);
		void make_area_2d(const std::string&, const std::string&);

		declareTnbServerFunction(retv_area_2d_blocks);
		declareTnbServerFunction(retv_area_2d_block_curves);
		declareTnbServerFunction(combine_area_2d_blocks);
		declareTnbServerFunction(split_area_2d_block);
		declareTnbServerFunction(rename_area_2d_block);

		void make_circle_2d_f1(const std::string&, const std::string&);
		void make_rectangular_2d_f1(const std::string&, const std::string&);

		void make_interpl_curve_2d(const std::string&, const std::string&);

		// geo lib

		declareTnbServerFunction(make_bnd_box_2d);
		declareTnbServerFunction(calc_bnd_box_2d_pnt_list);
		declareTnbServerFunction(calc_bnd_box_2d_curve);
		declareTnbServerFunction(calc_bnd_box_2d_crv_list);
		declareTnbServerFunction(calc_bnd_box_2d_area);
		declareTnbServerFunction(calc_bnd_box_2d_area_list);

		declareTnbServerFunction(do_bnd_box_2d_expand);
		declareTnbServerFunction(get_bnd_box_2d_dia);
		declareTnbServerFunction(get_bnd_box_2d_lengths);

		declareTnbServerFunction(make_size_map_2d_uniform);

		// mesh functions

		declareTnbServerFunction(make_mesh_ref_values_2d);
		declareTnbServerFunction(make_metric_prcsr_2d_settings);
		declareTnbServerFunction(make_metric_prcsr_2d);

		declareTnbServerFunction(make_mesh_curve_2d_opt_point_settings);
		declareTnbServerFunction(make_mesh_curve_2d_settings);
		declareTnbServerFunction(do_mesh_curve_2d);

		declareTnbServerFunction(make_mesh_2d_solu_data);
		declareTnbServerFunction(make_mesh_2d_region);
		declareTnbServerFunction(make_mesh_2d_node_gen_std);
		declareTnbServerFunction(do_mesh_2d_bnd);
		declareTnbServerFunction(do_mesh_2d);
		declareTnbServerFunction(do_mesh_2d_laplac_smooth);

		// post mesh

		declareTnbServerFunction(make_mesh_2d_qual_fun_vlrms2ratio);
		declareTnbServerFunction(make_mesh_2d_laplac_smooth_ang_fun_adj_edges);

		// num lib

		declareTnbServerFunction(make_num_adapt_integ);
		declareTnbServerFunction(make_num_newton_solver);
		declareTnbServerFunction(make_num_bisect_solver);

		// tools functions

		void make_discrete_shape_info_2d(const std::string&, const std::string&);
		void do_discret_2d(const std::string&, const std::string&);
		void do_boolean_sub_2d(const std::string&, const std::string&);

		void exit(const std::string&, const std::string&);

	public:
		
		static TnbServer_EXPORT const std::string END_MESSAGE;

		static TnbServer_EXPORT std::map<std::string, objects> Commands;
		static TnbServer_EXPORT const std::string REQUEST;
		static TnbServer_EXPORT const std::string FLAG;
		static TnbServer_EXPORT const std::string RESPONSE;
		static TnbServer_EXPORT const std::string VALUE;
		static TnbServer_EXPORT const std::string EMPTINESS;
		

		// default constructor

		Server() = default;

		// constructors


		// Public functions and operators

		TnbServer_EXPORT void Construct(const Command& theCommand, const Flag& flag, const Emptiness& theSense, const Value& theValue);
		TnbServer_EXPORT void SendObj(const std::shared_ptr<Server_Socket>&) const;
		
	};
}


#endif

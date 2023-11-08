#pragma once
#ifndef _Server_Header
#define _Server_Header

#include <Server_Module.hxx>

#include <memory>
#include <map>

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

			make_pnt_2d_list,

			make_segment_2d_f1,
			make_circle_2d_f1,
			make_rectangular_2d_f1,

			make_curve_2d_list,
			make_area_2d,

			make_interpl_curve_2d,

			make_discrete_shape_info_2d,
			do_discret_2d,
			do_boolean_sub_2d,
			
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

		void make_pnt_2d_list(const std::string&, const std::string&);

		// cad functions
		void make_segment_2d_f1(const std::string&, const std::string&);
		void make_Segment_3d(const std::string&, const std::string&);

		void make_curve_2d_list(const std::string&, const std::string&);
		void make_area_2d(const std::string&, const std::string&);

		void make_circle_2d_f1(const std::string&, const std::string&);
		void make_rectangular_2d_f1(const std::string&, const std::string&);

		void make_interpl_curve_2d(const std::string&, const std::string&);

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

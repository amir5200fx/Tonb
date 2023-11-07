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

			make_interpl_curve_2d,

			make_discrete_shape_info_2d,
			
			exit
		};

	private:

		/*Private Data*/

		std::shared_ptr<Server_Object> theObj_;
		std::string theCommand_;


		// Private functions and operators

		// global functions
		void create_real(const std::string&);
		void create_int(const std::string&);
		void create_bool(const std::string&);

		// geometrical functions
		void create_pnt_2d_f1(const std::string&);
		void create_pnt_3d(const std::string&);
		void create_vec_2d_f1(const std::string&);
		void create_vec_3d(const std::string&);
		void create_dir_2d_f1(const std::string&);
		void create_dir_3d(const std::string&);
		void create_axis_2d_f1(const std::string&);

		void make_pnt_2d_list(const std::string&);

		// cad functions
		void make_segment_2d_f1(const std::string&);
		void make_Segment_3d(const std::string&);

		void make_circle_2d_f1(const std::string&);

		void make_interpl_curve_2d(const std::string&);

		// tools functions

		void create_tools_discrete_shape_info_2d(const std::string&);

		void exit(const std::string&);

	public:
		
		static TnbServer_EXPORT const std::string END_MESSAGE;

		static TnbServer_EXPORT std::map<std::string, objects> Commands;
		static TnbServer_EXPORT const std::string REQUEST;
		static TnbServer_EXPORT const std::string RESPONSE;
		static TnbServer_EXPORT const std::string VALUE;

		// default constructor

		Server() = default;

		// constructors


		// Public functions and operators

		TnbServer_EXPORT void Construct(const std::string& theCommand, const std::string& theValue);
		TnbServer_EXPORT void SendObj(const std::shared_ptr<Server_Socket>&) const;
		
	};
}


#endif

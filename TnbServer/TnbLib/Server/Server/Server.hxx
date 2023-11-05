#pragma once
#ifndef _Server_Header
#define _Server_Header

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
			gl_real = 0,
			gl_integer,
			geo_vec2d,
			geo_dir2d,
			geo_axis,
			geo_pnt2d,
			geo_pnt3d,
			segment,
			exit
		};

	private:

		/*Private Data*/

		std::shared_ptr<Server_Object> theObj_;
		std::string theCommand_;


		// Private functions and operators

		void CreateReal(const std::string&);
		void CreateInt(const std::string&);
		
		void CreatePnt2d(const std::string&);
		void CreatePnt3d(const std::string&);
		void CreateVec2d(const std::string&);
		void CreateVec3d(const std::string&);
		void CreateDir2d(const std::string&);
		void CreateDir3d(const std::string&);
		void CreateAxis(const std::string&);
		void CraeteSegment(const std::string&);

	public:
		

		static std::map<std::string, objects> Commands;
		static const std::string REQUEST;
		static const std::string RESPONSE;
		static const std::string VALUE;

		// default constructor

		Server() = default;

		// constructors


		// Public functions and operators

		void Construct(const std::string& theCommand, const std::string& theValue);
		void SendObj(const std::shared_ptr<Server_Socket>&) const;
		
	};
}


#endif

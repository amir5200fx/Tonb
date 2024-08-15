#pragma once
#ifndef _GeoIO_Loader_STL_Header
#define _GeoIO_Loader_STL_Header
#include <Entity3d_TriangulationFwd.hxx>
#include <Geo_Module.hxx>
#include <Global_Done.hxx>

#include <memory>
namespace tnbLib
{
	// Forward Declarations

	namespace ioLib
	{
		class Loader_STL
			: public Global_Done
		{
			/*Private Data*/
			std::shared_ptr<Entity3d_Triangulation> theMesh_;
		public:
			// default constructor
			Loader_STL() = default;
			// constructors

			// Public functions and operators
			const auto& Mesh() const { return theMesh_; }

			TnbGeo_EXPORT void PerformBinary(const std::string& file_name);
			void PerformASCII(const std::string& file_name);
		};

	}
}
#endif
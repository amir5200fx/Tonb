#pragma once
#ifndef _BoundarySizeMap2d_CornerToolSystem_Header
#define _BoundarySizeMap2d_CornerToolSystem_Header

#include <Mesh_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class GeoMesh_Background_SmoothingHvCorrection_Info;

	namespace sysLib
	{

		TnbMesh_EXPORT extern std::shared_ptr<GeoMesh_Background_SmoothingHvCorrection_Info> gl_background_hv_correction_info;

		TnbMesh_EXPORT void init_gl_background_hv_correction_info();
	}
}

#endif // !_BoundarySizeMap2d_CornerToolSystem_Header

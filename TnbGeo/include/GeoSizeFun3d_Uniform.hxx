#pragma once
#ifndef _GeoSizeFun3d_Uniform_Header
#define _GeoSizeFun3d_Uniform_Header

#include <Pnt3d.hxx>
#include <GeoSizeFun_Uniform.hxx>

namespace tnbLib
{

	typedef GeoSizeFun_Uniform<Pnt3d> GeoSizeFun3d_Uniform;
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoSizeFun3d_Uniform);

#endif // !_GeoSizeFun3d_Uniform_Header

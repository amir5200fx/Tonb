#pragma once
#ifndef _Aft2d_ModelAnIsoFwd_Header
#define _Aft2d_ModelAnIsoFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	//- Forward Declarations
	template<class ModelType, class SizeFun, class MetricFun>
	class Aft_Model;

	class Cad2d_Plane;

	typedef Aft_Model<Cad2d_Plane, Geo2d_SizeFunction, Geo2d_MetricFunction>
		Aft2d_ModelAnIso;
}

#endif // !_Aft2d_ModelAnIsoFwd_Header

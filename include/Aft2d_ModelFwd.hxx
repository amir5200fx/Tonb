#pragma once
#ifndef _Aft2d_ModelFwd_Header
#define _Aft2d_ModelFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>

namespace tnbLib
{

	//- Forward Declarations
	template<class ModelType, class SizeFun, class MetricFun>
	class Aft_Model;

	class Cad2d_Plane;

	typedef Aft_Model<Cad2d_Plane, Geo2d_SizeFunction, void> Aft2d_Model;
}

#endif // !_Aft2d_ModelFwd_Header

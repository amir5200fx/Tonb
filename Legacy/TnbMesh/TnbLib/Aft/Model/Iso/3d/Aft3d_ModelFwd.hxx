#pragma once
#ifndef _Aft3d_ModelFwd_Header
#define _Aft3d_ModelFwd_Header

#include <Geo3d_SizeFunctionFwd.hxx>

namespace tnbLib
{

	//- Forward Declarations
	template<class ModelType, class SizeFun, class MetricFun>
	class Aft_Model;

	class Cad_TModel;

	typedef Aft_Model<Cad_TModel, Geo3d_SizeFunction, void> Aft3d_Model;
}

#endif // !_Aft3d_ModelFwd_Header

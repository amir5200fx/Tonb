#pragma once
#ifndef _Aft2d_tSolutionDataSurfaceFwd_Header
#define _Aft2d_tSolutionDataSurfaceFwd_Header

namespace tnbLib
{

	// Forward Declarations [6/20/2022 Amir]
	template<class ShapeType>
	class Aft2d_SolutionDataSurface;

	class Cad_TModel;

	typedef Aft2d_SolutionDataSurface<Cad_TModel> Aft2d_tSolutionDataSurface;
}

#endif // !_Aft2d_tSolutionDataSurfaceFwd_Header

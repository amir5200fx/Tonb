#pragma once
#ifndef _HydStatic_Modeler_CurveTools_Header
#define _HydStatic_Modeler_CurveTools_Header

#include <Pnt2d.hxx>
#include <Pnt3d.hxx>
#include <HydStatic_Modeler_CoordPlane.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_Modeler;
	class NModel_Edge;

	namespace hydStcLib
	{

		class Modeler_CurveTools
		{

		public:

			static std::shared_ptr<NModel_Edge> CreateSegment
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1, 
				const Standard_Real x,
				const Modeler_CoordPlane thePlane,
				HydStatic_Modeler& theModeler
			);

			static std::shared_ptr<NModel_Edge> CreateSegment
			(
				const Pnt3d& theP0,
				const Pnt3d& theP1,
				HydStatic_Modeler& theModeler
			);
		};
	}
}

#endif // !_HydStatic_Modeler_CurveTools_Header

#pragma once
#ifndef _PtdShapeFit_Tools_Header
#define _PtdShapeFit_Tools_Header

#include <PtdShapeFit_Module.hxx>

#include <vector>
#include <memory>

#include <gp_Ax1.hxx>
#include <Standard_Handle.hxx>

class Geom_Plane;

namespace tnbLib
{

	// Forward Declarations [2/13/2023 Payvand]
	class Cad_Shape;
	class Cad2d_Plane;
	class Pln_Curve;
	class Pnt2d;

	class PtdShapeFit_Tools
	{

	public:

		static TnbPtdShapeFit_EXPORT std::vector<std::pair<Standard_Real, Standard_Integer>> 
			Knots
			(
				const Standard_Integer theNbQ, 
				const Standard_Integer theDeg,
				const Standard_Real theU0,
				const Standard_Real theU1
			);


		static TnbPtdShapeFit_EXPORT std::tuple
			<
			std::vector<std::pair<Pnt2d, Standard_Real>>, 
			std::vector<Standard_Real>,
			std::vector<Standard_Integer>, 
			Standard_Integer
			> 
			RetrievePoles(const Pln_Curve&);

		static TnbPtdShapeFit_EXPORT std::vector<std::shared_ptr<Pln_Curve>> 
			RetrieveCurves(const Cad2d_Plane&);

		static TnbPtdShapeFit_EXPORT std::shared_ptr<Cad_Shape> 
			MakeExtrudedSurface
			(
				const std::vector<std::shared_ptr<Pln_Curve>>&,
				const std::vector<Handle(Geom_Plane)>&
			);

		static TnbPtdShapeFit_EXPORT std::shared_ptr<Cad_Shape> 
			MakeExtrudedShape
			(
				const std::vector<std::shared_ptr<Cad2d_Plane>>&,
				const gp_Ax1&,
				const std::vector<Standard_Real>& theLocs
			);
	};
}

#endif // !_PtdShapeFit_Tools_Header

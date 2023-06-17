#pragma once
#ifndef _Tools_Header
#define _Tools_Header

#include <Pnt3d.hxx>
#include <Pnt2d.hxx>

#include <vector>

#include <TopoDS_Face.hxx>
#include <Geom_Surface.hxx>
#include <Geom_Curve.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom_Plane.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <Standard_Handle.hxx>

namespace tnbLib
{

	class Tools
	{

	public:

		static std::vector<Pnt3d> CalcPnt3ds(const Standard_Real z0, const std::vector<Standard_Real>& theZs, const Standard_Real theRadius, const Standard_Real thePhi);
		static std::vector<Pnt3d> CalcPnt3ds(const std::vector<Pnt2d>&, const Handle(Geom_Surface)&);
		static std::vector<Pnt2d> ProjectPointsToCylinderSurf(const std::vector<Pnt3d>& theCoords, const Handle(Geom_Surface)&);
		static Handle(Geom2d_Curve) ProjectCurveOnSurf(const Handle(Geom_Curve)&, const Handle(Geom_Surface)&);

		static std::vector<Pnt3d> CalcCrackPoints(const std::vector<Pnt3d>& thePnts, const std::vector<Standard_Real>& theDs, const gp_Ax1&);

		static Handle(Geom_Curve) Interpolate(const std::vector<Pnt3d>&);

		static std::tuple<TopoDS_Face, TopoDS_Face, TopoDS_Face> 
			CreateTrimSurf(const std::vector<Pnt2d>& thePnts, const Standard_Real theWidth, const TopoDS_Face&);

		// the first is the inner side face and the second is the outer, the first paired is the upper curves and the last is the lower curves [5/1/2023 Payvand]
		static std::tuple<TopoDS_Face, TopoDS_Face, std::pair<Handle(Geom_Curve), Handle(Geom_Curve)>, std::pair<Handle(Geom_Curve), Handle(Geom_Curve)>>
			CreateCrackSurface
			(
				const Handle(Geom_Curve)& theOuter, 
				const Handle(Geom_Curve)& theInner, 
				const Handle(Geom2d_Curve)& theCrack,
				const Handle(Geom_Surface)& thePlane
			);

		static TopoDS_Face CreateSidePlane(const Handle(Geom_Curve)& theOuter, const Handle(Geom_Curve)& theInner, const Handle(Geom_Surface)& thePlane);

		static std::vector<Handle(Geom_Curve)> OuterBoundaryCurves(const TopoDS_Face&);

		//static TopoDS_Face CreateUpperFaceLeft()
	};
}

#endif // !_Tools_Header

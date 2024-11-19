#pragma once
#ifndef _NModel_SurfaceGeometry_Header
#define _NModel_SurfaceGeometry_Header

#include <Global_AccessMethod.hxx>
#include <Global_Handle.hxx>
#include <OFstream.hxx>

#include <opencascade/TopoDS_Face.hxx>

class Geom_Surface;
class Poly_Triangulation;

namespace tnbLib
{

	class NModel_SurfaceGeometry
	{

		/*Private Data*/

		Handle(Geom_Surface) theGeometry_;

		TopoDS_Face theFace_;


		static void CheckGeometry(const Handle(Geom_Surface)& thePatch, const char* theName);

	protected:

		NModel_SurfaceGeometry
		(
			const Handle(Geom_Surface)& theGeometry
		)
			: theGeometry_(theGeometry)
		{
			//CheckGeometry(theGeometry, "NModel_SurfaceGeometry()");
		}

	public:

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		Handle(Poly_Triangulation) RetrieveTriangulation() const;


		//- Io functions and operators

		void ExportPlaneCurvesToPlt(OFstream& File) const;

		void ExportToPlt(OFstream& File) const;

		void ExportMetricDetToPlt(OFstream& File) const;

		void ExportMetricDetPlaneToPlt(OFstream& File) const;

		//- Macros
		GLOBAL_ACCESS_SINGLE(TopoDS_Face, Face)
	};
}

#endif // !_NModel_SurfaceGeometry_Header
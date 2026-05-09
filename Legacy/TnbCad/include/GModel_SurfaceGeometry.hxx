#pragma once
#ifndef _GModel_SurfaceGeometry_Header
#define _GModel_SurfaceGeometry_Header

#include <Cad_Module.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <Global_Handle.hxx>
#include <OFstream.hxx>

class Geom_Surface;
class Poly_Triangulation;

#include <opencascade/TopoDS_Face.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Cad_GeomSurface;
	class Pnt2d;
	class Pnt3d;

	class GModel_SurfaceGeometry
	{

		/*Private Data*/

		std::shared_ptr<Cad_GeomSurface> theGeometry_;

		TopoDS_Face theFace_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:


		// default constructor

		GModel_SurfaceGeometry()
		{}

		TnbCad_EXPORT GModel_SurfaceGeometry
		(
			const std::shared_ptr<Cad_GeomSurface>& theGeometry
		);

		TnbCad_EXPORT GModel_SurfaceGeometry
		(
			std::shared_ptr<Cad_GeomSurface>&& theGeometry
		);

	public:


		// public functions and operators [6/13/2022 Amir]

		const auto& GeomSurface() const
		{
			return theGeometry_;
		}

		TnbCad_EXPORT Handle(Poly_Triangulation) RetrieveTriangulation() const;

		TnbCad_EXPORT Pnt3d Value
		(
			const Pnt2d& theCoord
		) const;

		//- Io functions and operators

		void ExportToPlt(OFstream& File) const;

		void ExportMetricDetToPlt(OFstream& File) const;

		void ExportMetricDetPlaneToPlt(OFstream& File) const;

		//- Macros
		GLOBAL_ACCESS_SINGLE(TopoDS_Face, Face)
	};
}

#endif // !_GModel_SurfaceGeometry_Header

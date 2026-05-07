#pragma once
#ifndef _TModel_SurfaceGeometry_Header
#define _TModel_SurfaceGeometry_Header

#include <Standard_Handle.hxx>
#include <TopoDS_Face.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <Cad_Module.hxx>
#include <OFstream.hxx>

class Geom_Surface;
class Poly_Triangulation;

namespace tnbLib
{
	
	// Forward Declarations [6/21/2022 Amir]
	class Cad_GeomSurface;

	class TModel_SurfaceGeometry
	{

		/*Private Data*/

		std::shared_ptr<Cad_GeomSurface> theGeometry_;
		Handle(Poly_Triangulation) theMesh_;

		//TopoDS_Face theFace_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

		static void CheckGeometry(const Handle(Geom_Surface)& thePatch, const char* theName);

	protected:

		TModel_SurfaceGeometry()
		{
			theMesh_.Nullify();
		}

		TModel_SurfaceGeometry
		(
			const std::shared_ptr<Cad_GeomSurface>& theGeometry
		)
			: theGeometry_(theGeometry)
		{
			theMesh_.Nullify();
			//CheckGeometry(theGeometry, "TModel_SurfaceGeometry()");
		}

	public:

		const auto& GeomSurface() const
		{
			return theGeometry_;
		}

		const auto& Triangulation() const
		{
			return theMesh_;
		}

		//Handle(Poly_Triangulation) RetrieveTriangulation() const;

		void SetTriangulation(const Handle(Poly_Triangulation)& tri)
		{
			theMesh_ = tri;
		}


		//- Io functions and operators

		void ExportPlaneCurvesToPlt(OFstream& File) const;

		void ExportToPlt(OFstream& File) const;

		void ExportMetricDetToPlt(OFstream& File) const;

		void ExportMetricDetPlaneToPlt(OFstream& File) const;

		//- Macros
		//GLOBAL_ACCESS_SINGLE(TopoDS_Face, Face)
	};
}

#endif // !_TModel_SurfaceGeometry_Header

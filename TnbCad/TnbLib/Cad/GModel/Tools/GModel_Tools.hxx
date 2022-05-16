#pragma once
#ifndef _GModel_Tools_Header
#define _GModel_Tools_Header

#include <Cad_Module.hxx>
#include <Entity2d_BoxFwd.hxx>

#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>

#include <memory>
#include <vector>

class TopoDS_Face;
class TopoDS_Edge;
class TopoDS_Shape;
class Geom_Surface;
class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations
	class GModel_Surface;
	class GModel_Edge;
	class GModel_Plane;
	class GModel_Wire;
	class GModel_ParaWire;
	class GModel_ParaCurve;
	class Geo_ApprxCurve_Info;
	class OFstream;

	class GModel_Tools
	{

	public:

		static TnbCad_EXPORT std::vector<std::shared_ptr<GModel_ParaCurve>> 
			MakeCurves
			(
				const std::vector<Handle(Geom2d_Curve)>&
			);

		static TnbCad_EXPORT std::vector<Handle(Geom2d_Curve)> 
			RetrieveGeometries
			(
				const std::vector<std::shared_ptr<GModel_ParaCurve>>&
			);

		static TnbCad_EXPORT std::vector<Handle(Geom2d_Curve)> RetrieveGeometries(const GModel_ParaWire&);
		static TnbCad_EXPORT Handle(Geom_Surface) RetrieveGeometry(const GModel_Surface&);

		static TnbCad_EXPORT Standard_Boolean IsPlane(const std::shared_ptr<GModel_Surface>&);
		static TnbCad_EXPORT Standard_Boolean IsCylinder(const std::shared_ptr<GModel_Surface>&);

		static TnbCad_EXPORT Standard_Boolean IsUniMetric(const std::shared_ptr<GModel_Surface>&);

		static TnbCad_EXPORT std::pair<std::shared_ptr<GModel_ParaCurve>, std::shared_ptr<GModel_ParaCurve>> 
			Split
			(
				const Standard_Real x, 
				const std::shared_ptr<GModel_ParaCurve>&
			);

		static TnbCad_EXPORT std::shared_ptr<GModel_Edge>
			GetEdge
			(
				const TopoDS_Edge& theEdge, 
				const TopoDS_Face& theFace,
				const Standard_Integer theIndex
			);

		static TnbCad_EXPORT std::shared_ptr<GModel_Surface>
			GetSurface
			(
				const TopoDS_Face& theFace
			);

		static TnbCad_EXPORT std::vector<std::shared_ptr<GModel_Surface>> 
			GetSurfaces
			(
				const TopoDS_Shape& theShape
			);

		static TnbCad_EXPORT Entity2d_Box CalcBoundingBox(const GModel_ParaWire&);

		static TnbCad_EXPORT std::shared_ptr<GModel_ParaCurve> 
			Trim
			(
				const std::shared_ptr<GModel_ParaCurve>&, 
				const Standard_Real theU0, 
				const Standard_Real theU1
			);

		// no changing is applied to a wire with a curve [2/21/2022 Amir]
		static TnbCad_EXPORT std::shared_ptr<GModel_ParaWire> 
			TrimWire
			(
				const std::shared_ptr<GModel_ParaWire>&
			);

		static TnbCad_EXPORT std::shared_ptr<GModel_ParaWire> 
			GetOuterParaWire
			(
				const std::shared_ptr<GModel_Surface>&
			);

		static TnbCad_EXPORT std::vector<std::shared_ptr<GModel_ParaWire>> 
			GetInnerParaWires
			(
				const std::shared_ptr<GModel_Surface>&
			);

		static TnbCad_EXPORT std::shared_ptr<GModel_Plane> 
			GetParaPlane
			(
				const std::shared_ptr<GModel_Surface>&, 
				const Standard_Real theTol
			);

		static TnbCad_EXPORT std::shared_ptr<GModel_ParaWire> MakeWire(const std::shared_ptr<GModel_ParaCurve>&);
		static TnbCad_EXPORT std::shared_ptr<GModel_ParaWire> MakeWire(const std::vector<std::shared_ptr<GModel_ParaCurve>>&);

		static TnbCad_EXPORT std::shared_ptr<GModel_ParaWire> 
			FillGaps
			(
				const std::shared_ptr<GModel_ParaWire>&, 
				const Standard_Real theTol
			);

		static TnbCad_EXPORT std::shared_ptr<GModel_ParaWire> 
			RepairWire
			(
				const std::shared_ptr<GModel_ParaWire>&,
				const Standard_Real theTol
			);

		static TnbCad_EXPORT std::shared_ptr<GModel_ParaWire>
			RemoveIntersections
			(
				const std::shared_ptr<GModel_ParaWire>&,
				const Standard_Real theTol
			);

		static TnbCad_EXPORT void ExportToPlt
		(
			const std::shared_ptr<GModel_Plane>&,
			const std::shared_ptr<Geo_ApprxCurve_Info>&,
			OFstream&
		);

		static TnbCad_EXPORT void ExportToPlt
		(
			const std::shared_ptr<GModel_ParaWire>&, 
			const std::shared_ptr<Geo_ApprxCurve_Info>&, 
			OFstream&
		);
	};
}

#endif // !_GModel_Tools_Header

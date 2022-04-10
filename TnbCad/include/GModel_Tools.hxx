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

namespace tnbLib
{

	// Forward Declarations
	class GModel_Surface;
	class GModel_Edge;
	class GModel_Plane;
	class GModel_Wire;
	class GModel_ParaWire;
	class GModel_ParaCurve;

	class GModel_Tools
	{

	public:

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
	};
}

#endif // !_GModel_Tools_Header

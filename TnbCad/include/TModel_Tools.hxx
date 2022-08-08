#pragma once
#ifndef _TModel_Tools_Header
#define _TModel_Tools_Header

#include <Entity3d_BoxFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Cad_Module.hxx>

#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>

#include <memory>
#include <vector>

class TopoDS_Face;
class TopoDS_Edge;
class TopoDS_Shape;
class Geom_Surface;
class Geom2d_Curve;
class gp_Trsf2d;

namespace tnbLib
{

	// Forward Declarations [3/16/2022 Amir]
	class Cad_TModel;
	class TModel_ParaCurve;
	class TModel_Surface;
	class TModel_ParaWire;
	class TModel_Plane;

	class TModel_Tools
	{

		/*Private Data*/

	public:

		static TnbCad_EXPORT Entity3d_Box CalcBoundingBox(const Cad_TModel&);

		static TnbCad_EXPORT Standard_Boolean IsPlane(const std::shared_ptr<TModel_Surface>&);
		static TnbCad_EXPORT Standard_Boolean IsCylinder(const std::shared_ptr<TModel_Surface>&);

		static TnbCad_EXPORT std::vector<std::shared_ptr<TModel_ParaCurve>>
			MakeParaCurves
			(
				const std::vector<Handle(Geom2d_Curve)>&
			);

		static TnbCad_EXPORT std::vector<Handle(Geom2d_Curve)>
			RetrieveGeometries
			(
				const std::vector<std::shared_ptr<TModel_ParaCurve>>&
			);

		static TnbCad_EXPORT std::vector<Handle(Geom2d_Curve)>
			RetrieveGeometries(const TModel_ParaWire&);

		static TnbCad_EXPORT Handle(Geom_Surface) 
			RetrieveGeometry(const TModel_Surface&);

		static TnbCad_EXPORT std::pair<std::shared_ptr<TModel_ParaCurve>, std::shared_ptr<TModel_ParaCurve>> 
			Split
			(
				const Standard_Real x, 
				const std::shared_ptr<TModel_ParaCurve>&
			);

		static TnbCad_EXPORT Entity2d_Box CalcBoundingBox(const TModel_ParaWire&);

		static TnbCad_EXPORT std::shared_ptr<TModel_ParaCurve>
			Trim
			(
				const std::shared_ptr<TModel_ParaCurve>&,
				const Standard_Real theU0,
				const Standard_Real theU1
			);

		// no changing is applied to a wire with a curve [6/21/2022 Amir]
		static TnbCad_EXPORT std::shared_ptr<TModel_ParaWire> TrimWire(const std::shared_ptr<TModel_ParaWire>&);

		static TnbCad_EXPORT std::shared_ptr<TModel_ParaWire>
			GetOuterParaWire
			(
				const std::shared_ptr<TModel_Surface>&
			);

		static TnbCad_EXPORT std::vector<std::shared_ptr<TModel_ParaWire>>
			GetInnerParaWires
			(
				const std::shared_ptr<TModel_Surface>&
			);

		static TnbCad_EXPORT std::shared_ptr<TModel_Plane>
			GetParaPlane
			(
				const std::shared_ptr<TModel_Surface>&,
				const Standard_Real theTol
			);

		static TnbCad_EXPORT std::shared_ptr<TModel_ParaWire> MakeWire(const std::shared_ptr<TModel_ParaCurve>&);
		static TnbCad_EXPORT std::shared_ptr<TModel_ParaWire> MakeWire(const std::vector<std::shared_ptr<TModel_ParaCurve>>&);

		static TnbCad_EXPORT std::shared_ptr<TModel_ParaWire>
			FillGaps
			(
				const std::shared_ptr<TModel_ParaWire>&,
				const Standard_Real theTol
			);

		static TnbCad_EXPORT std::shared_ptr<TModel_ParaWire>
			RepairWire
			(
				const std::shared_ptr<TModel_ParaWire>&,
				const Standard_Real theTol
			);

		static TnbCad_EXPORT std::shared_ptr<TModel_ParaWire>
			RemoveIntersections
			(
				const std::shared_ptr<TModel_ParaWire>&,
				const Standard_Real theTol
			);

		static TnbCad_EXPORT std::pair<std::shared_ptr<TModel_ParaCurve>, std::shared_ptr<TModel_ParaCurve>>
			RepairIntersection
			(
				const std::shared_ptr<TModel_ParaCurve>& theC0,
				const std::shared_ptr<TModel_ParaCurve>& theC1,
				const Standard_Real theTol
			);
	};
}

#endif // !_TModel_Tools_Header

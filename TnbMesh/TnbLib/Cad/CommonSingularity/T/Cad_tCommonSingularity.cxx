#include <Cad_tCommonSingularity.hxx>

#include <Aft2d_tRegionPlaneSurface.hxx>
#include <Aft2d_tPlnWireSurface.hxx>
#include <Aft2d_tPlnCurveSurface.hxx>
#include <Cad_tPoleSingularCurve.hxx>
#include <TModel_ParaDegenCurve.hxx>
#include <Cad_Tools.hxx>
#include <TModel_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	auto RetrieveGeometries(const std::vector<std::shared_ptr<Aft2d_tPlnCurveSurface>>& theCurves)
	{
		std::vector<Handle(Geom2d_Curve)> curves;
		curves.reserve(theCurves.size());
		for (const auto& x : theCurves)
		{
			Debug_Null_Pointer(x);
			const auto& c = x->Curve();
			Debug_Null_Pointer(c);

			curves.push_back(c->Geometry());
		}
		return std::move(curves);
	}

	auto ReplaceDegeneracies
	(
		const std::shared_ptr<Aft2d_tPlnWireSurface>& theWire,
		const std::shared_ptr<TModel_Surface>& theSurface,
		const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo,
		const Standard_Real theTol
	)
	{
		static auto isDegenerated = 
			[]
		(
			const Handle(Geom2d_Curve)& theCurve,
			const Handle(Geom_Surface)& theSurface,
			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo,
			const Standard_Real theTol
			)
		{
			auto len = Cad_Tools::CalcLength(theCurve, theSurface, theInfo);
			return len <= theTol;
		};

		const auto& oldCurves = theWire->Curves();
		auto geometries = RetrieveGeometries(theWire->Curves());
		auto surf = TModel_Tools::RetrieveGeometry(*theSurface);

		std::vector<std::shared_ptr<Aft2d_tPlnCurveSurface>> curves;
		curves.reserve(oldCurves.size());

		Standard_Integer k = 0;
		for (const auto& x : geometries)
		{
			if (isDegenerated(x, surf, theInfo, theTol))
			{
				auto pm = x->Value(MEAN(x->FirstParameter(), x->LastParameter()));
				auto c = std::make_shared<Cad_tPoleSingularCurve>(oldCurves.at(k)->Curve(), pm);
				curves.push_back(std::move(c));
			}
			else
			{
				curves.push_back(oldCurves.at(k));
			}
			k++;
		}
		auto wire = std::make_shared<Aft2d_tPlnWireSurface>(theWire->Index(), theWire->Name(), std::move(curves));
		return std::move(wire);
	}

	auto ReplaceDegeneracies
	(
		const std::shared_ptr<Aft2d_tPlnWireSurface>& theWire
	)
	{
		std::vector<std::shared_ptr<Aft2d_tPlnCurveSurface>> curves;
		curves.reserve(theWire->Curves().size());
		for (const auto& x : theWire->Curves())
		{
			Debug_Null_Pointer(x);
			const auto& curve = x->Curve();
			Debug_Null_Pointer(curve);

			if (auto degen = std::dynamic_pointer_cast<TModel_ParaDegenCurve>(curve))
			{
				auto pm = x->Value(MEAN(x->FirstParameter(), x->LastParameter()));
				auto c = std::make_shared<Cad_tPoleSingularCurve>(curve, pm);
				curves.push_back(std::move(c));
			}
			else
			{
				curves.push_back(x);
			}
		}
		auto wire = std::make_shared<Aft2d_tPlnWireSurface>(theWire->Index(), theWire->Name(), std::move(curves));
		return std::move(wire);
	}
}

template<>
void tnbLib::Cad_tCommonSingularity::Perform()
{
	if (NOT Plane())
	{
		FatalErrorIn(FunctionSIG)
			<< "no plane has been loaded." << endl
			<< abort(FatalError);
	}

	auto id = Plane()->Index();
	const auto& name = Plane()->Name();

	const auto& outer = Plane()->Outer();
	auto newOuter = ReplaceDegeneracies(outer/*, Surface(), IntegInfo(), Tolerance()*/);

	if (Plane()->Inner())
	{
		std::vector<std::shared_ptr<Aft2d_tPlnWireSurface>> innerWires;
		innerWires.reserve(Plane()->NbHoles());
		for (const auto& x : *Plane()->Inner())
		{
			auto newInner = ReplaceDegeneracies(x/*, Surface(), IntegInfo(), Tolerance()*/);
			innerWires.push_back(std::move(newInner));
		}

		auto pln =
			std::make_shared<Aft2d_tRegionPlaneSurface>
			(
				id, name, nullptr, outer,
				std::make_shared<std::vector<std::shared_ptr<Aft2d_tPlnWireSurface>>>(std::move(innerWires))
				);
		ModifiedRef() = std::move(pln);
	}
	else
	{
		auto pln =
			std::make_shared<Aft2d_tRegionPlaneSurface>
			(
				id, name, nullptr, outer,
				nullptr
				);
		ModifiedRef() = std::move(pln);
	}

	Change_IsDone() = Standard_True;
}
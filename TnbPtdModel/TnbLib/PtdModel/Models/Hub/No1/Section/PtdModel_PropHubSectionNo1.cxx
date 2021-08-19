#include <PtdModel_PropHubSectionNo1.hxx>

#include <PtdModel_Par.hxx>
#include <PtdModel_WrappedBladeSection.hxx>
#include <PtdModel_BladeGlobalPars.hxx>
#include <PtdModel_BladeInfo.hxx>
#include <PtdModel_BladeView.hxx>
#include <PtdModel_PropBlade.hxx>
#include <PtdModel_PropHub.hxx>
#include <PtdModel_PropHubParsNo1.hxx>
#include <PtdModel_HubCurves.hxx>
#include <Geo_BoxTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <TColgp_Array1OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <Geom_BSplineCurve.hxx>

Standard_Real tnbLib::PtdModel_PropHubSectionNo1::DEFAULT_EPSILON(1.0E-4);

namespace tnbLib
{

	std::pair<Standard_Real, Standard_Real>
		CalcBound(const std::shared_ptr<PtdModel_BladeView>& bladeView, const Standard_Real eps)
	{
		if (NOT bladeView)
		{
			FatalErrorIn(FunctionSIG)
				<< "no blade view has been found!" << endl
				<< abort(FatalError);
		}

		if (bladeView->WrappedSections().empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "the wrapped section list is empty!" << endl
				<< abort(FatalError);
		}
		const auto& root = bladeView->WrappedSections()[0];
		const auto b0 = Geo_BoxTools::GetBox(root->Back(), 0);
		const auto b1 = Geo_BoxTools::GetBox(root->Face(), 0);

		auto b = Geo_BoxTools::Union(b0, b1);
		b.Expand(b.Diameter()*eps);

		auto t = std::make_pair(b.P0().Z(), b.P1().Z());
		return std::move(t);
	}
}

std::vector<std::shared_ptr<tnbLib::PtdModel_HubCurve>>
tnbLib::PtdModel_PropHubSectionNo1::SectionCurves(const PtdModel_PropHub& theHub) const
{
	const auto& pars = theHub.Parameters();
	auto parsNo1 = std::dynamic_pointer_cast<PtdModel_PropHubParsNo1>(pars);
	if (NOT parsNo1)
	{
		FatalErrorIn(FunctionSIG)
			<< "no parameter for the no1 hub model has been found" << endl
			<< abort(FatalError);
	}

	if (NOT parsNo1->Offset())
	{
		FatalErrorIn(FunctionSIG)
			<< "no offset parameter has been found!" << endl
			<< abort(FatalError);
	}
	const auto offset = parsNo1->Offset()->Value();

	const auto& blade = theHub.Blade();
	if (NOT blade)
	{
		FatalErrorIn(FunctionSIG)
			<< "no blade has been found!" << endl
			<< abort(FatalError);
	}

	const auto& inf = blade->BladeInfo();
	if (NOT inf)
	{
		FatalErrorIn(FunctionSIG)
			<< "no info for the blade has been found!" << endl
			<< abort(FatalError);
	}

	const auto& glPars = inf->Globals();
	if (NOT glPars)
	{
		FatalErrorIn(FunctionSIG)
			<< "no global parameters have been found!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(glPars->HubRadius());
	const auto radius = glPars->HubRadius()->Value()*(1.0 + DEFAULT_EPSILON);

	const auto& bladeView = blade->BladeView();
	const auto[z0, z1] = CalcBound(bladeView, DEFAULT_EPSILON);

	Pnt3d p0(radius, 0, z0);
	Pnt3d p1(radius, 0, z1);

	static const Standard_Integer nbPoles = 2;
	static const Standard_Integer degree = 1;

	static const size_t nbCurves = 3;

	std::vector<std::shared_ptr<PtdModel_HubCurve>> curves;
	curves.reserve(nbCurves);

	TColgp_Array1OfPnt poles0(1, nbPoles);
	poles0.SetValue(1, p0);
	poles0.SetValue(2, p1);

	TColStd_Array1OfReal knots(1, 2);
	knots.SetValue(1, 0.0);
	knots.SetValue(2, 1.0);

	TColStd_Array1OfInteger mults(1, 2);
	mults.SetValue(1, 2);
	mults.SetValue(2, 2);

	Handle(Geom_Curve) geom0 = new Geom_BSplineCurve(poles0, knots, mults, degree);
	auto curve0 = std::make_shared<ptdModel::HubCurve_Hub>(std::move(geom0));
	
	Pnt3d p2(0, 0, z0);

	TColgp_Array1OfPnt poles1(1, nbPoles);
	poles1.SetValue(1, p2);
	poles1.SetValue(2, p0);

	Handle(Geom_Curve) geom1 = new Geom_BSplineCurve(poles1, knots, mults, degree);
	auto curve1 = std::make_shared<ptdModel::HubCurve_Nose>(std::move(geom1));

	Pnt3d p3(0, 0, z1);

	TColgp_Array1OfPnt poles2(1, nbPoles);
	poles2.SetValue(1, p3);
	poles2.SetValue(2, p1);

	Handle(Geom_Curve) geom2 = new Geom_BSplineCurve(poles2, knots, mults, degree);
	auto curve2 = std::make_shared<ptdModel::HubCurve_Tail>(std::move(geom2));

	curves.push_back(std::move(curve0));
	curves.push_back(std::move(curve1));
	curves.push_back(std::move(curve2));

	return std::move(curves);
}
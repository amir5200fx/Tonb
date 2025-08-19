#include <Cad2d_RepairWire.hxx>

#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/Geom2dAPI_InterCurveCurve.hxx>
#include <opencascade/Geom2d_TrimmedCurve.hxx>

const std::shared_ptr<tnbLib::NumAlg_AdaptiveInteg_Info> tnbLib::Cad2d_RepairWire::DEFAULT_INTEG_INFO =
std::make_shared<tnbLib::NumAlg_AdaptiveInteg_Info>();

namespace tnbLib
{

	class RepairWireIntegInfoRunTime
	{

		/*Private Data*/

	public:

		// default constructor [6/16/2022 Amir]

		RepairWireIntegInfoRunTime()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

void tnbLib::RepairWireIntegInfoRunTime::SetInfo()
{
	const auto& info = Cad2d_RepairWire::DEFAULT_INTEG_INFO;
	info->SetMaxNbIterations(100);
	info->SetNbInitIterations(4);
	info->SetTolerance(1.0E-6);
}

static const tnbLib::RepairWireIntegInfoRunTime myRepairWireIntegInfoRunTimeObj;

std::vector<Handle(Geom2d_Curve)>
tnbLib::Cad2d_RepairWire::RepairWire
(
	const Handle(Geom2d_Curve)& theC0,
	const Handle(Geom2d_Curve)& theC1
)
{
	std::vector<Handle(Geom2d_Curve)> curves;
	curves.reserve(3);

	auto[c0, c1] = Subdivide(theC0, MEAN(theC0->FirstParameter(), theC0->LastParameter()));
	curves.push_back(std::move(c0));
	curves.push_back(std::move(c1));
	curves.push_back(theC1);

	auto tCrvs = RepairWire(curves);

	auto C0 = RetrieveCurve(tCrvs.at(0), tCrvs.at(1));
	auto C1 = tCrvs.at(2);

	std::vector<Handle(Geom2d_Curve)> wire;
	wire.reserve(2);

	wire.push_back(std::move(C0));
	wire.push_back(std::move(C1));

	return std::move(wire);
}

std::vector<Handle(Geom2d_Curve)>
tnbLib::Cad2d_RepairWire::RepairWire
(
	const std::vector<Handle(Geom2d_Curve)>& theCurves
)
{
	Debug_If_Condition(theCurves.size() < 3);

	std::map<Standard_Integer, Handle(Geom2d_Curve)> reg;
	Standard_Integer id = 0;
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);
		auto paired = std::make_pair(++id, x);
		auto insert = reg.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data!" << endl
				<< abort(FatalError);
		}
	}

	Debug_Null_Pointer(LastItem(theCurves));
	Debug_Null_Pointer(FirstItem(theCurves));

	const auto& c0 = LastItem(theCurves);
	const auto& c1 = FirstItem(theCurves);

	auto[trimmed0, trimmed1] = RepairIntersection(c0, c1, Tolerance());

	reg.at(1) = trimmed1;
	reg.at(theCurves.size()) = trimmed0;

	for (size_t i = 1; i < theCurves.size(); i++)
	{
		const auto& c0 = reg.at(i);
		const auto& c1 = reg.at(i + 1);

		Debug_Null_Pointer(c0);
		Debug_Null_Pointer(c1);

		auto[trimmed0, trimmed1] = RepairIntersection(c0, c1, Tolerance());

		reg.at(i) = trimmed0;
		reg.at(i + 1) = trimmed1;
	}

	std::vector<Handle(Geom2d_Curve)> trimmedCurves;
	trimmedCurves.reserve(theCurves.size());
	for (const auto& x : reg)
	{
		Debug_Null_Pointer(x.second);
		trimmedCurves.push_back(x.second);
	}

	return std::move(trimmedCurves);
}

Handle(Geom2d_Curve) 
tnbLib::Cad2d_RepairWire::RetrieveGeometry
(
	const Handle(Geom2d_Curve)& theCurve
)
{
	auto trimmed = Handle(Geom2d_TrimmedCurve)::DownCast(theCurve);
	if (trimmed)
	{
		return trimmed->BasisCurve();
	}
	else
	{
		return theCurve;
	}
}

Handle(Geom2d_Curve) 
tnbLib::Cad2d_RepairWire::RetrieveCurve
(
	const Handle(Geom2d_Curve)& theC0,
	const Handle(Geom2d_Curve)& theC1
)
{
	Debug_Null_Pointer(theC0);
	Debug_Null_Pointer(theC1);

	auto geom = RetrieveGeometry(theC0);
	const auto x0 = theC0->FirstParameter();
	const auto x1 = theC1->LastParameter();

	auto t = Pln_CurveTools::Trim(geom, x0, x1);
	return std::move(t);
}

Handle(Geom2d_Curve)
tnbLib::Cad2d_RepairWire::RetrieveCurve
(
	const Handle(Geom2d_Curve)& theC0,
	const Handle(Geom2d_Curve)& theC1,
	const Handle(Geom2d_Curve)& theC2
)
{
	Debug_Null_Pointer(theC0);
	Debug_Null_Pointer(theC1);
	Debug_Null_Pointer(theC2);

	auto geom = RetrieveGeometry(theC0);
	const auto x0 = theC0->FirstParameter();
	const auto x1 = theC2->LastParameter();

	auto t = Pln_CurveTools::Trim(geom, x0, x1);
	return std::move(t);
}

std::pair<Handle(Geom2d_Curve), Handle(Geom2d_Curve)> 
tnbLib::Cad2d_RepairWire::Subdivide
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real x
)
{
	auto c0 = Pln_CurveTools::Trim
	(
		theCurve,
		theCurve->FirstParameter(),
		x
	);
	auto c1 = Pln_CurveTools::Trim
	(
		theCurve,
		x,
		theCurve->LastParameter()
	);
	auto t = std::make_pair(std::move(c0), std::move(c1));
	return std::move(t);
}

std::pair<Handle(Geom2d_Curve), Handle(Geom2d_Curve)> 
tnbLib::Cad2d_RepairWire::RepairIntersection
(
	const Handle(Geom2d_Curve)& theC0, 
	const Handle(Geom2d_Curve)& theC1, 
	const Standard_Real theTol
)
{
	auto alg = Pln_Tools::Intersection(theC0, theC1, theTol);

	std::vector<Standard_Real> params0;
	std::vector<Standard_Real> params1;
	if (alg->NbPoints())
	{
		for (Standard_Integer i = 1; i <= alg->NbPoints(); i++)
		{
			auto p0 = alg->Intersector().Point(i).ParamOnFirst();
			auto p1 = alg->Intersector().Point(i).ParamOnSecond();

			params0.push_back(p0);
			params1.push_back(p1);
		}
	}
	if (alg->NbSegments())
	{
		for (Standard_Integer i = 1; i <= alg->NbSegments(); i++)
		{
			auto p0 = alg->Intersector().Segment(i).FirstPoint().ParamOnFirst();
			auto p1 = alg->Intersector().Segment(i).LastPoint().ParamOnSecond();

			params0.push_back(p0);
			params1.push_back(p1);
		}
	}
	if (params0.empty())
	{
		auto paired = std::make_pair(theC0, theC1);
		return std::move(paired);
	}

	std::sort(params0.begin(), params0.end());
	std::sort(params1.begin(), params1.end());

	std::vector<Standard_Real> mParams0;
	{
		mParams0.push_back(params0.at(0));
		for (size_t i = 1; i < params0.size(); i++)
		{
			if (std::abs(params0.at(i) - params0.at(i - 1)) > theTol)
			{
				mParams0.push_back(params0.at(i));
			}
		}
	}
	std::vector<Standard_Real> mParams1;
	{
		mParams1.push_back(params1.at(0));
		for (size_t i = 1; i < params1.size(); i++)
		{
			if (std::abs(params1.at(i) - params1.at(i - 1)) > theTol)
			{
				mParams1.push_back(params1.at(i));
			}
		}
	}

	{
		auto p0 = FirstItem(mParams0);
		if (p0 > theC0->LastParameter()) p0 = theC0->LastParameter();

		Handle(Geom2d_Curve) trimmed0;
		if (std::abs(p0 - theC0->LastParameter()) <= theTol)
		{
			trimmed0 = theC0;
		}
		else
		{
			trimmed0 = Pln_CurveTools::Trim(theC0, theC0->FirstParameter(), p0);
		}
		if (NOT INSIDE(p0, theC0->FirstParameter(), theC0->LastParameter()))
		{
			FatalErrorIn(FunctionSIG)
				<< "something went wrong in intersection alg." << endl
				<< abort(FatalError);
		}

		auto p1 = LastItem(mParams1);
		if (p1 < theC1->FirstParameter()) p1 = theC1->FirstParameter();

		Handle(Geom2d_Curve) trimmed1;
		if (std::abs(p1 - theC1->FirstParameter()) <= theTol)
		{
			trimmed1 = theC1;
		}
		else
		{
			trimmed1 = Pln_CurveTools::Trim(theC1, p1, theC1->LastParameter());
		}
		if (NOT INSIDE(p1, theC1->FirstParameter(), theC1->LastParameter()))
		{
			FatalErrorIn(FunctionSIG)
				<< "something went wrong in intersection alg." << endl
				<< abort(FatalError);
		}

		auto paired = std::make_pair(std::move(trimmed0), std::move(trimmed1));
		return std::move(paired);
	}
}

const Standard_Real tnbLib::Cad2d_RepairWire::DEFAULT_TOLERANCE = 1.0E-6;

#include <Pln_Tools.hxx>

void tnbLib::Cad2d_RepairWire::Perform()
{
	std::vector<Handle(Geom2d_Curve)> curves;
	for (const auto& x : theCurves_)
	{
		Debug_Null_Pointer(x);
		if (Pln_Tools::Length(*x, IntegInfo()) > Tolerance())
		{
			curves.push_back(x);
		}
	}

	/*OFstream myFile("curves2d.plt");
	for (const auto& x : theCurves_)
	{
		Pln_CurveTools::ExportToPlt(x, myFile, 20);
	}
	std::exit(1);*/

	if (curves.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve list is empty." << endl
			<< abort(FatalError);
	}

	if (curves.size() IS_EQUAL 1)
	{
		auto curve = FirstItem(curves);
		Debug_Null_Pointer(curve);

		auto p = 0.75*curve->FirstParameter() + 0.25*curve->LastParameter();
		auto[c0, c1] = Subdivide(curve, p);
		auto wire = RepairWire(c0, c1);
		
		auto retrieved = RetrieveCurve(wire.at(0), wire.at(1));

		theWire_.push_back(std::move(retrieved));
	}
	else if (curves.size() IS_EQUAL 2)
	{
		auto wire = RepairWire(FirstItem(curves), LastItem(curves));
		WireRef() = std::move(wire);
	}
	else
	{
		auto wire = RepairWire(curves);
		WireRef() = std::move(wire);
	}
	Change_IsDone() = Standard_True;
}
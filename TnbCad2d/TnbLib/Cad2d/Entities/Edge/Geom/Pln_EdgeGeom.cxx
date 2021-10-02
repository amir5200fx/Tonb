#include <Pln_EdgeGeom.hxx>

#include <Entity2d_Polygon.hxx>
#include <Geo2d_ApprxCurve.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

tnbLib::Pnt2d 
tnbLib::Pln_EdgeGeom::FirstCoord() const
{
	if (NOT Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge is not discretized!" << endl
			<< abort(FatalError);
	}
	return FirstItem(Mesh()->Points());
}

tnbLib::Pnt2d 
tnbLib::Pln_EdgeGeom::LastCoord() const
{
	if (NOT Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge is not discretized!" << endl
			<< abort(FatalError);
	}
	return LastItem(Mesh()->Points());
}

tnbLib::Pnt2d 
tnbLib::Pln_EdgeGeom::FirstCoord(const Standard_Boolean theSense) const
{
	if (theSense)
	{
		auto pt = FirstCoord();
		return std::move(pt);
	}
	else
	{
		auto pt = LastCoord();
		return std::move(pt);
	}
}

tnbLib::Pnt2d
tnbLib::Pln_EdgeGeom::LastCoord(const Standard_Boolean theSense) const
{
	if (theSense)
	{
		auto pt = LastCoord();
		return std::move(pt);
	}
	else
	{
		auto pt = FirstCoord();
		return std::move(pt);
	}
}

void tnbLib::Pln_EdgeGeom::Approx
(
	const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
) const
{
	if (NOT Curve())
	{
		FatalErrorIn("void Approx(const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo) const")
			<< "the Edge has no curve inside!" << endl
			<< abort(FatalError);
	}

	if (Curve()->IsLinear())
	{
		auto& pts = Mesh()->Points();
		pts.reserve(2);

		pts.push_back(Curve()->FirstCoord());
		pts.push_back(Curve()->LastCoord());
	}
	else
	{
		const auto& curve = *Curve();
		Geo2d_ApprxCurve approx
		(
			curve.Geometry(),
			curve.FirstParameter(),
			curve.LastParameter(), theInfo);

		approx.Perform();
		Debug_If_Condition_Message(NOT approx.IsDone(), "the algorithm is not performed!");

		const auto& chain = approx.Chain();

		Mesh() = std::make_shared<Entity2d_Polygon>();
		Debug_Null_Pointer(Mesh());

		auto& pts = Mesh()->Points();
		pts = std::move(chain->Points());
	}
}


#include <Cad2d_Modeler_SrchEng.hxx>

#include <Entity2d_Box.hxx>
#include <Pln_Vertex.hxx>
#include <error.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::cad2dLib::Modeler_SrchEng::CheckDomain() const
{
	return &theCorners_.GeometryBoundingBox() IS_EQUAL &null_domain;
}

void tnbLib::cad2dLib::Modeler_SrchEng::CheckDomain
(
	const char * theName
) const
{
	if (CheckDomain())
	{
		FatalErrorIn(theName)
			<< "no domain is specified!" << endl
			<< abort(FatalError);
	}
}

namespace tnbLib
{
	const std::shared_ptr<cad2dLib::Modeler_Corner> cad2dLib::Modeler_SrchEng::null =
		std::make_shared<cad2dLib::Modeler_Corner>();

	const Entity2d_Box cad2dLib::Modeler_SrchEng::null_domain = 
		Entity2d_Box(Pnt2d(0, 0), Pnt2d(1, 1));
}

tnbLib::cad2dLib::Modeler_SrchEng::Modeler_SrchEng()
	: theMaxRadius_(1.0E-3)
{
	theCorners_.SetGeometryCoordFunc(&Modeler_Corner::GetCoord);
	theCorners_.SetGeometryRegion(null_domain);
}

const std::shared_ptr<tnbLib::cad2dLib::Modeler_Corner>&
tnbLib::cad2dLib::Modeler_SrchEng::SelectCorner
(
	const Pnt2d & theCoord
) const
{
#ifdef _DEBUG
	CheckDomain("const std::shared_ptr<cad2dLib::Modeler_Corner>& SelectCorner(const Pnt2d& theCoord) const");
#endif // DEBUG

	Debug_If_Condition_Message(Radius() <= gp::Resolution(), "Invalid radius");

	Entity2d_Box b(theCoord - Radius(), theCoord + Radius());
	std::vector<std::shared_ptr<cad2dLib::Modeler_Corner>> items;
	theCorners_.GeometrySearch(b, items);

	if (items.empty())
	{
		return null;
	}

	if (items.size() IS_EQUAL 1) return items[0];
	return Modeler_SrchEng::MinDist(items, theCoord);
}

std::shared_ptr<tnbLib::cad2dLib::Modeler_Corner>
tnbLib::cad2dLib::Modeler_SrchEng::FindCorner
(
	const std::shared_ptr<Pln_Vertex>& theVtx
) const
{
#ifdef _DEBUG
	CheckDomain("const std::shared_ptr<cad2dLib::Modeler_Corner>& FindCorner(const std::shared_ptr<Pln_Vertex>& theVtx) const");
#endif // DEBUG

	Debug_If_Condition_Message(Radius() <= gp::Resolution(), "Invalid radius");

	Debug_Null_Pointer(theVtx);
	const auto& centre = theVtx->Coord();

	Entity2d_Box b(centre - Radius(), centre + Radius());
	std::vector<std::shared_ptr<cad2dLib::Modeler_Corner>> items;
	theCorners_.GeometrySearch(b, items);

	if (items.empty())
	{
		return null;
	}

	for (const auto& x : items)
	{
		Debug_Null_Pointer(x);
		const auto& verties = x->Vertices();

		auto iter = verties.find(theVtx->Index());
		if (iter NOT_EQUAL verties.end())
		{
			return x;
		}
	}
	return null;
}

void tnbLib::cad2dLib::Modeler_SrchEng::ReArrangeSrchEngine()
{
#ifdef _DEBUG
	CheckDomain("void ReArrangeSrchEngine()");
#endif // DEBUG

	std::vector<std::shared_ptr<cad2dLib::Modeler_Corner>>
		items;
	theCorners_.RetrieveFromGeometryTo(items);

	for (const auto& x : items)
		theCorners_.RemoveFromGeometry(x);

	const auto& b0 = theCorners_.GeometryBoundingBox();
	const auto[dx, dy] = b0.Length();

	theCorners_.SetGeometryRegion(b0.Expanded(0.5*dx, 0.5*dy));
	theCorners_.InsertToGeometry(items);
}

void tnbLib::cad2dLib::Modeler_SrchEng::InsertToSrchEngine
(
	const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner
)
{
#ifdef _DEBUG
	CheckDomain("void InsertToSrchEngine(const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner)");
#endif // DEBUG

	const auto& domain = theCorners_.GeometryBoundingBox();
	if (NOT domain.IsInside(theCorner->Coord()))
	{
		ReArrangeSrchEngine();
	}

	theCorners_.InsertToGeometry(theCorner);
}

void tnbLib::cad2dLib::Modeler_SrchEng::RemoveFromSrchEngine
(
	const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner
)
{
	theCorners_.RemoveFromGeometry(theCorner);
}

void tnbLib::cad2dLib::Modeler_SrchEng::SetMaxRadius
(
	const Standard_Real theRadius
)
{
	theMaxRadius_ = theRadius;
}

void tnbLib::cad2dLib::Modeler_SrchEng::SetDomain
(
	const Entity2d_Box & theDomain
)
{
	theCorners_.SetGeometryRegion(theDomain);
}

Standard_Boolean
tnbLib::cad2dLib::Modeler_SrchEng::IsNull
(
	const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner
)
{
	return (Standard_Boolean)(theCorner IS_EQUAL null);
}

const std::shared_ptr<tnbLib::cad2dLib::Modeler_Corner>& 
tnbLib::cad2dLib::Modeler_SrchEng::MinDist
(
	const std::vector<std::shared_ptr<cad2dLib::Modeler_Corner>>& theCorners,
	const Pnt2d & theCentre
)
{
	size_t id = 0;
	Standard_Real dmin = RealLast();

	size_t k = 0;
	for (const auto& x : theCorners)
	{
		auto d = theCentre.SquareDistance(x->Coord());
		if (d <= dmin)
		{
			id = k;
			dmin = d;
		}
		k++;
	}
	return theCorners[id];
}
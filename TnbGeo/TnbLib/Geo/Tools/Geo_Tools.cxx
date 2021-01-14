#include <Geo_Tools.hxx>

#include <Entity2d_Polygon.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity2d_Chain.hxx>
#include <Entity3d_Chain.hxx>
#include <Entity3d_Triangulation.hxx>

tnbLib::Pnt2d
tnbLib::Geo_Tools::GetIntersectionPoint
(
	const std::shared_ptr<IntersectEntity2d>& entity
)
{
	auto ent = std::dynamic_pointer_cast<PointIntersectEntity2d>(entity);
	if (NOT ent)
	{
		FatalErrorIn(FunctionSIG)
			<< " the intersection type is not point" << endl
			<< abort(FatalError);
	}
	return ent->IntPnt;
}

tnbLib::Entity2d_Segment
tnbLib::Geo_Tools::GetIntersectionSegment
(
	const std::shared_ptr<IntersectEntity2d>& entity
)
{
	auto ent = std::dynamic_pointer_cast<SegmentIntersectEntity2d>(entity);
	if (NOT ent)
	{
		FatalErrorIn(FunctionSIG)
			<< " the intersection type is not segment" << endl
			<< abort(FatalError);
	}
	Entity2d_Segment seg(ent->Segment.P0(), ent->Segment.P1());
	return std::move(seg);
}

tnbLib::Pnt2d 
tnbLib::Geo_Tools::IntersectionTwoLines
(
	const Pnt2d & P0,
	const Dir2d & td0, 
	const Pnt2d & P1, 
	const Dir2d & td1,
	const Standard_Real theTol
)
{
	if (td0.IsParallel(td1, theTol))
	{
		FatalErrorIn(FunctionSIG)
			<< "the two lines are parallel" << endl
			<< abort(FatalError);
	}

	Vec2d t0(td0.XY());
	Vec2d t1(td1.XY());

	const auto dp = P1 - P0;
	const auto denom = t0.Crossed(t1);

	const auto nume = Vec2d(dp.XY()).Crossed(t1);

	const auto alf = nume / denom;

	const auto pt = P0 + alf * Pnt2d(t0.XY());
	return std::move(pt);
}

std::shared_ptr<tnbLib::Entity2d_Chain> 
tnbLib::Geo_Tools::RetrieveChain
(
	const Entity2d_Polygon & thePoly
)
{
	auto chain = std::make_shared<Entity2d_Chain>();
	Debug_Null_Pointer(chain);

	chain->Points() = thePoly.Points();
	chain->Connectivity() = dualConnectivityList_Chain(thePoly.NbPoints() - 1);
	
	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity3d_Chain>
tnbLib::Geo_Tools::RetrieveChain
(
	const Entity3d_Polygon & thePoly
)
{
	auto chain = std::make_shared<Entity3d_Chain>();
	Debug_Null_Pointer(chain);

	chain->Points() = thePoly.Points();
	chain->Connectivity() = dualConnectivityList_Chain(thePoly.NbPoints() - 1);

	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity2d_Chain> 
tnbLib::Geo_Tools::RetrieveChain
(
	const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePoly
)
{
	auto chain = std::make_shared<Entity2d_Chain>();
	Debug_Null_Pointer(chain);

	auto& pts = chain->Points();
	auto& indices = chain->Connectivity();

	Standard_Integer nbPts = 0;
	for (const auto& poly : thePoly)
	{
		Debug_Null_Pointer(poly);

		for (const auto& pt : poly->Points())
		{
			pts.push_back(pt);
		}

		auto l = 
			dualConnectivityList_Chain(poly->NbPoints() - 1);
		for (const auto& x : l)
		{
			auto i0 = x.Value(0) + nbPts;
			auto i1 = x.Value(1) + nbPts;

			connectivity::dual edge;

			edge.Value(0) = i0;
			edge.Value(1) = i1;

			indices.push_back(std::move(edge));
		}

		nbPts += poly->NbPoints();
	}
	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity3d_Chain>
tnbLib::Geo_Tools::RetrieveChain
(
	const std::vector<std::shared_ptr<Entity3d_Polygon>>& thePoly
)
{
	auto chain = std::make_shared<Entity3d_Chain>();
	Debug_Null_Pointer(chain);

	auto& pts = chain->Points();
	auto& indices = chain->Connectivity();

	Standard_Integer nbPts = 0;
	for (const auto& poly : thePoly)
	{
		Debug_Null_Pointer(poly);

		for (const auto& pt : poly->Points())
		{
			pts.push_back(pt);
		}

		auto l =
			dualConnectivityList_Chain(poly->NbPoints() - 1);
		for (const auto& x : l)
		{
			auto i0 = x.Value(0) + nbPts;
			auto i1 = x.Value(1) + nbPts;

			connectivity::dual edge;

			edge.Value(0) = i0;
			edge.Value(1) = i1;

			indices.push_back(std::move(edge));
		}

		nbPts += poly->NbPoints();
	}
	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity3d_Chain>
tnbLib::Geo_Tools::RetrieveChain
(
	const std::vector<std::shared_ptr<Entity3d_Chain>>& theChains
)
{
	auto chain = std::make_shared<Entity3d_Chain>();
	Debug_Null_Pointer(chain);

	auto& pts = chain->Points();
	auto& indices = chain->Connectivity();

	Standard_Integer nbPts = 0;
	for (const auto& ch : theChains)
	{
		Debug_Null_Pointer(ch);

		for (const auto& pt : ch->Points())
		{
			pts.push_back(pt);
		}

		for (const auto& x : ch->Connectivity())
		{
			auto i0 = x.Value(0) + nbPts;
			auto i1 = x.Value(1) + nbPts;

			connectivity::dual edge;

			edge.Value(0) = i0;
			edge.Value(1) = i1;

			indices.push_back(std::move(edge));
		}

		nbPts += ch->NbPoints();
	}
	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity3d_Triangulation> 
tnbLib::Geo_Tools::Triangulation
(
	const Entity3d_Chain & theChain
)
{
	auto tr = std::make_shared<Entity3d_Triangulation>();
	Debug_Null_Pointer(tr);

	auto& pts = tr->Points();
	auto& indices = tr->Connectivity();

	pts = theChain.Points();
	for (const auto& x : theChain.Connectivity())
	{
		auto i0 = x.Value(0);
		auto i1 = x.Value(1);

		connectivity::triple t;
		t.Value(0) = i0;
		t.Value(1) = i1;
		t.Value(2) = i0;

		indices.push_back(std::move(t));
	}
	return std::move(tr);
}

size_t 
tnbLib::Geo_Tools::FindSpan
(
	const Standard_Real x, 
	const std::vector<Standard_Real>& theSorted
)
{
#ifdef _DEBUG
	CheckSorted(theSorted, "size_t Geo_Tools::FindSpan(Args...)");
#endif // _DEBUG

	auto high = theSorted.size() - 1;
	if (x IS_EQUAL theSorted[high])
	{
		return high;
	}

	size_t low = 0;
	auto mid = (low + high) / 2;
	while (x < theSorted[mid] OR x >= theSorted[mid + 1])
	{
		if (x < theSorted[mid]) high = mid;
		else low = mid;
		mid = (low + high) / 2;
	}
	return mid;
}

void tnbLib::Geo_Tools::CheckSorted
(
	const std::vector<Standard_Real>& theSorted,
	const char* theName
)
{
	auto iter = theSorted.begin();
	auto x0 = *iter;

	iter++;
	while (iter NOT_EQUAL theSorted.end())
	{
		if (*iter < x0)
		{
			FatalErrorIn(theName)
				<< "the vector is not sorted!" << endl
				<< abort(FatalError);
		}
		x0 = *iter;
		iter++;
	}
}
#include <Cad2d_EdgeEdgeTrim.hxx>

#include <Pln_Curve.hxx>
#include <Cad2d_EdgeEdgeIntersection.hxx>
#include <Cad2d_IntsctEntity_Pair.hxx>
#include <Cad2d_IntsctEntity_Point.hxx>
#include <Cad2d_IntsctEntity_Segment.hxx>
#include <Cad2d_IntsctEntity_TangSegment.hxx>
#include <Cad2d_IntsctEntity_OrthSegment.hxx>
#include <Cad2d_IntsctEntity.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Cad2d_EdgeEdgeTrim::Cad2d_EdgeEdgeTrim()
{
}

tnbLib::Cad2d_EdgeEdgeTrim::Cad2d_EdgeEdgeTrim
(
	const std::shared_ptr<Cad2d_EdgeEdgeIntersection>& theAlg
)
	: theIntersection_(theAlg)
{
}

const std::shared_ptr<tnbLib::Pln_Edge>& 
tnbLib::Cad2d_EdgeEdgeTrim::Edge0() const
{
	return Intersection()->Edge0();
}

const std::shared_ptr<tnbLib::Pln_Edge>& 
tnbLib::Cad2d_EdgeEdgeTrim::Edge1() const
{
	return Intersection()->Edge1();
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::Cad2d_EdgeEdgeTrim::RetrieveCurves() const
{
	std::vector<std::shared_ptr<Pln_Curve>> Q;
	RetrieveCurvesTo(Q);
	return std::move(Q);
}

std::shared_ptr<tnbLib::Pln_Curve> 
tnbLib::Cad2d_EdgeEdgeTrim::SelectToTrim
(
	const Standard_Integer theIndex
)
{
	auto iter = theCurves_.find(theIndex);
	if (iter NOT_EQUAL theCurves_.end())
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeTrim::SelectToTrim(const Standard_Integer theIndex)")
			<< "the item is not in the map!" << endl
			<< abort(FatalError);
	}

	auto trimmed = std::move(iter->second);
	theCurves_.erase(iter);

	return std::move(trimmed);
}

void tnbLib::Cad2d_EdgeEdgeTrim::Perform(const Standard_Real theTol)
{
	if (NOT Intersection())
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeTrim::Perform()")
			<< "the intersection algorithm is not loaded!" << endl
			<< abort(FatalError);
	}

	const auto& alg = *Intersection();
	/*if (NOT alg.IsDone())
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeTrim::Perform()")
			<< "the intersection algorithm is not performed!" << endl
			<< abort(FatalError);
	}*/

	if (NOT alg.NbEntities())
	{
		Change_IsDone() = Standard_True;
		return;
	}

	std::vector<std::shared_ptr<Cad2d_IntsctEntity_Segment>> entities0;
	std::vector<std::shared_ptr<Cad2d_IntsctEntity_Segment>> entities1;

	for (const auto& x : alg.Entities())
	{
		Debug_Null_Pointer(x);

		const auto& ent0 = x->Entity0();
		Debug_Null_Pointer(ent0);

		const auto& ent1 = x->Entity1();
		Debug_Null_Pointer(ent1);

		auto seg0 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(ent0);
		Debug_Null_Pointer(seg0);

		auto seg1 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(ent1);
		Debug_Null_Pointer(seg1);

		entities0.push_back(std::move(seg0));
		entities1.push_back(std::move(seg1));
	}

	auto sub0 = Cad2d_IntsctEntity_Segment::SubdivideEdge(Edge0(), entities0, theTol);
	auto sub1 = Cad2d_IntsctEntity_Segment::SubdivideEdge(Edge1(), entities1, theTol);

	auto& curves = ChangeCurves();

	Standard_Integer nbCurves = 0;
	for (const auto& x : sub0)
	{
		Debug_Null_Pointer(x);
		x->Index() = ++nbCurves;

		curves.insert(std::make_pair(nbCurves, x));
	}

	for (const auto& x : sub1)
	{
		Debug_Null_Pointer(x);
		x->Index() = ++nbCurves;

		curves.insert(std::make_pair(nbCurves, x));
	}

	Change_IsDone() = Standard_True;
}

void tnbLib::Cad2d_EdgeEdgeTrim::RetrieveCurvesTo
(
	std::vector<std::shared_ptr<Pln_Curve>>& theCurves
) const
{
	theCurves.reserve(NbCurves());
	for (const auto& x : theCurves_)
	{
		Debug_Null_Pointer(x.second);
		theCurves.push_back(x.second);
	}
}
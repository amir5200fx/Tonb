#include <Cad2d_IntsctEntity_Segment.hxx>

#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Cad2d_IntsctEntity_OrthSegment.hxx>
#include <Cad2d_IntsctEntity_TangSegment.hxx>

#include <algorithm>

tnbLib::Cad2d_IntsctEntity_Segment::Cad2d_IntsctEntity_Segment
(
	const Standard_Integer theIndex
)
	: Cad2d_IntsctEntity(theIndex)
{
}

tnbLib::Cad2d_IntsctEntity_Segment::Cad2d_IntsctEntity_Segment
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Cad2d_IntsctEntity(theIndex, theName)
{
}

Standard_Boolean 
tnbLib::Cad2d_IntsctEntity_Segment::CompareEntities
(
	const std::shared_ptr<Cad2d_IntsctEntity_Segment>& theEntity0,
	const std::shared_ptr<Cad2d_IntsctEntity_Segment>& theEntity1
)
{
	Debug_Null_Pointer(theEntity0);
	Debug_Null_Pointer(theEntity1);

	return theEntity0->CharParameter() < theEntity1->CharParameter();
}

void tnbLib::Cad2d_IntsctEntity_Segment::SortEntities
(
	std::vector<std::shared_ptr<Cad2d_IntsctEntity_Segment>>& theEntities
)
{
	std::sort(theEntities.begin(), theEntities.end(), &CompareEntities);
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::Cad2d_IntsctEntity_Segment::SubdivideEdge
(
	const std::shared_ptr<Pln_Edge>& theEdge,
	const std::vector<std::shared_ptr<Cad2d_IntsctEntity_Segment>>& theEntities,
	const Standard_Real theTol
)
{
	auto curve = theEdge->Curve();

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	for (const auto& x : theEntities)
	{
		Debug_Null_Pointer(x);

		if (x->IsOrthogonal())
		{
			auto orth = std::dynamic_pointer_cast<Cad2d_IntsctEntity_OrthSegment>(x);
			Debug_Null_Pointer(orth);

			if (
				std::abs(orth->CharParameter() - curve->FirstParameter()) 
				<= gp::Resolution() 
				OR 
				std::abs(orth->CharParameter() - curve->LastParameter()) 
				<= gp::Resolution()
				)
			{
				continue;
			}

			auto[c0, c1] = curve->Split(orth->CharParameter());

			if (NOT c0)
			{
				continue;
			}

			if (NOT c1)
			{
				continue;
			}

			Debug_Null_Pointer(c0);
			Debug_Null_Pointer(c1);

			if (Pln_Curve::IsValid(c0, theTol))
			{
				curves.push_back(c0);
			}

			curve = c1;
		}
		else
		{
			auto tang = std::dynamic_pointer_cast<Cad2d_IntsctEntity_TangSegment>(x);
			Debug_Null_Pointer(tang);

			if (std::abs(tang->Parameter0() - tang->Parameter1()) <= gp::Resolution())
			{
				continue;
			}

			auto[c0, c1, c2] = curve->Split(*tang);

			/*Debug_Null_Pointer(c0);
			Debug_Null_Pointer(c1);
			Debug_Null_Pointer(c2);*/

			Debug_Null_Pointer(c1);

			if (c0 AND Pln_Curve::IsValid(c0, theTol))
			{
				curves.push_back(c0);
			}

			if (Pln_Curve::IsValid(c1, theTol))
			{
				curves.push_back(c1);
			}

			curve = c2;

			if (NOT curve)
			{
				break;
			}
		}
	}

	if (curve AND Pln_Curve::IsValid(curve, theTol)) curves.push_back(curve);
	return std::move(curves);
}
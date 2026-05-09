#include <Cad2d_IntsctEntity_Segment.hxx>

#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Cad2d_IntsctEntity_OrthSegment.hxx>
#include <Cad2d_IntsctEntity_TangSegment.hxx>

#include <algorithm>

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
	typedef std::shared_ptr<Cad2d_IntsctEntity_Segment> intsctSegment_t;
	typedef std::shared_ptr<Pln_Curve> curve_t;

	static auto par_distance = [](const intsctSegment_t& ent, const curve_t& curve)
	{
		return std::min
		(
			std::abs(ent->CharParameter() - curve->FirstParameter()),
			std::abs(ent->CharParameter() - curve->LastParameter())
		);
	};

	typedef std::shared_ptr<Cad2d_IntsctEntity_TangSegment> tangSegment_t;

	static auto tang_segment_par_length = [](const tangSegment_t& t)
	{
		return std::abs(t->Parameter0() - t->Parameter1());
	};

	auto curve = theEdge->Curve();

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	for (const auto& x : theEntities)
	{
		Debug_Null_Pointer(x);

		if (x->IsOrthogonal())
		{
			if (par_distance(x, curve) <= gp::Resolution())
			{
				continue;
			}

			auto[c0, c1] = curve->Split(x->CharParameter());

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

			/*if (Pln_Curve::IsValid(c0, theTol))
			{
				curves.push_back(c0);
			}*/

			curves.push_back(std::move(c0));

			curve = c1;
		}
		else
		{
			auto tang = std::dynamic_pointer_cast<Cad2d_IntsctEntity_TangSegment>(x);
			Debug_Null_Pointer(tang);

			if (tang_segment_par_length(tang) <= gp::Resolution())
			{
				continue;
			}

			auto[c0, c1, c2] = curve->Split(*tang);

			/*Debug_Null_Pointer(c0);
			Debug_Null_Pointer(c1);
			Debug_Null_Pointer(c2);*/

			Debug_Null_Pointer(c1);

			if (c0 /*AND Pln_Curve::IsValid(c0, theTol)*/)
			{
				curves.push_back(std::move(c0));
			}

			/*if (Pln_Curve::IsValid(c1, theTol))
			{
				curves.push_back(c1);
			}*/

			curves.push_back(std::move(c1));

			curve = c2;

			if (NOT curve)
			{
				break;
			}
		}
	}

	if (curve /*AND Pln_Curve::IsValid(curve, theTol)*/) curves.push_back(std::move(curve));
	return std::move(curves);
}
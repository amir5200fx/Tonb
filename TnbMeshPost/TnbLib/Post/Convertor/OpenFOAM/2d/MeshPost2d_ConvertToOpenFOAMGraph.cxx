#include <MeshPost2d_ConvertToOpenFOAM.hxx>

#include <Entity2d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::pair
<
	std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Vertex>>,
	std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Segment>>
>
tnbLib::MeshPost2d_ConvertToOpenFOAM::CalcGragh
(
	const Entity2d_Triangulation& theTris,
	const std::vector<std::pair<Standard_Integer, Standard_Integer>>& theBoundaries
)
{
	std::vector<std::shared_ptr<Vertex>> vertices;
	Standard_Integer k = 0;
	for (const auto& x : theTris.Points())
	{
		auto v = std::make_shared<Vertex>(++k);
		vertices.push_back(std::move(v));
	}

	std::vector<std::shared_ptr<Segment>> segments;
	k = 0;
	for (const auto& x : theBoundaries)
	{
		const auto& v0 = vertices.at(Index_Of(x.first));
		const auto& v1 = vertices.at(Index_Of(x.second));

		std::array<std::shared_ptr<Vertex>, Segment::nbVertices> paired = { v0,v1 };
		auto seg = std::make_shared<Segment>(++k, std::move(paired));
		v0->Insert(seg);
		v1->Insert(seg);

		segments.push_back(std::move(seg));
	}
	const auto maxBndId = segments.size();
	for (const auto& x : theTris.Connectivity())
	{
		auto i0 = Index_Of(x.Value(0));
		auto i1 = Index_Of(x.Value(1));
		auto i2 = Index_Of(x.Value(2));

		const auto& v0 = vertices.at(i0);
		const auto& v1 = vertices.at(i1);
		const auto& v2 = vertices.at(i2);

		if (Segment::IsValidToCreate(v0, v1))
		{// segment 0 [6/28/2023 Payvand]
			std::array<std::shared_ptr<Vertex>, Segment::nbVertices> paired = { v0,v1 };
			auto seg = std::make_shared<Segment>(++k, std::move(paired));
			v0->Insert(seg);
			v1->Insert(seg);

			segments.push_back(std::move(seg));
		}
		if (Segment::IsValidToCreate(v1, v2))
		{// segment 1 [6/28/2023 Payvand]
			std::array<std::shared_ptr<Vertex>, Segment::nbVertices> paired = { v1,v2 };
			auto seg = std::make_shared<Segment>(++k, std::move(paired));
			v1->Insert(seg);
			v2->Insert(seg);

			segments.push_back(std::move(seg));
		}
		if (Segment::IsValidToCreate(v2, v0))
		{// segment 2 [6/28/2023 Payvand]
			std::array<std::shared_ptr<Vertex>, Segment::nbVertices> paired = { v2,v0 };
			auto seg = std::make_shared<Segment>(++k, std::move(paired));
			v2->Insert(seg);
			v0->Insert(seg);

			segments.push_back(std::move(seg));
		}
	}
	const auto nbIntSegments = segments.size() - maxBndId;
	k = 0;
	for (size_t i = 0; i < maxBndId; i++)
	{
		segments.at(i)->Index() += (Standard_Integer)nbIntSegments;
	}
	for (size_t i = maxBndId; i < segments.size(); i++)
	{
		segments.at(i)->Index() = ++k;
	}
	auto t = std::make_pair(vertices, segments);
	return std::move(t);
}
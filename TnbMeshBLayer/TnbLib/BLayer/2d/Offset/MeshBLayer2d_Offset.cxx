#include <MeshBLayer2d_Offset.hxx>

#include <Geo2d_UniformNet.hxx>
#include <Entity2d_QuadMesh.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	auto RetrievePairs(const Entity2d_Polygon& thePoly0, const Entity2d_Polygon& thePoly1)
	{
		const auto n = thePoly0.NbPoints();
		if (n < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "Invalid polygon has been detected." << endl
				<< abort(FatalError);
		}
		std::vector<std::pair<Pnt2d, Pnt2d>> pairs;
		pairs.reserve(n);
		const auto& pts0 = thePoly0.Points();
		const auto& pts1 = thePoly1.Points();
		for (size_t i = 0; i < n; i++)
		{
			const auto& p0 = pts0.at(i);
			const auto& p1 = pts1.at(i);
			pairs.push_back({ p0,p1 });
		}
		return std::move(pairs);
	}

	auto UniformDistb(const Standard_Integer n)
	{
		std::vector<Standard_Real> parameters;
		parameters.reserve(n + 1);
		if(n<1)
		{
			FatalErrorIn(FunctionSIG)
				<< "Invalid no. of segments has been detected." << endl
				<< abort(FatalError);
		}
		const Standard_Real du = 1.0 / (Standard_Real)n;
		for (size_t i = 0; i <= n; i++)
		{
			auto u = i * du;
			parameters.push_back(u);
		}
		return std::move(parameters);
	}

	auto DiscreteSegment
	(
		const std::pair<Pnt2d, Pnt2d>& theCoords,
		const std::vector<Standard_Real>& us,
		const Standard_Real theBeta
	)
	{
		auto [p0, p1] = theCoords;
		const auto du = p1 - p0;
		const auto delta = p0.Distance(p1);
		std::vector<Pnt2d> pts;
		pts.reserve(us.size());
		//std::cout << "p0 = " << p0 << ", p1= " << p1 << std::endl;
		for (const auto u:us)
		{
			auto eta = 1.0 - u;
			if (eta < 0.0) eta = 0.0;
			if (eta > 1.0) eta = 1.0;
			//std::cout << "eta = " << eta << std::endl;
			const auto t = MeshBLayer2d_Offset::CalcRate(theBeta, eta);
			//std::cout << "u = " << u << ", t = " << t << std::endl;
			auto pt = du * t + p0;
			//std::cout << pt << std::endl;
			pts.emplace_back(std::move(pt));
		}
		//PAUSE;
		return std::move(pts);
	}

	auto Reverse(std::vector<std::vector<Pnt2d>>& theCoords)
	{
		const auto ni = theCoords.at(0).size();
		const auto nj = theCoords.size();
		std::vector<Pnt2d> reversed;
		for (size_t i = 0; i < ni; i++)
		{
			for (size_t j = 0; j < nj; j++)
			{
				auto& pt = theCoords.at(j).at(i);
				reversed.emplace_back(std::move(pt));
			}
		}
		return std::move(std::move(reversed));
	}
}

void tnbLib::MeshBLayer2d_Offset::Perform()
{
	if (NOT Polygon())
	{
		FatalErrorIn(FunctionSIG)
			<< "No polygon has been loaded." << endl
			<< abort(FatalError);
	}
	const auto& polygon = *Polygon();
	if (NOT Offset())
	{
		FatalErrorIn(FunctionSIG)
			<< "No offset has been loaded." << endl
			<< abort(FatalError);
	}
	const auto& offset = *Offset();
	if (polygon.NbPoints() NOT_EQUAL offset.NbPoints())
	{
		FatalErrorIn(FunctionSIG)
			<< "the size of the polygons are not the same." << endl
			<< abort(FatalError);
	}
	const auto pts = RetrievePairs(polygon, offset);
	const auto us = UniformDistb(ClusterSize());
	std::vector<std::vector<Pnt2d>> coords;
	for (const auto& pair:pts)
	{
		auto offsets = DiscreteSegment(pair, us, Rate());
		coords.emplace_back(std::move(offsets));
	}
	const auto nj = coords.at(0).size() - 1;
	const auto ni = coords.size() - 1;
	//std::cout << "ni: " << ni << ", nj: " << nj << std::endl;
	auto tot_coords = Reverse(coords);
	std::vector<connectivity::quadruple> indices;
	{
		const auto alg = std::make_shared<Geo2d_UniformNet>();
		alg->SetNi(ni);
		alg->SetNj(nj);
		alg->Perform();
		auto& net = alg->IndicesRef();
		indices = std::move(net);
	}
	theMesh_ = 
		std::make_shared<Entity2d_QuadMesh>
	(std::move(tot_coords), std::move(indices));
}

Standard_Real 
tnbLib::MeshBLayer2d_Offset::CalcRate
(
	const Standard_Real theBeta, 
	const Standard_Real theEta
)
{
	const auto cte = (theBeta + 1.0) / (theBeta - 1.0);
	const auto pow = std::pow(cte, theEta);
	return (1.0 - theBeta * (pow - 1.0) / (pow + 1.0));
}
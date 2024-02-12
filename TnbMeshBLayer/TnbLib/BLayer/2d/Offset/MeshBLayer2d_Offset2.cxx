#include <Entity_Polygon.hxx>
#include <Entity2d_QuadMesh.hxx>
#include <Entity2d_CmpMesh.hxx>
#include <Entity2d_CmpConnect_Quad.hxx>
#include <Entity2d_CmpConnect_Triangle.hxx>
#include <MeshBLayer2d_Offset2.hxx>
#include <Merge2d_QuadMesh.hxx>
#include <Geo2d_UniformNet.hxx>

std::vector<std::pair<tnbLib::Pnt2d, tnbLib::Pnt2d>>
tnbLib::MeshBLayer2d_Offset2::RetrievePairs() const
{
	std::vector<Pnt2d> offsets;
	std::vector<Pnt2d> polygon;
	for (const auto& x: theOffset_)
	{
		offsets.emplace_back(x->coord);
		const auto node = x->paired.lock();
		Debug_Null_Pointer(node);
		polygon.emplace_back(node->coord);
	}
	std::vector<std::pair<Pnt2d, Pnt2d>> pairs;
	for (size_t i = 0; i < offsets.size(); i++)
	{
		const auto& p0 = polygon.at(i);
		const auto& p1 = offsets.at(i);
		pairs.push_back({ p0,p1 });
	}
	return std::move(pairs);
}

void tnbLib::MeshBLayer2d_Offset2::CalculateStrip()
{
	{// check the wire is closed.
		const auto& pnts = thePolygon_->Points();
		const auto& p0 = pnts.at(0);
		const auto& p1 = pnts.at(pnts.size() - 1);
		if (p0.Distance(p1) > 1.0e-6)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the wire is not closed." << endl
				<< abort(FatalError);
		}
	}
	const auto& pnts0 = thePolygon_->Points();
	const auto& pnts1 = theGeoOffset_->Points();
	Standard_Real d = RealLast();
	for (Standard_Integer i = 0; i < pnts0.size(); i++)
	{
		d = std::min(pnts0.at(i).Distance(pnts1.at(i)), d);
	}
	std::vector<Dir2d> m_normals;
	m_normals.reserve(pnts0.size() - 1);
	for (size_t i = 0; i < pnts0.size() - 1; i++)
	{
		const auto& p0 = pnts0.at(i);
		const auto& p1 = pnts1.at(i);
		m_normals.emplace_back(Dir2d{ p0,p1 });
	}
	m_normals.emplace_back(m_normals.at(0));
	std::vector<Dir2d> normals;
	for (size_t i = 0; i < pnts0.size() - 1; i++)
	{
		const auto& p0 = pnts0.at(i);
		const auto& p1 = pnts0.at(i + 1);
		normals.emplace_back(CalcNormal(p0, p1));
	}
	normals.emplace_back(normals.at(0));
	for (int i = 0; i < m_normals.size(); i++)
	{
		auto v0 = i - 1;
		if (v0 < 0)
		{
			v0 = static_cast<int>(normals.size()) - 1;
		}
		const auto vm = i;
		const auto v1 = i;
		const auto& n0 = normals.at(v0);
		const auto& nm = m_normals.at(vm);
		const auto& n1 = normals.at(v1);

		const auto ang0 = std::abs(CalcAngle(n0, nm));
		const auto ang1 = std::abs(CalcAngle(nm, n1));
		const auto& p0 = pnts0.at(i);
		const auto& p1 = pnts1.at(i);
		/*const auto d0 = pnts0.at(v0).Distance(pnts1.at(v0));
		const auto d1 = pnts0.at(v1).Distance(pnts1.at(v1));
		const auto d = p0.Distance(p1);*/
		//std::cout << "d = " << d << std::endl;
		auto node0 = std::make_shared<Node>(p0);

		std::vector<std::shared_ptr<Node>> lefts;
		if (ang0 > ChevronAngle())
		{
			const auto nbSubs = static_cast<int>(std::ceil(ang0 / ChevronAngle()));
			const auto du = 1.0 / static_cast<Standard_Real>(nbSubs);
			//const auto dd = (d1 - d0) / static_cast<Standard_Real>(nbSubs);
			auto u = n0;
			for (size_t i = 0; i < nbSubs; i++)
			{
				const auto da = i * du * ang0;
				auto u1 = u.Rotated(-da);
				//auto di = d0 + i * dd;
				auto pt = p0 + d * u1;
				auto node = std::make_shared<LeftNode>(pt);
				node->paired = node0;
				lefts.emplace_back(node);
			}
		}
		auto pt = p0 + d * nm;
		auto node1 = std::make_shared<CentreNode>(pt);
		node1->paired = node0;
		std::vector<std::shared_ptr<Node>> rights;
		if (ang1 > ChevronAngle())
		{
			const auto nbSubs = static_cast<int>(std::ceil(ang1 / ChevronAngle()));
			const auto du = 1.0 / static_cast<Standard_Real>(nbSubs);
			auto u = nm;
			for (size_t i = 1; i <= nbSubs; i++)
			{
				const auto da = i * du * ang1;
				auto u1 = u.Rotated(-da);
				auto pt = p0 + d * u1;
				auto node = std::make_shared<RightNode>(pt);
				node->paired = node0;
				rights.emplace_back(node);
			}
		}
		node1->lefts = std::move(lefts);
		node1->rights = std::move(rights);
		theStrip_.emplace_back(std::make_pair(node0, node1));
	}
}

void tnbLib::MeshBLayer2d_Offset2::RetrieveTopoOffset()
{
	{
		const auto& node = theStrip_.at(0).second;
		theOffset_.emplace_back(node);
		for (const auto& x: node->rights)
		{
			theOffset_.emplace_back(x);
		}
	}
	for (size_t i = 1; i < theStrip_.size(); i++)
	{
		const auto& node = theStrip_.at(i).second;
		for (const auto& x: node->lefts)
		{
			theOffset_.emplace_back(x);
		}
		theOffset_.emplace_back(node);
		for (const auto& x: node->rights)
		{
			theOffset_.emplace_back(x);
		}
	}
	{
		const auto& node = theStrip_.at(0).second;
		for (const auto& x : node->lefts)
		{
			theOffset_.emplace_back(x);
		}
	}
}

void tnbLib::MeshBLayer2d_Offset2::CreateMesh()
{
	static auto push_to_list = [](Standard_Integer i, std::vector<Standard_Integer>& l)
		{
			for (const auto j:l)
			{
				if (j IS_EQUAL i)
				{
					return;
				}
			}
			l.emplace_back(i);
		};
	const auto pts = RetrievePairs();
	const auto us = UniformDistb(ClusterSize());
	std::vector<std::vector<Pnt2d>> coords;
	for (const auto& pair: pts)
	{
		auto [p0, p1] = pair;
		const auto dis = p0.Distance(p1);
		const auto tm = FirstLayer() / dis;
		if (tm > 0.9)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Invalid the first layer thickness has been detected." << endl
				<< abort(FatalError);
		}
		auto pm = p0 + tm * (p1 - p0);
		std::vector<Pnt2d> offsets;
		offsets.emplace_back(p0);
		for (const auto& x : DiscreteSegment({ pm, p1 }, us, Rate()))
		{
			offsets.emplace_back(x);
		}
		coords.emplace_back(std::move(offsets));
	}
	const auto nj = coords.at(0).size() - 1;
	const auto ni = coords.size() - 1;
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
	const auto mesh = 
		std::make_shared<Entity2d_QuadMesh>
	(std::move(tot_coords), std::move(indices));
	const auto merge = std::make_shared<Merge2d_QuadMesh>();
	merge->Import(*mesh);
	merge->InfoAlg().SetRadius(1.0e-9);
	merge->Perform();
	const auto merged = merge->Merged();
	{
		const auto& coords = merged->Points();
		std::vector<std::shared_ptr<Entity2d_CmpConnect>> indices;
		for (const auto& i: merged->Connectivity())
		{
			if (i.IsDegenerated())
			{
				std::vector<Standard_Integer> compact;
				compact.emplace_back(i.Value(0));
				push_to_list(i.Value(1), compact);
				push_to_list(i.Value(2), compact);
				push_to_list(i.Value(3), compact);
				if (compact.size() NOT_EQUAL 3)
				{
					FatalErrorIn(FunctionSIG) << endl
						<< "Unknown element has been detected." << endl
						<< abort(FatalError);
				}
				auto t = std::make_shared<Entity2d_CmpConnect_Triangle>
					(Entity2d_CmpConnect_Triangle::Array3{ 
					compact.at(0), compact.at(1), compact.at(2) });
				indices.emplace_back(std::move(t));
			}
			else
			{
				auto t = std::make_shared<Entity2d_CmpConnect_Quad>
					(Entity2d_CmpConnect_Quad::Array4{
					i.Value(0), i.Value(1), i.Value(2), i.Value(3) });
				indices.emplace_back(std::move(t));
			}
		}
		theMesh_ = std::make_shared<Entity2d_CmpMesh>(coords, indices);
	}
}

tnbLib::Dir2d
tnbLib::MeshBLayer2d_Offset2::CalcNormal(const Pnt2d& theP0, const Pnt2d& theP1)
{
	Dir2d u{ theP0, theP1 };
	return u.Rotated(PI_2);
}

Standard_Real
tnbLib::MeshBLayer2d_Offset2::CalcAngle(const Dir2d& theD0, const Dir2d& theD1)
{
	return theD0.Angle(theD1);
}

std::vector<Standard_Real>
tnbLib::MeshBLayer2d_Offset2::UniformDistb(const Standard_Integer n)
{
	std::vector<Standard_Real> parameters;
	parameters.reserve(n + 1);
	if (n < 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid no. of segments has been detected." << endl
			<< abort(FatalError);
	}
	const Standard_Real du = 1.0 / static_cast<Standard_Real>(n);
	for (size_t i = 0; i <= n; i++)
	{
		auto u = i * du;
		parameters.push_back(u);
	}
	return std::move(parameters);
}

std::vector<tnbLib::Pnt2d>
tnbLib::MeshBLayer2d_Offset2::DiscreteSegment(const std::pair<Pnt2d, Pnt2d>& theCoords,
	const std::vector<Standard_Real>& us, const Standard_Real theBeta)
{
	auto [p0, p1] = theCoords;
	const auto du = p1 - p0;
	const auto delta = p0.Distance(p1);
	std::vector<Pnt2d> pts;
	pts.reserve(us.size());
	//std::cout << "p0 = " << p0 << ", p1= " << p1 << std::endl;
	for (const auto u : us)
	{
		auto eta = 1.0 - u;
		if (eta < 0.0) eta = 0.0;
		if (eta > 1.0) eta = 1.0;
		//std::cout << "eta = " << eta << std::endl;
		const auto t = MeshBLayer2d_Offset2::CalcRate(theBeta, eta);
		//std::cout << "u = " << u << ", t = " << t << std::endl;
		auto pt = du * t + p0;
		//std::cout << pt << std::endl;
		pts.emplace_back(std::move(pt));
	}
	return std::move(pts);
}

std::vector<tnbLib::Pnt2d>
tnbLib::MeshBLayer2d_Offset2::Reverse(const std::vector<std::vector<Pnt2d>>& theCoords)
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
	return std::move(reversed);
}

void tnbLib::MeshBLayer2d_Offset2::Perform()
{
	if (NOT thePolygon_)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "no polygon has been found." << endl
			<< abort(FatalError);
	}
	CalculateStrip();
	RetrieveTopoOffset();
	CreateMesh();
	Change_IsDone() = Standard_True;
}

std::shared_ptr<tnbLib::Entity2d_Polygon>
tnbLib::MeshBLayer2d_Offset2::RetrieveOffset() const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "the application is not performed!" << endl
			<< abort(FatalError);
	}
	std::vector<Pnt2d> coords;
	coords.reserve(theOffset_.size());
	for (const auto& x: theOffset_)
	{
		coords.emplace_back(x->coord);
	}
	return std::make_shared<Entity2d_Polygon>(std::move(coords), 0);
}

Standard_Real
tnbLib::MeshBLayer2d_Offset2::CalcRate
(
	const Standard_Real theBeta,
	const Standard_Real theEta
)
{
	const auto cte = (theBeta + 1.0) / (theBeta - 1.0);
	const auto pow = std::pow(cte, theEta);
	return (1.0 - theBeta * (pow - 1.0) / (pow + 1.0));
}

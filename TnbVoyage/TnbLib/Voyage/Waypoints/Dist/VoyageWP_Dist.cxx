#include <VoyageWP_Dist.hxx>

#include <VoyageGeo_Earth.hxx>
#include <Mesh2d_CurveAnIso.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <Pln_CurveTools.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geo_Tools.hxx>

Standard_Integer
tnbLib::VoyageWP_Dist::NbWPs() const
{
	Debug_Null_Pointer(theWaypoints_);
	return theWaypoints_->NbPoints();
}

Standard_Integer
tnbLib::VoyageWP_Dist::MinDistanceId() const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the application is not performed." << endl
			<< abort(FatalError);
	}
	Standard_Integer id = 0;
	Standard_Real minDist = RealLast();
	Standard_Integer i = 0;
	for (const auto x : theDists_)
	{
		//std::cout << "dist = " << x << ", min dis = "<< minDist<< ", id = "<< id << std::endl;
		if (x < minDist)
		{
			minDist = x;
			id = i;
		}
		++id;
	}
	return id;
}

Standard_Real
tnbLib::VoyageWP_Dist::MinDistance() const
{
	return Distance(MinDistanceId());
}

Standard_Real
tnbLib::VoyageWP_Dist::Distance
(
	const Standard_Integer theIndex
) const
{
	if(NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the application is not performed." << endl
			<< abort(FatalError);
	}
	if (NOT INSIDE(theIndex, 0, theDists_.size() - 1))
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid index." << endl
			<< abort(FatalError);
	}
	return theDists_.at(theIndex);
}

Standard_Real
tnbLib::VoyageWP_Dist::DistanceWP
(
	const Standard_Integer theIndex
) const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the application is not performed." << endl
			<< abort(FatalError);
	}
	if (NOT INSIDE(theIndex, 0, theWPdists_.size() - 1))
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid index." << endl
			<< abort(FatalError);
	}
	return theWPdists_.at(theIndex);
}

Standard_Real
tnbLib::VoyageWP_Dist::DistanceWP
(
	const Standard_Integer from,
	const Standard_Integer to
) const
{
	Standard_Real dist = 0;
	if (NOT INSIDE(from, 0, theWPdists_.size() - 1))
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid index." << endl
			<< abort(FatalError);
	}
	if (NOT INSIDE(to - 1, 0, theWPdists_.size() - 1))
	{
		std::cout << "from : " << from << ", to: " << to << ", size : " << theWPdists_.size() << std::endl;
		std::cout << " dist size: " << theDists_.size() << ", wp size: " << theWPdists_.size() << std::endl;
		std::cout << "min id = " << MinDistanceId() << std::endl;
		FatalErrorIn(FunctionSIG)
			<< "invalid index." << endl
			<< " index: " << to - 1 << ", size = " << theWPdists_.size() << endl
			<< abort(FatalError);
	}
	//std::cout << "from : " << from << ", to: " << to << ", size : " << theWPdists_.size() << std::endl;
	forThose(id, from, to - 1)
	{
		//std::cout << "distance id = " << theWPdists_.at(id) << std::endl;
		dist += theWPdists_.at(id);
	}
	return dist;
}

Standard_Integer
tnbLib::VoyageWP_Dist::MaxStarAngle
(
	const Standard_Real theAngle
) const
{
	const auto min_dist_id = MinDistanceId();
	for (Standard_Integer i = 0; i < min_dist_id; i++)
	{
		if (StarAngle(min_dist_id, i) <= theAngle)
		{
			return i;
		}
	}
	return min_dist_id;
}

Standard_Integer
tnbLib::VoyageWP_Dist::MaxPortAngle(const Standard_Real theAngle) const
{
	const auto min_dist_id = MinDistanceId();
	std::cout << std::endl;
	std::cout << " MIN ID = " << min_dist_id << std::endl;
	std::cout << std::endl;
	for (Standard_Integer i = min_dist_id + 1; i < theDists_.size(); i++)
	{
		std::cout << " por id test: " << i << std::endl;
		if (PortAngle(min_dist_id, i) > theAngle)
		{
			std::cout << "YESSS" << std::endl;
			return i - 1;
		}
	}
	return min_dist_id;
}

Standard_Real
tnbLib::VoyageWP_Dist::StarAngle
(
	const Standard_Integer theMinDist, 
	const Standard_Integer theIndex
) const
{
	if (theMinDist < theIndex)
	{
		FatalErrorIn(FunctionSIG)
			<< "the index should be smaller than the minDist index due to the starboard side." << endl
			<< " - the min. dist id: " << theMinDist << endl
			<< " - the index: " << theIndex << endl
			<< abort(FatalError);
	}
	//std::cout << "the min index = " << theMinDist << ", theIndex = " << theIndex << std::endl;
	const auto wp_dist = DistanceWP(theIndex, theMinDist);
	std::cout << "wp_dist: " << wp_dist << std::endl;
	const auto min_dist = Distance(theMinDist);
	std::cout << "min dist = " << min_dist << std::endl;
	const auto id_dist = Distance(theIndex);
	std::cout << "i distance: " << id_dist << std::endl;
	const auto cos_theta = 
		(min_dist * min_dist + id_dist * id_dist - wp_dist * wp_dist) / 
		(2.0 * min_dist * id_dist);
	if (NOT INSIDE(cos_theta, -1.0, 1.0))
	{
		FatalErrorIn(FunctionSIG)
			<< "something went wrong." << endl
			<< " cos_theta = " << cos_theta << endl
			<< abort(FatalError);
	}
	std::cout << std::endl;
	//std::cout << "star angle = " << cos_theta << std::endl;
	std::cout <<"star angle = " << Geo_Tools::RadianToDegree(std::acos(cos_theta)) << std::endl;
	std::cout << std::endl;
	//return cos_theta;
	//PAUSE;
	return std::acos(cos_theta);
}

Standard_Real
tnbLib::VoyageWP_Dist::PortAngle
(
	const Standard_Integer theMinDist,
	const Standard_Integer theIndex
) const
{
	if (theIndex < theMinDist)
	{
		FatalErrorIn(FunctionSIG)
			<< "the index should be bigger than the minDist index due to the port side." << endl
			<< " - the min. dist id: " << theMinDist << endl
			<< " - the index: " << theIndex << endl
			<< abort(FatalError);
	}
	const auto wp_dist = DistanceWP(theMinDist, theIndex);
	std::cout << "wp_dist: " << wp_dist << std::endl;
	const auto min_dist = Distance(theMinDist);
	std::cout << "min dist = " << min_dist << std::endl;
	const auto id_dist = Distance(theIndex);
	std::cout << "i distance: " << id_dist << std::endl;
	const auto cos_theta =
		(min_dist * min_dist + id_dist * id_dist - wp_dist * wp_dist) /
		(2.0 * min_dist * id_dist);
	if (NOT INSIDE(cos_theta, -1.0, 1.0))
	{
		FatalErrorIn(FunctionSIG)
			<< "something went wrong." << endl
			<< abort(FatalError);
	}
	std::cout << std::endl;
	std::cout << "port angle = " << Geo_Tools::RadianToDegree(std::acos(cos_theta)) << std::endl;
	std::cout << std::endl;
	//std::exit(1);
	return std::acos(cos_theta);
}

void tnbLib::VoyageWP_Dist::Perform()
{
	if (NOT Earth())
	{
		FatalErrorIn(FunctionSIG)
			<< "the earth is not loaded." << endl
			<< abort(FatalError);
	}
	const auto& earth = Earth();
	if (NOT WPs())
	{
		FatalErrorIn(FunctionSIG)
			<< "the waypoints are not loaded." << endl
			<< abort(FatalError);
	}
	const auto& wps = WPs();
	auto metrics = earth->GetMetrics();
	Debug_Null_Pointer(metrics);
	auto sizeFun =
		std::make_shared<GeoSizeFun2d_Uniform>
		(1.0, metrics->BoundingBox());
	if (NOT MetricInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric info. has been loaded." << endl
			<< abort(FatalError);
	}
	const auto& metricInfo = MetricInfo();
	auto metricProcsr =
		std::make_shared<Geo2d_MetricPrcsrAnIso>(sizeFun, metrics, metricInfo);
	theWPdists_.reserve(NbWPs() - 1);
	theDists_.reserve(NbWPs());
	const auto& wps_points = wps->Points();
	if (NOT MeshInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh info. has been loaded." << endl
			<< abort(FatalError);
	}
	if (NOT MaxSubLev())
	{
		FatalErrorIn(FunctionSIG)
			<< "no max. sub. lev. has been set." << endl
			<< abort(FatalError);
	}
	for (size_t i = 1; i < NbWPs(); i++)
	{
		const auto& p0 = wps_points.at(i - 1);
		const auto& p1 = wps_points.at(i);
		auto geom = Pln_CurveTools::MakeSegment(p0, p1);
		Debug_Null_Pointer(geom);
		auto alg = std::make_shared<Mesh2d_CurveAnIso>
			(
				geom,
				geom->FirstParameter(), geom->LastParameter(),
				metricProcsr, MeshInfo());
		auto dist = alg->CalcLengthWithChecking(MaxSubLev());
		theWPdists_.push_back(dist);
	}
	for (const auto& x : wps_points)
	{
		auto geom = Pln_CurveTools::MakeSegment(Coord(), x);
		Debug_Null_Pointer(geom);
		auto alg = std::make_shared<Mesh2d_CurveAnIso>
			(
				geom,
				geom->FirstParameter(), geom->LastParameter(),
				metricProcsr, MeshInfo());
		auto dist = alg->CalcLengthWithChecking(MaxSubLev());
		theDists_.push_back(dist);
	}
	Change_IsDone() = Standard_True;
}
#include <Voyage_AdaptPath.hxx>

#include <Voyage_Tools.hxx>
#include <Voyage_AdaptPath_Info.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<tnbLib::Pnt2d>
tnbLib::Voyage_AdaptPath::SubPoints(const Pnt2d& theP0, const Pnt2d& theP1) const
{
	const auto nbSamples = GetInfo()->NbSamples();
	const auto du = 1.0 / (static_cast<Standard_Real>(nbSamples) + 1.0);
	const auto dp = theP1 - theP0;
	std::vector<Pnt2d> coords;
	for (Standard_Integer i = 1; i <= nbSamples; i++)
	{
		auto p = theP0 + i * du * dp;
		coords.emplace_back(std::move(p));
	}
	return std::move(coords);
}

std::pair<tnbLib::Voyage_AdaptPath::SubPath, tnbLib::Voyage_AdaptPath::SubPath> tnbLib::Voyage_AdaptPath::Subdivide(
	const SubPath& thePath0, const SubPath& thePath1) const
{
	const auto nbLevs = GetInfo()->NbLevels();
	const auto crit = static_cast<Standard_Real>(thePath0->NbPoints());
	const auto max_nb_fronts = static_cast<Standard_Integer>((crit - 0.5) / 2.0);
	const auto max_nb_backs = static_cast<Standard_Integer>((crit + 0.5) / 2.0);
	SubPath s0, s1;
	{
		const auto nb_fronts = std::min(max_nb_fronts, nbLevs);
		std::vector<Pnt2d> coords;
		for (Standard_Integer i = 0; i < thePath0->NbPoints() - nb_fronts - 1; i++)
		{
			coords.emplace_back(thePath0->GetPoint(i));
		}
		for (Standard_Integer i = thePath0->NbPoints() - nb_fronts; i < thePath0->NbPoints(); i++)
		{
			const auto& p0 = thePath0->GetPoint(i - 1);
			const auto& p1 = thePath0->GetPoint(i);
			auto subs = SubPoints(p0, p1);
			coords.emplace_back(p0);
			for (auto& x: subs)
			{
				coords.emplace_back(std::move(x));
			}
		}
		coords.emplace_back(thePath0->LastPoint());
		s0 = std::make_shared<Entity2d_Polygon>(std::move(coords), 0);
	}
	{
		const auto nb_backs = std::min(max_nb_backs, nbLevs);
		std::vector<Pnt2d> coords;
		for (Standard_Integer i = 0; i < nb_backs; i++)
		{
			const auto& p0 = thePath1->GetPoint(i);
			const auto& p1 = thePath1->GetPoint(i + 1);
			auto subs = SubPoints(p0, p1);
			coords.emplace_back(p0);
			for (auto& x : subs)
			{
				coords.emplace_back(std::move(x));
			}
		}
		for (Standard_Integer i = nb_backs; i < thePath1->NbPoints(); i++)
		{
			coords.emplace_back(thePath1->GetPoint(i));
		}
		s1 = std::make_shared<Entity2d_Polygon>(std::move(coords), 0);
	}
	auto paired = std::make_pair(std::move(s0), std::move(s1));
	return std::move(paired);
}

tnbLib::Voyage_AdaptPath::SubPath tnbLib::Voyage_AdaptPath::Copy(const SubPath& thePath)
{
	std::vector<Pnt2d> coords;
	for (const auto& x: thePath->Points())
	{
		coords.emplace_back(x);
	}
	return std::make_shared<Entity2d_Polygon>(std::move(coords), 0);
}

std::vector<tnbLib::Voyage_AdaptPath::SubPath>
tnbLib::Voyage_AdaptPath::Copy(const std::vector<SubPath>& thePath)
{
	std::vector<SubPath> path;
	for (const auto& x: thePath)
	{
		path.emplace_back(Copy(x));
	}
	return std::move(path);
}

void tnbLib::Voyage_AdaptPath::Perform()
{
	if (Path().empty())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No path has been loaded." << endl
			<< abort(FatalError);
	}
	if (NOT GetInfo())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No info. has been loaded." << endl
			<< abort(FatalError);
	}
	auto path = Copy(Path());
	for (size_t i = 1; i < path.size(); i++)
	{
		const auto id0 = i - 1;
		const auto id1 = i;
		const auto& sub0 = path.at(id0);
		const auto& sub1 = path.at(id1);
		const auto& p0 = sub0->GetPoint(sub0->NbPoints() - 2);
		const auto& p1 = sub1->GetPoint(0);
		const auto& p2 = sub1->GetPoint(1);
		const auto angle = std::abs(PI - Voyage_Tools::CalcTurningAngle(p0, p1, p2));
		std::cout << "a0 = " << Voyage_Tools::CalcTurningAngle(p0, p1, p2) << std::endl;
		std::cout << "angle = " << angle << ", crit= " << GetInfo()->TargetAngle() << std::endl;
		if (angle > GetInfo()->TargetAngle())
		{
			std::cout << "size 0: " << sub0->NbPoints() << std::endl;
			auto [new_sub0, new_sub1] = 
				Subdivide(sub0, sub1);
			std::cout << "size 1: " << new_sub0->NbPoints() << std::endl;
			path.at(id0) = new_sub0;
			path.at(id1) = new_sub1;
		}
	}
	theRefined_ = std::move(path);
	Change_IsDone() = Standard_True;
}

#include <VoyageGeo_WaypointsDistb.hxx>

#include <VoyageGeo_Tools.hxx>
#include <VoyageGeo_Path.hxx>
#include <Voyage_WptsGrid.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

}

void tnbLib::VoyageGeo_WaypointsDistb::Perform()
{
	if (NOT RefRoute())
	{
		FatalErrorIn(FunctionSIG)
			<< "no reference route has been found." << endl
			<< abort(FatalError);
	}
	const auto& ref = RefRoute();
	if (NOT SizeFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "no size function has been found." << endl
			<< abort(FatalError);
	}
	if (NOT MetricFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric function has been found." << endl
			<< abort(FatalError);
	}
	auto us = ref->Discrete(SizeFun(), MetricFun());
	if (us.size() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid size function has been detected." << endl
			<< abort(FatalError);
	}
	const auto n = (Standard_Integer)us.size();
	std::vector<Standard_Integer> nbSegments;
	nbSegments.resize(n);
	if (n % 2 == 0)
	{
		for (Standard_Integer i = 0; i < n / 2; i++)
		{
			nbSegments.at(i) = std::min(i, MaxDeviation());
		}
		for (Standard_Integer i = n / 2; i < n; i++)
		{
			nbSegments.at(i) = std::min(n - i + 1, MaxDeviation());
		}
	}
	else
	{
		for (Standard_Integer i = 0; i <= n / 2; i++)
		{
			nbSegments.at(i) = std::min(i, MaxDeviation());
		}
		for (Standard_Integer i = n / 2 + 1; i < n; i++)
		{
			nbSegments.at(i) = std::min(n - i + 1, MaxDeviation());
		}
	}
	auto grid = std::make_shared<Voyage_WptsGrid>();
	grid->SetStageSize(n);
	size_t k = 0;
	for (size_t j = 0; j < n; j++)
	{
		auto nj = nbSegments.at(j);
		auto u = us.at(j);

		std::vector<Pnt2d> pts;
		// lower parts [7/11/2023 Payvand]
		auto p0 = ref->Value(u);
		auto normal = ref->CalcNormal(u);
		Vec2d du = -Deviation() * normal;
		for (size_t i = 0; i < nbSegments.at(k); i++)
		{
			auto pt = p0 + i * du;
			pts.push_back(std::move(pt));
		}
		du *= -1;
		for (size_t i = 1; i < nbSegments.at(k); i++)
		{
			auto pt = p0 + i * du;
			pts.push_back(std::move(pt));
		}
		grid->StageRef(k) = std::move(pts);
		++k;
	}
	theGrid_ = std::move(grid);
	Change_IsDone() = Standard_True;
}
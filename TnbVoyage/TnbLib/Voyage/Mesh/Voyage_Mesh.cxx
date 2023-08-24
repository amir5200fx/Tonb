//#include <Voyage_Mesh.hxx>
//
//#include <Voyage_WptsGrid.hxx>
//#include <VoyageGeo_Path.hxx>
//#include <VoyageField_Earth.hxx>
//#include <Entity2d_Polygon.hxx>
//#include <TnbError.hxx>
//#include <OSstream.hxx>
//
//Standard_Boolean 
//tnbLib::Voyage_Mesh::IsValid(const Pnt2d& theCoord) const
//{
//	return Standard_True;
//}
//
//namespace tnbLib
//{
//
//	namespace voyageLib
//	{
//
//		struct StageCoords
//		{
//
//			std::vector<Pnt2d> leftSide;
//			std::vector<Pnt2d> rightSide;
//			Pnt2d stage;
//		};
//
//		static std::vector<Pnt2d> 
//			CalcCoords
//			(
//				const Standard_Integer n,
//				const Vec2d& theNormal, 
//				const Pnt2d& theCoord
//			)
//		{
//			std::vector<Pnt2d> coords;
//			coords.reserve(n);
//			for (Standard_Integer i = 1; i <= n; i++)
//			{
//				auto pt = theCoord + (Standard_Real)i * theNormal;
//				coords.push_back(std::move(pt));
//			}
//			return std::move(coords);
//		}
//	}
//}
//
//void tnbLib::Voyage_Mesh::Perform()
//{
//	if (NOT RefRoute())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "no reference route has been found." << endl
//			<< abort(FatalError);
//	}
//	if (NOT MetricPrcsr())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "no metric function has been found." << endl
//			<< abort(FatalError);
//	}
//	const auto& refPath = RefRoute();
//	auto us = refPath->Discrete(MetricPrcsr(), CurveInfo());
//	if (us.size() < 3)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "invalid size function has been detected." << endl
//			<< abort(FatalError);
//	}
//	const auto n = (Standard_Integer)us.size();
//	
//	std::vector<voyageLib::StageCoords> stages_coords;
//	for (auto u : us)
//	{
//		auto stage = refPath->Value(u);
//		auto left_norm = refPath->CalcNormal(u);
//		Dir2d right_norm = -left_norm;
//
//		auto left_coords = 
//			voyageLib::CalcCoords
//			(MaxDeviation(), Resolution() * left_norm, stage);
//		auto right_coords = 
//			voyageLib::CalcCoords
//			(MaxDeviation(), Resolution() * right_norm, stage);
//
//		std::vector<Pnt2d> left_valids, right_valids;
//		for (auto& x : left_coords)
//		{
//			if (NOT IsValid(x)) break;
//			left_valids.push_back(std::move(x));
//		}
//		for (auto& x : right_coords)
//		{
//			if (NOT IsValid(x)) break;
//			right_valids.push_back(std::move(x));
//		}
//		auto current = 
//			voyageLib::StageCoords
//		{ std::move(left_valids),std::move(right_valids),std::move(stage) };
//		stages_coords.push_back(std::move(current));
//	}
//	size_t k = 0;
//	std::vector<size_t> left_sk, right_sk;
//	left_sk.reserve(n);
//	right_sk.reserve(n);
//	for (size_t i = 0; i < n; i++)
//	{
//		left_sk.at(i) = 
//			std::min(k, stages_coords.at(i).leftSide.size());
//		k = left_sk.at(i);
//		++k;
//	}
//	k = 0;
//	for (size_t i = 0; i < n; i++)
//	{
//		right_sk.at(i) = 
//			std::min(k, stages_coords.at(i).rightSide.size());
//		k = right_sk.at(i);
//		++k;
//	}
//	std::reverse(left_sk.begin(), left_sk.end());
//	std::reverse(right_sk.begin(), right_sk.end());
//	k = 0;
//	for (size_t i = 0; i < n; i++)
//	{
//		left_sk.at(i) = std::min(left_sk.at(i), k);
//		k = left_sk.at(i);
//		++k;
//	}
//	k = 0;
//	for (size_t i = 0; i < n; i++)
//	{
//		right_sk.at(i) = std::min(k, right_sk.at(i));
//		k = right_sk.at(i);
//		++k;
//	}
//	std::reverse(left_sk.begin(), left_sk.end());
//	std::reverse(right_sk.begin(), right_sk.end());
//
//	auto grid = std::make_shared<Voyage_WptsGrid>();
//	grid->SetStageSize(n);
//	for (size_t j = 0; j < n; j++)
//	{
//		const auto& stage = stages_coords.at(j);
//		auto nj = 
//			stage.leftSide.size() + stage.rightSide.size() + 1;
//
//		std::vector<Pnt2d> pts;
//		pts.reserve(nj);
//		for (const auto& x : stage.rightSide)
//		{
//			pts.push_back(x);
//		}
//		pts.push_back(stage.stage);
//		for (const auto& x : stage.leftSide)
//		{
//			pts.push_back(x);
//		}
//		grid->StageRef(j) = std::move(pts);
//	}
//	theGrid_ = std::move(grid);
//	Change_IsDone() = Standard_True;
//}
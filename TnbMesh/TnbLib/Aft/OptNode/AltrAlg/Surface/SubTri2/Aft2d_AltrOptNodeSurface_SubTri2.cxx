#include <Aft2d_AltrOptNodeSurface_SubTri2.hxx>

#include <Aft2d_MetricPrcsrSurface.hxx>
#include <Aft_CorrOptNode_IterativeTools.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Aft_OptNode_Tools.hxx>
#include <Mesh_CurveOptmPoint_BisectCorrection.hxx>
#include <Pln_CurveTools.hxx>
#include <Entity2d_Metric1.hxx>
#include <NumAlg_BisectionSolver.hxx>
#include <NumAlg_BisectionSolver_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

const Standard_Integer tnbLib::Aft2d_AltrOptNodeSurface_SubTri2::DEFAULT_MAX_LEV = 3;
const Standard_Real tnbLib::Aft2d_AltrOptNodeSurface_SubTri2::DEFAULT_TOLERANCE = 0.01;

std::tuple<Standard_Real, Standard_Real, Standard_Boolean>
tnbLib::Aft2d_AltrOptNodeSurface_SubTri2::Iter
(
	const Pnt2d & theCentre, 
	const Pnt2d & theP0, 
	const Pnt2d & theP1, 
	const Standard_Real theH
)
{
	auto p = P0();
	std::cout << "correcting..." << std::endl;
	if (Aft_CorrOptNode_IterativeTools::CorrectOptNode(*MetricMap(), theP0, theP1, theCentre, p, theH, *SizeCorrInfo()))
	{
		std::cout << "correctined0" << std::endl;
		auto d0 = MetricMap()->CalcUnitDistance(theP0, p);
		auto d1 = MetricMap()->CalcUnitDistance(theP1, p);

		auto t = std::make_tuple(d0, d1, Standard_False);
		return std::move(t);
	}
	std::cout << "correctined0" << std::endl;
	auto d0 = MetricMap()->CalcUnitDistance(theP0, p);
	auto d1 = MetricMap()->CalcUnitDistance(theP1, p);

	auto t = std::make_tuple(d0, d1, Standard_True);
	return std::move(t);
}

//void tnbLib::Aft2d_AltrOptNodeSurface_SubTri2::Perform()
//{
//	std::cout << "Altering..." << std::endl;
//	std::cout << std::endl;
//	Debug_Null_Pointer(SizeCorrInfo());
//	Debug_Null_Pointer(BisectInfo());
//	Debug_Null_Pointer(Front());
//	Debug_Null_Pointer(MetricMap());
//	Debug_If_Condition(ElmSize() <= gp::Resolution());
//
//	const auto& centre = Front()->Centre();
//
//	const auto& node0 = Front()->Node0();
//	const auto& node1 = Front()->Node1();
//	Debug_Null_Pointer(node0);
//	Debug_Null_Pointer(node1);
//
//	const auto& v0 = node0->Coord();
//	const auto& v1 = node1->Coord();
//
//	CorrectedRef() = P0();
//	Standard_Real H = 1.0;
//
//	for (auto iter = 1; iter <= MaxLevel(); iter++)
//	{
//		auto denom = std::pow(2.0, (Standard_Real)(iter + 1));
//		auto h = std::sqrt(1.0 / (denom*denom) + 0.75)*H;
//
//		auto t = std::pow(2.0, (Standard_Real)iter);
//		auto V0 = centre + (v0 - centre)*t;
//		auto V1 = centre + (v1 - centre)*t;
//
//		auto[d0, d1, converged] = Iter(centre, V0, V1, h);
//
//		if (std::abs(d0 - d1) / std::max(d0, d1) <= Tolerance())
//		{
//			break;
//		}
//	}
//
//	{
//		static const Standard_Real C = 0.86602540378443864676372317075294;
//		auto[Q0, Q1, cond] = Aft_OptNode_Tools::BisectInitialGuess(*MetricMap(), centre, CorrectedRef(), C, 10);
//		if (NOT cond)
//		{
//			CorrectedRef() = P0();
//			IsConvergedRef() = Standard_False;
//		}
//		else
//		{
//			if (Q0.Distance(Q1) IS_EQUAL 0)
//			{
//				CorrectedRef() = Q0;
//				IsConvergedRef() = Standard_True;
//			}
//			else
//			{
//				std::cout << " bisect correction" << std::endl;
//				auto curve = Pln_CurveTools::MakeSegment(Q0, Q1);
//				Mesh_CurveEntity<Geom2d_Curve, Aft2d_MetricPrcsrSurface> 
//					entity
//					(
//						*curve,
//						*MetricMap(),
//						curve->FirstParameter(),
//						curve->LastParameter()
//					);
//				auto u0 = curve->FirstParameter();
//				Mesh_CurveOptmPoint_BisectCorrection<Geom2d_Curve, Aft2d_MetricPrcsrSurface>
//					correction(u0, u0, curve->LastParameter(), entity, BisectInfo());
//
//				correction.SetLen(C);
//				correction.Perform();
//				std::cout << " bisect correction is done!" << std::endl;
//				std::cout << "hh=" << MetricMap()->CalcUnitDistance(centre, curve->Value(correction.Corrected())) << std::endl;
//				CorrectedRef() = curve->Value(correction.Corrected());
//				IsConvergedRef() = Standard_True;
//			}
//		}
//	}
//	
//	Change_IsDone() = Standard_True;
//}
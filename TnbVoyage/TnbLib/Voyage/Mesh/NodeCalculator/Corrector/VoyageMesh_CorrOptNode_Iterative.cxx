#include <VoyageMesh_CorrOptNode_Iterative.hxx>

#include <VoyageMesh_Edge.hxx>
#include <VoyageMesh_Node.hxx>
#include <VoyageMesh_Traits.hxx>
#include <Aft_CorrOptNode_IterativeTools.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Aft2d_MetricPrcsrSurface.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	Standard_Boolean CorrectOptNode_1
	(
		const Geo2d_MetricPrcsrAnIso& theMap,
		const Pnt2d& theV0, 
		const Pnt2d& theV1, 
		const Pnt2d& theCentre, 
		Pnt2d& theP0,
		const Standard_Real h,
		const Aft_SizeCorr_IterativeInfo& theInfo
	)
	{
		auto P = theP0;

		const auto& map = theMap;
		const auto& info = theInfo;

		const auto& domain = map.BoundingBox();
		if (NOT domain.IsInside(P))
		{
			P = MeshBase_Tools::CorrectCoord(theCentre, P, domain);
		}

		const auto omega = info.UnderRelaxation();
		const auto tol = info.Tolerance();

		Standard_Boolean cond = Standard_True;
		Standard_Integer Iter = 0;

		Debug_If_Condition(h <= gp::Resolution());
		const auto invH = 1.0 / h;
		//std::cout << "h = " << h << ", inv h = " << invH << std::endl;
		//std::cout << "tol = " << tol << std::endl;
		Standard_Real d0, d1;
		do
		{
			//std::cout << "do..." << std::endl;
			d0 = map.CalcUnitDistance(theV0, P) * invH;
			d1 = map.CalcUnitDistance(theV1, P) * invH;
			Debug_If_Condition(d0 <= gp::Resolution());
			Debug_If_Condition(d1 <= gp::Resolution());
			//std::cout << "d0: " << d0 << ", d1: " << d1 << std::endl;
			auto Pa = theV0 + (P - theV0) / d0;
			auto Pb = theV1 + (P - theV1) / d1;

			auto Pn = 0.5 * (Pa + Pb);

			auto dP = Pn - P;

			P += omega * dP;

			if (ABS(1.0 - d0) <= tol AND ABS(1.0 - d1) <= tol)
			{
				cond = Standard_False;
				break;
			}

			if (NOT domain.IsInside(P))
			{
				P = MeshBase_Tools::CorrectCoord(theCentre, P, domain);
			}
		} while (++Iter <= info.MaxNbIters());
		//PAUSE;
		if (NOT domain.IsInside(P))
		{
			P = MeshBase_Tools::CorrectCoord(theCentre, P, domain);
		}

		theP0 = std::move(P);
		return cond;
	}

	auto Correct_1
	(
		const Geo2d_MetricPrcsrAnIso& theMap,
		Pnt2d& theP0, 
		const VoyageMesh_Edge& theEdge,
		const Aft_SizeCorr_IterativeInfo& theInfo
	)
	{
		const auto& edge = theEdge;
		Debug_Null_Pointer(edge.Node0());
		Debug_Null_Pointer(edge.Node1());

		return CorrectOptNode_1
		(
			theMap,
			edge.Node0()->Coord(),
			edge.Node1()->Coord(),
			edge.Centre(), theP0, 0.866, theInfo
		);
	}

	auto Correct_1
	(
		const Geo2d_MetricPrcsrAnIso& theMap,
		const Pnt2d& theP0,
		Pnt2d& theP, 
		const Standard_Real h,
		const Aft_SizeCorr_IterativeInfo& theInfo
	)
	{
		auto P = theP;

		const auto& map = theMap;
		const auto& info = theInfo;

		const auto& domain = map.BoundingBox();
		if (NOT domain.IsInside(P))
		{
			P = MeshBase_Tools::CorrectCoord(theP0, P, domain);
		}

		const auto omega = info.UnderRelaxation();
		const auto tol = info.Tolerance();

		Standard_Boolean cond = Standard_True;
		Standard_Integer Iter = 0;
		do
		{
			auto dis = map.CalcUnitDistance(theP0, P) / h;
			Debug_If_Condition(dis <= gp::Resolution());

			auto pt = theP0 + (P - theP0) / dis;
			auto dp = pt - P;

			P += /*omega **/ dp;

			if (std::abs(1.0 - dis) <= tol)
			{
				cond = Standard_False;
				break;
			}

			if (NOT domain.IsInside(P))
			{
				P = MeshBase_Tools::CorrectCoord(theP0, P, domain);
			}
		} while (++Iter <= info.MaxNbIters());

		if (NOT domain.IsInside(P))
		{
			P = MeshBase_Tools::CorrectCoord(theP0, P, domain);
		}

		theP = std::move(P);
		return cond;
	}
}

template<>
void tnbLib::VoyageMesh_CorrOptNode_Iterative::Perform
(
	const Aft_SizeCorr_IterativeInfo& theInfo
)
{
	Debug_Null_Pointer(MetricMap());
	Debug_Null_Pointer(Front());

	auto P = P0();
	/*auto cond = Aft_CorrOptNode_IterativeTools::template
		Correct<VoyageMesh_Edge, Geo2d_SizeFunction, Geo2d_MetricFunction, Aft_SizeCorr_IterativeInfo>
		(
			*MetricMap(),
			P,
			*Front(), theInfo
		);*/
	auto cond = Correct_1(*MetricMap(), P, *Front(), theInfo);
	if (cond AND NOT theInfo.IgnoreNonConvergency())
	{
		FatalErrorIn(FunctionSIG)
			<< " failed to calculate optimized node" << endl
			<< abort(FatalError);
	}

	if (verbose AND cond)
	{
		Info << " WARNING: failed to calculate optimized node." << endl;
	}

	IsConverged_ = !cond;
	CoordRef() = std::move(P);
	Change_IsDone() = Standard_True;
}
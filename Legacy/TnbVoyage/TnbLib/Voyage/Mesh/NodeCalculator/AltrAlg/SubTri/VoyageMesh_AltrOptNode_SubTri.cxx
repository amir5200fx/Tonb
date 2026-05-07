#include <VoyageMesh_AltrOptNode_SubTri.hxx>

#include <VoyageMesh_AltrOptNode_NelderMeadObj.hxx>
#include <VoyageMesh_MetricPrcsr.hxx>
#include <Aft_CorrOptNode_IterativeTools.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Entity2d_Metric1.hxx>
#include <NumAlg_NelderMead.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Integer tnbLib::VoyageMesh_AltrOptNode_SubTri::DEFAULT_MAX_LEV = 5;

namespace tnbLib
{
	namespace voyageLib
	{

		Standard_Boolean CorrectOptNode(const VoyageMesh_MetricPrcsr& theMap, const Pnt2d& theV0, const Pnt2d& theV1, const Pnt2d& theCentre, Pnt2d& theP0, const Standard_Real h, Aft_SizeCorr_IterativeInfo& theInfo)
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
			Standard_Real d0, d1;
			do
			{
				//std::cout << "do..." << std::endl;
				d0 = map.CalcUnitDistance(theV0, P) * invH;
				d1 = map.CalcUnitDistance(theV1, P) * invH;
				Debug_If_Condition(d0 <= gp::Resolution());
				Debug_If_Condition(d1 <= gp::Resolution());
				std::cout << "d0: " << d0 << ", d1: " << d1 << std::endl;
				auto Pa = theV0 + (P - theV0) / d0;
				auto Pb = theV1 + (P - theV1) / d1;

				auto Pn = 0.5 * (Pa + Pb);

				auto dP = Pn - P;

				P += omega * dP;
				std::cout << "P = " << P << std::endl;
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

			if (NOT domain.IsInside(P))
			{
				P = MeshBase_Tools::CorrectCoord(theCentre, P, domain);
			}
			std::cout << std::endl;
			PAUSE;
			theP0 = std::move(P);
			return cond;
		}
	}
}

Standard_Boolean 
tnbLib::VoyageMesh_AltrOptNode_SubTri::Iter
(
	const Standard_Integer theLev, 
	const Pnt2d& theCentre, 
	const Pnt2d& theP0, 
	const Pnt2d& theP1,
	const Standard_Real theH
)
{
	if (theLev > MaxLevel())
	{
		return Standard_False;
	}

	const auto denom = std::pow(2.0, static_cast<Standard_Real>(theLev + 1));
	const auto V0 = MEAN(theCentre, theP0);
	const auto V1 = MEAN(theCentre, theP1);

	//const auto d0 = 1.0 / (denom*denom);
	const auto h = std::sqrt(1.0 / (denom * denom) + 0.75) * theH;
	std::cout << "INNER H = " << h << ", old = " << theH << std::endl;
	SizeCorrInfo()->SetUnderRelaxation(0.75);
	SizeCorrInfo()->SetMaxNbIters(15);
	auto p0 = P0();
	/*if (
		Aft_CorrOptNode_IterativeTools::CorrectOptNode
		(*MetricMap(), V0, V1, theCentre, p0, h, *SizeCorrInfo())
		)
	{
		return Iter(theLev + 1, theCentre, V0, V1, theH);
	}*/
	if (
		voyageLib::CorrectOptNode
		(*MetricMap(), V0, V1, theCentre, p0, h, *SizeCorrInfo())
		)
	{
		return Iter(theLev + 1, theCentre, V0, V1, theH);
	}
	CorrectedRef() = p0;
	return Standard_True;
}

void tnbLib::VoyageMesh_AltrOptNode_SubTri::Perform()
{
	Debug_Null_Pointer(SizeCorrInfo());
	Debug_Null_Pointer(Front());
	Debug_Null_Pointer(MetricMap());
	Debug_If_Condition(ElmSize() <= gp::Resolution());

	const auto& centre = Front()->Centre();

	const auto& node0 = Front()->Node0();
	const auto& node1 = Front()->Node1();
	Debug_Null_Pointer(node0);
	Debug_Null_Pointer(node1);

	const auto& v0 = node0->Coord();
	const auto& v1 = node1->Coord();

	CorrectedRef() = P0();
	
	{
		IsConvergedRef() = Standard_True;
		Change_IsDone() = Standard_True;
		return;
	}
	std::cout << CorrectedRef() << std::endl;

	if (Iter(1, centre, v0, v1, 1.0))
	{
		IsConvergedRef() = Standard_True;
	}
	else
	{
		NumAlg_NelderMead<VoyageMesh_AltrOptNode_NelderMeadObj> alg;

		alg.SetP0(Front()->Node0()->Coord());
		alg.SetP1(Front()->Node1()->Coord());
		alg.SetP2(CorrectedRef());

		alg.SetInfo(NelderMeadInfo());
		alg.SetMetricMap(MetricMap());
		alg.SetTolerance(NelderMeadInfo()->Tolerance());

		alg.Perform();

		CorrectedRef() = alg.BestVertex();
		std::cout << CorrectedRef() << std::endl;
		std::cout << std::endl;
		IsConvergedRef() = alg.IsConverged();
	}
	Change_IsDone() = Standard_True;
}
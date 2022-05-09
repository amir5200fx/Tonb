#include <Aft2d_AltrOptNodeSurface_MetricCorr.hxx>

#include <Aft2d_OptNodeSurface_Analytical.hxx>
#include <Aft2d_CorrOptNodeSurface_Iterative.hxx>
#include <Aft2d_MetricPrcsrSurface.hxx>
#include <MeshBase_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Integer tnbLib::Aft2d_AltrOptNodeSurface_MetricCorr::DEFAULT_MAX_LEV = 10;

Standard_Boolean
tnbLib::Aft2d_AltrOptNodeSurface_MetricCorr::Iter
(
	const Standard_Integer theLev,
	const Entity2d_Metric1& theM0,
	const Entity2d_Metric1& theM
)
{
	std::cout << "level: " << theLev << std::endl;
	if (theLev > MaxLev())
	{
		return Standard_False;
	}

	const auto& domain = MetricMap()->BoundingBox();

	const auto metric = 0.5*(theM0 + theM);

	const auto& v0 = Front()->Node0()->Coord();
	const auto& v1 = Front()->Node1()->Coord();
	const auto len = MetricMap()->CalcUnitDistance(v0, v1) / 2;

	Aft2d_OptNodeSurface_Analytical optNode(ElmSize(), len, metric, *Front());
	optNode.Perform();
	Debug_If_Condition_Message(NOT optNode.IsDone(), "the application is not performed!");

	CorrectedRef() = optNode.Coord();
	if (NOT domain.IsInside(Corrected()))
	{
		CorrectedRef() = MeshBase_Tools::CorrectCoord(Front()->Centre(), Corrected(), domain);
	}

	Aft2d_CorrOptNodeSurface_Iterative corr(MetricMap(), Front(), Corrected(), ElmSize());
	corr.Perform(*IterInfo());

	if (NOT corr.IsConverged())
	{
		std::cout << "centre: " << Front()->Centre() << std::endl;
		std::cout << "len: " << Front()->Length3D() << ",  " << Front()->CharLength() << std::endl;
		std::cout << "M0: " << theM0.A()<<",  "<< theM0.B()<<",  "<< theM0.C() << std::endl;
		std::cout << "det0: " << theM0.Determinant() << ",  det1: " << MetricMap()->CalcMetric(corr.Coord()).Determinant() << std::endl;
		return Iter(theLev + 1, theM0, MetricMap()->CalcMetric(corr.Coord()));
	}
	return Standard_True;
}

void tnbLib::Aft2d_AltrOptNodeSurface_MetricCorr::Perform()
{
	Debug_Null_Pointer(Front());
	Debug_Null_Pointer(MetricMap());
	Debug_If_Condition(ElmSize() <= gp::Resolution());

	if (Iter
	(
		0,
		MetricMap()->CalcMetric(Front()->Centre()),
		MetricMap()->CalcMetric(P0())
	))
	{
		IsConvergedRef() = Standard_True;
	}
	else
	{
		IsConvergedRef() = Standard_False;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	Change_IsDone() = Standard_True;
}
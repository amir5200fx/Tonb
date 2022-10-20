#include <Aft2d_MetricPrcsrSurfaceUniMetric_RefineH.hxx>

#include <Aft2d_OptNodeSurfaceUniMetric_Calculator.hxx>

Standard_Real tnbLib::Aft2d_MetricPrcsrSurfaceUniMetric_RefineH::DEFAULT_COEFF = 0.3;
Standard_Real tnbLib::Aft2d_MetricPrcsrSurfaceUniMetric_RefineH::DEFAULT_DELTA = 0.2;

Standard_Real
tnbLib::Aft2d_MetricPrcsrSurfaceUniMetric_RefineH::CalcElementSize
(
	const std::shared_ptr<Aft2d_EdgeSurface>& theFront
) const
{
	Debug_Null_Pointer(NodeCalculator());
	const auto h1 = Aft2d_MetricPrcsrSurfaceUniMetric::CalcElementSize(theFront);

	NodeCalculator()->SetFront(theFront);
	NodeCalculator()->SetSize(h1);

	NodeCalculator()->Perform();
	Debug_If_Condition_Message(NOT NodeCalculator()->IsDone(), "the node calculator is not performed!");

	InitCoordCache = NodeCalculator()->Coord();
	
	const auto h2 = Aft2d_MetricPrcsrSurfaceUniMetric::CalcElementSize(InitCoordCache);

	if (h2 >= h1)
	{	
		return h2;
	}
	else
	{
		Debug_If_Condition(std::abs(h1) <= gp::Resolution());
		const auto frac = (h1 - h2) / h1;
		if (frac <= Delta())
		{
			return h1;
		}
		else
		{
			return Coeff()*h1 + (1.0 - Coeff())*h2;
		}
	}
}

void tnbLib::Aft2d_MetricPrcsrSurfaceUniMetric_RefineH::SetInfo(const std::shared_ptr<info>& theInfo)
{
	this->OverrideInfo(theInfo);
	this->OverrideBaseInfo(theInfo);
}

void tnbLib::Aft2d_MetricPrcsrSurfaceUniMetric_RefineH::SetSizeFun(const std::shared_ptr<Geo2d_SizeFunction>& theFun)
{
	this->OverrideSizeFunction(theFun);
}

void tnbLib::Aft2d_MetricPrcsrSurfaceUniMetric_RefineH::SetMetricFun(const std::shared_ptr<GeoMetricFun2d_Uniform>& theFun)
{
	this->OverrideMetricFunction(theFun);
}
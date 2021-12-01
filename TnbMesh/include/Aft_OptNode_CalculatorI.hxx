#pragma once
template<class FrontType, class SizeFun, class MetricFun>
inline void tnbLib::Aft_OptNode_Calculator<FrontType, SizeFun, MetricFun>::SetFront
(
	const std::shared_ptr<frontType>& theFront
)
{
	theFront_ = theFront;
	if (IsDone())
	{
		Change_IsDone() = Standard_False;
	}
}

template<class FrontType, class SizeFun, class MetricFun>
inline void tnbLib::Aft_OptNode_Calculator<FrontType, SizeFun, MetricFun>::SetMetricMap
(
	const std::shared_ptr<metricMap>& theMetricMap
)
{
	theMetricMap_ = theMetricMap;
	if (IsDone())
	{
		Change_IsDone() = Standard_False;
	}
}

template<class FrontType, class SizeFun, class MetricFun>
inline void tnbLib::Aft_OptNode_Calculator<FrontType, SizeFun, MetricFun>::SetSize
(
	const Standard_Real theSize
)
{
	theSize_ = theSize;
	if (IsDone())
	{
		Change_IsDone() = Standard_False;
	}
}
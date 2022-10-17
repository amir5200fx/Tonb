#pragma once
#ifndef _Aft2d_MetricPrcsrSurfaceUniMetric_RefineH_Header
#define _Aft2d_MetricPrcsrSurfaceUniMetric_RefineH_Header

#include <Aft2d_MetricPrcsrSurfaceUniMetric.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_CalculatorFwd.hxx>

namespace tnbLib
{

	struct Aft2d_MetricPrcsrSurfaceUniMetric_RefineH_Cache
	{

		mutable Pnt2d InitCoordCache;

	protected:

		// default constructor [10/17/2022 Amir]

		Aft2d_MetricPrcsrSurfaceUniMetric_RefineH_Cache()
			: InitCoordCache(Pnt2d::null)
		{}

	};

	class Aft2d_MetricPrcsrSurfaceUniMetric_RefineH
		: public Aft2d_MetricPrcsrSurfaceUniMetric
		, public Aft2d_MetricPrcsrSurfaceUniMetric_RefineH_Cache
	{

		/*Private Data*/

		std::shared_ptr<Aft2d_OptNodeSurfaceUniMetric_Calculator> theNodeCalculator_;

		Standard_Real theCoeff_;
		Standard_Real theDelta_;


		// private functions and operators [10/17/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:



	public:

		static TnbMesh_EXPORT Standard_Real DEFAULT_COEFF;
		static TnbMesh_EXPORT Standard_Real DEFAULT_DELTA;

		using Aft2d_MetricPrcsrSurfaceUniMetric::info;

		// default constructor [10/17/2022 Amir]

		Aft2d_MetricPrcsrSurfaceUniMetric_RefineH()
			: theCoeff_(DEFAULT_COEFF)
			, theDelta_(DEFAULT_DELTA)
		{}

		const auto& NodeCalculator() const
		{
			return theNodeCalculator_;
		}

		auto Delta() const
		{
			return theDelta_;
		}

		auto Coeff() const
		{
			return theCoeff_;
		}

		Standard_Boolean CanProvideInitCoord() const override
		{
			return Standard_True;
		}

		Pnt2d InitCoord() const override
		{
			return InitCoordCache;
		}

		TnbMesh_EXPORT Standard_Real
			CalcElementSize
			(
				const std::shared_ptr<Aft2d_EdgeSurface>&
			) const override;

		TnbMesh_EXPORT void SetInfo(const std::shared_ptr<info>& theInfo);
		TnbMesh_EXPORT void SetSizeFun(const std::shared_ptr<Geo2d_SizeFunction>& theFun);
		TnbMesh_EXPORT void SetMetricFun(const std::shared_ptr<GeoMetricFun2d_Uniform>& theFun);

		void SetNodeCalculator(const std::shared_ptr<Aft2d_OptNodeSurfaceUniMetric_Calculator>& theCalculator)
		{
			theNodeCalculator_ = theCalculator;
		}

		// the linear interpolation value which is between 0 and 1 [10/17/2022 Amir]
		void SetCoeff(const Standard_Real theValue)
		{
			theCoeff_ = theValue;
		}

		// the max. percentage of element size deviation. the value is between 0 and 1 [10/17/2022 Amir]
		void SetDelta(const Standard_Real theValue)
		{
			theDelta_ = theValue;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_MetricPrcsrSurfaceUniMetric_RefineH);

#endif // !_Aft2d_MetricPrcsrSurfaceUniMetric_RefineH_Header

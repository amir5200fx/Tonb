#pragma once
#ifndef _Aft2d_AltrOptNodeSurface_Header
#define _Aft2d_AltrOptNodeSurface_Header

#include <Aft_AltrOptNode.hxx>
#include <Aft2d_AltrOptNodeSurfaceFwd.hxx>
#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Aft2d_MetricPrcsrSurfaceFwd.hxx>
#include <Aft2d_OptNodeSurface_AltrFwd.hxx>
#include <Entity2d_Metric1.hxx>
#include <Global_Done.hxx>

namespace tnbLib
{

	template<>
	class Aft_AltrOptNode<Aft2d_EdgeSurface, Geo2d_SizeFunction, Geo2d_MetricFunction>
		: public Global_Done
	{

		friend typename Aft2d_OptNodeSurface_Altr;

		/*Private Data*/

		std::shared_ptr<Aft2d_EdgeSurface> theFront_;

		std::shared_ptr<Aft2d_MetricPrcsrSurface> theMetricMap_;
		
		Pnt2d theP0_;
		Standard_Real theSize_;


		// results [5/7/2022 Amir]

		Pnt2d theCorrected_;

		Standard_Boolean IsConverged_;

	protected:

		// default constructor [5/7/2022 Amir]

		Aft_AltrOptNode()
			: IsConverged_(Standard_False)
		{}


		// constructors [5/7/2022 Amir]


		// protected functions and operators [5/7/2022 Amir]

		auto& IsConvergedRef()
		{
			return IsConverged_;
		}

		auto& CorrectedRef()
		{
			return theCorrected_;
		}

		void SetFront(const std::shared_ptr<Aft2d_EdgeSurface>& theFront)
		{
			theFront_ = theFront;
		}

		void SetMetricMap(const std::shared_ptr<Aft2d_MetricPrcsrSurface>& theMap)
		{
			theMetricMap_ = theMap;
		}

		void SetElmSize(const Standard_Real h)
		{
			theSize_ = h;
		}

		void SetP0(const Pnt2d& theCoord)
		{
			theP0_ = theCoord;
		}

		void SetP0(Pnt2d&& theCoord)
		{
			theP0_ = std::move(theCoord);
		}

	public:

		// public functions and operators [5/7/2022 Amir]

		const auto& Front() const
		{
			return theFront_;
		}

		const auto& MetricMap() const
		{
			return theMetricMap_;
		}

		const auto& P0() const
		{
			return theP0_;
		}

		const auto& Corrected() const
		{
			return theCorrected_;
		}

		auto ElmSize() const
		{
			return theSize_;
		}

		auto IsConverged() const
		{
			return IsConverged_;
		}

		virtual void Perform() = 0;

		
	};
}

#endif // !_Aft2d_AltrOptNodeSurface_Header

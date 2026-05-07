#pragma once
#ifndef _VoyageMesh_AltrOptNode_Header
#define _VoyageMesh_AltrOptNode_Header

#include <VoyageMesh_AltrOptNodeFwd.hxx>
#include <VoyageMesh_MetricPrcsrFwd.hxx>
#include <VoyageMesh_OptNode_AltrFwd.hxx>
#include <Aft_AltrOptNode.hxx>
#include <Entity2d_Metric1.hxx>
#include <Global_Done.hxx>

namespace tnbLib
{

	// Forward Declarations [8/23/2023 aamir]
	class VoyageMesh_Edge;

	template<>
	class Aft_AltrOptNode<VoyageMesh_Edge, Geo2d_SizeFunction, Geo2d_MetricFunction>
		: public Global_Done
	{

		friend typename VoyageMesh_OptNode_Altr;

		/*Private Data*/

		std::shared_ptr<VoyageMesh_Edge> theFront_;

		std::shared_ptr<VoyageMesh_MetricPrcsr> theMetricMap_;

		Pnt2d theP0_;
		Standard_Real theSize_;


		// results [5/7/2022 Amir]

		Pnt2d theCorrected_;

		Standard_Boolean IsConverged_;


		// Private functions and operators [3/11/2023 Payvand]


	protected:


		// default constructor [5/7/2022 Amir]

		Aft_AltrOptNode()
			: IsConverged_(Standard_False)
			, theP0_(Pnt2d::null)
			, theSize_(0)
			, theCorrected_(Pnt2d::null)
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

		void SetFront(const std::shared_ptr<VoyageMesh_Edge>& theFront)
		{
			theFront_ = theFront;
		}

		void SetMetricMap(const std::shared_ptr<VoyageMesh_MetricPrcsr>& theMap)
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

#endif // !_VoyageMesh_AltrOptNode_Header

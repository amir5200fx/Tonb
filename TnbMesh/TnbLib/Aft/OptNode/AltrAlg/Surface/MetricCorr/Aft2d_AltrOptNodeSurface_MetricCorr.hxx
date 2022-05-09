#pragma once
#ifndef _Aft2d_AltrOptNodeSurface_MetricCorr_Header
#define _Aft2d_AltrOptNodeSurface_MetricCorr_Header

#include <Aft2d_AltrOptNodeSurface.hxx>

namespace tnbLib
{

	// Forward Declarations [5/7/2022 Amir]
	class Aft_SizeCorr_IterativeInfo;

	class Aft2d_AltrOptNodeSurface_MetricCorr
		: public Aft2d_AltrOptNodeSurface
	{

		/*Private Data*/

		Standard_Integer theMaxLev_;

		std::shared_ptr<Aft_SizeCorr_IterativeInfo> theInfo_;

		// private functions and operators [5/7/2022 Amir]

		TnbMesh_EXPORT Standard_Boolean
			Iter
			(
				const Standard_Integer theLev,
				const Entity2d_Metric1& theM0,
				const Entity2d_Metric1&
			);

	public:

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_LEV;

		// default constructor [5/7/2022 Amir]

		Aft2d_AltrOptNodeSurface_MetricCorr()
			: theMaxLev_(DEFAULT_MAX_LEV)
		{}


		// constructors [5/7/2022 Amir]


		// public functions and operators [5/7/2022 Amir]

		auto MaxLev() const
		{
			return theMaxLev_;
		}

		const auto& IterInfo() const
		{
			return theInfo_;
		}

		TnbMesh_EXPORT void Perform() override;

		void SetIterInfo(const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void SetMaxLev(const Standard_Integer theMax)
		{
			theMaxLev_ = theMax;
		}
	};
}

#endif // !_Aft2d_AltrOptNodeSurface_MetricCorr_Header

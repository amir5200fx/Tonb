#pragma once
#ifndef _Cad_CommonSingularity_Header
#define _Cad_CommonSingularity_Header

#include <Cad_SingularityTraits.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [6/9/2022 Amir]
	class NumAlg_AdaptiveInteg_Info;

	template<class SurfType>
	class Cad_CommonSingularity
		: public Global_Done
	{

	public:

		typedef typename cad_singularity_traits<SurfType>::plnType plnType;
		typedef typename cad_singularity_traits<SurfType>::parCurveType parCurveType;

	private:

		/*Private Data*/

		std::shared_ptr<SurfType> theSurface_;
		std::shared_ptr<plnType> thePlane_;

		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theInfo_;

		Standard_Real theTolerance_;

		// results [6/9/2022 Amir]

		std::shared_ptr<plnType> theModified_;


		auto& ModifiedRef()
		{
			return theModified_;
		}

	public:

		// default constructor [6/9/2022 Amir]

		Cad_CommonSingularity()
		{}

		// constructors [6/9/2022 Amir]


		// public functions and operators [6/9/2022 Amir]

		const auto& Plane() const
		{
			return thePlane_;
		}

		const auto& Surface() const
		{
			return theSurface_;
		}

		const auto& Modified() const
		{
			return theModified_;
		}

		const auto& IntegInfo() const
		{
			return theInfo_;
		}

		auto Tolerance() const
		{
			return theTolerance_;
		}

		void Perform();

		void SetSurface(const std::shared_ptr<SurfType>& theSurface)
		{
			theSurface_ = theSurface;
		}

		void SetPlane(const std::shared_ptr<plnType>& thePlane)
		{
			thePlane_ = thePlane;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

		void SetInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}
	};
}

#endif // !_Cad_CommonSingularity_Header

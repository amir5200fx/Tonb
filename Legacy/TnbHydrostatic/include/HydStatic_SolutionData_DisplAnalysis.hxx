#pragma once
#ifndef _HydStatic_SolutionData_DisplAnalysis_Header
#define _HydStatic_SolutionData_DisplAnalysis_Header

#include <Marine_ModelsFwd.hxx>
#include <Marine_VesselParam_DISPV.hxx>
#include <HydStatic_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	namespace hydStcLib
	{

		class SolutionData_DisplAnalysis
		{

			/*Private Data*/

			std::shared_ptr<marineLib::Model_Hull> theHull_;

			marineLib::DISPV theDispv_;

			// private functions and operators [9/21/2022 Amir]

			TNB_SERIALIZATION(TnbHydStatic_EXPORT);

		public:

			// default constructor [9/21/2022 Amir]

			SolutionData_DisplAnalysis()
			{}

			// constructors [9/21/2022 Amir]


			// public functions and operators [9/21/2022 Amir]

			const auto& Hull() const
			{
				return theHull_;
			}

			const auto& DISPV() const
			{
				return theDispv_;
			}

			void SetHull(const std::shared_ptr<marineLib::Model_Hull>& theHull)
			{
				theHull_ = theHull;
			}

			void SetHull(std::shared_ptr<marineLib::Model_Hull>&& theHull)
			{
				theHull_ = std::move(theHull);
			}

			void SetDispv(const marineLib::DISPV& theV)
			{
				theDispv_ = theV;
			}

			void SetDispv(marineLib::DISPV&& theV)
			{
				theDispv_ = std::move(theV);
			}
		};
	}
}

#endif // !_HydStatic_SolutionData_DisplAnalysis_Header

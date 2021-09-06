#pragma once
#ifndef _HydStatic_SolutionData_Bonjean2_Header
#define _HydStatic_SolutionData_Bonjean2_Header

#include <Global_Serialization.hxx>
#include <Marine_BodiesFwd.hxx>
#include <HydStatic_Module.hxx>
#include <HydStatic_Bonjean2.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Domain;
	class HydStatic_Bonjean2;

	namespace hydStcLib
	{

		class SolutionData_Bonjean2
		{

			/*Private Data*/

			std::shared_ptr<marineLib::Body_Displacer> theBody_;
			std::shared_ptr<Marine_Domain> theDomain_;

			std::vector<std::shared_ptr<HydStatic_Bonjean2::bonjeanEntity>> theSections_;

			//- private functions and operators

			TNB_SERIALIZATION(TnbHydStatic_EXPORT);

		public:


			//- default constructor

			SolutionData_Bonjean2()
			{}


			//- constructors



			//- public functions and operators

			const auto& Body() const
			{
				return theBody_;
			}

			const auto& Domain() const
			{
				return theDomain_;
			}

			const auto& Sections() const
			{
				return theSections_;
			}

			void SetDomain(const std::shared_ptr<Marine_Domain>& theDomain)
			{
				theDomain_ = theDomain;
			}

			void SetBody(const std::shared_ptr<marineLib::Body_Displacer>& theBody)
			{
				theBody_ = theBody;
			}

			void SetSections(const std::vector<std::shared_ptr<HydStatic_Bonjean2::bonjeanEntity>>& theSections)
			{
				theSections_ = theSections;
			}

			void SetSections(std::vector<std::shared_ptr<HydStatic_Bonjean2::bonjeanEntity>>&& theSections)
			{
				theSections_ = std::move(theSections);
			}
		};
	}
}

#endif // !_HydStatic_SolutionData_Bonjean2_Header

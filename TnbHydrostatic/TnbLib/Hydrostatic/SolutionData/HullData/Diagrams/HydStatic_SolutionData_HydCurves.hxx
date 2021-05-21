#pragma once
#ifndef _HydStatic_SolutionData_HydCurves_Header
#define _HydStatic_SolutionData_HydCurves_Header

#include <Global_Serialization.hxx>
#include <HydStatic_Module.hxx>
#include <Marine_BodiesFwd.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_HydCurves;
	class Marine_Domain;

	namespace hydStcLib
	{

		class SolutionData_HydCurves
		{

			/*Private Data*/

			std::shared_ptr<marineLib::Body_Displacer> theBody_;
			std::shared_ptr<Marine_Domain> theDomain_;


			std::shared_ptr<HydStatic_HydCurves> theCurves_;


			//- private functions and operators

			TNB_SERIALIZATION(TnbHydStatic_EXPORT);

		public:

			//- default constructor

			SolutionData_HydCurves()
			{}


			//- constructors

			explicit SolutionData_HydCurves
			(
				const std::shared_ptr<marineLib::Body_Displacer>& theBody
			)
				: theBody_(theBody)
			{}

			//- public functions and operators

			const auto& Body() const
			{
				return theBody_;
			}

			const auto& Domain() const
			{
				return theDomain_;
			}

			const auto& Curves() const
			{
				return theCurves_;
			}

			void LoadBody(const std::shared_ptr<marineLib::Body_Displacer>& theBody)
			{
				theBody_ = theBody;
			}

			void LoadDomain(const std::shared_ptr<Marine_Domain>& theDomain)
			{
				theDomain_ = theDomain;
			}

			void SetCurves(const std::shared_ptr<HydStatic_HydCurves>& theCurves)
			{
				theCurves_ = theCurves;
			}
		};
	}
}

#endif // !_HydStatic_SolutionData_HydCurves_Header

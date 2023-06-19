#pragma once
#ifndef _HydStatic_SolutionData_GZ_Header
#define _HydStatic_SolutionData_GZ_Header

#include <Global_Serialization.hxx>
#include <Marine_BodiesFwd.hxx>
#include <HydStatic_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Domain;
	class HydStatic_rArmCurve;
	class HydStatic_CrsCurvesGraph;

	namespace hydStcLib
	{

		class SolutionData_GZ
		{

			/*Private Data*/
			std::shared_ptr<marineLib::Body_Displacer> theBody_;
			std::shared_ptr<Marine_Domain> theDomain_;


			std::shared_ptr<HydStatic_CrsCurvesGraph> theCrossCurves_;
			std::shared_ptr<HydStatic_rArmCurve> theGz_;


			//- private functions and operators

			TNB_SERIALIZATION(TnbHydStatic_EXPORT);

		public:

			//- default constructor

			SolutionData_GZ()
			{}


			//- constructors

			explicit SolutionData_GZ
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

			const auto& CrossCurves() const
			{
				return theCrossCurves_;
			}

			const auto& GZ() const
			{
				return theGz_;
			}

			void LoadBody(const std::shared_ptr<marineLib::Body_Displacer>& theBody)
			{
				theBody_ = theBody;
			}

			void LoadDomain(const std::shared_ptr<Marine_Domain>& theDomain)
			{
				theDomain_ = theDomain;
			}

			void SetCrossCurves(const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCurves)
			{
				theCrossCurves_ = theCurves;
			}

			void SetGZ(const std::shared_ptr<HydStatic_rArmCurve>& theGZ)
			{
				theGz_ = theGZ;
			}

		}; 
	}
}

#endif // !_HydStatic_SolutionData_GZ_Header

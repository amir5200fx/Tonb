#pragma once
#ifndef _HydStatic_SolutionData_GzEff_Header
#define _HydStatic_SolutionData_GzEff_Header

#include <Global_Done.hxx>
#include <Global_Serialization.hxx>
#include <Marine_VesselParam_DISPV.hxx>
#include <HydStatic_rArmCurve_EffFwd.hxx>
#include <HydStatic_FormCoeffFwd.hxx>
#include <HydStatic_FormDimsFwd.hxx>
#include <HydStatic_Module.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_HullShape;
	class HydStatic_TankShape;
	class HydStatic_SailShape;
	class HydStatic_Model;

	class StbGMaker_Model;

	namespace hydStcLib
	{

		class SolutionData_GzEff
			: public Global_Done
		{

		public:

			typedef std::map
				<
				Standard_Integer,
				std::shared_ptr<HydStatic_TankShape>
				>
				tankMap;

			enum class analysisCode
			{
				importModel,
				dispv,
				gzEff
			};

		private:

			/*Private Data*/

			std::shared_ptr<StbGMaker_Model> theModel_;

			marineLib::DISPV theDispv_;

			std::shared_ptr<HydStatic_HullShape> theHull_;
			std::map<Standard_Integer, std::shared_ptr<HydStatic_TankShape>> theTanks_;


			std::shared_ptr<hydStcLib::rArmCurve_Eff> theGzEff_;

			analysisCode theCode_;

			//- private functions and operators

			TNB_SERIALIZATION(TnbHydStatic_EXPORT);


		public:

			//- default constructor

			SolutionData_GzEff()
			{}


			//- public functions and operators

			const auto& DISPV() const
			{
				return theDispv_;
			}

			const auto& Hull() const
			{
				return theHull_;
			}

			const auto& Tanks() const
			{
				return theTanks_;
			}

			const auto& Model() const
			{
				return theModel_;
			}

			const auto& GzEff() const
			{
				return theGzEff_;
			}

			auto CurrentAnalysis() const
			{
				return theCode_;
			}

			TnbHydStatic_EXPORT Standard_Boolean IsUpdated(const analysisCode code);

			TnbHydStatic_EXPORT tankMap::const_iterator SelectTank(const Standard_Integer theIndex) const;
			TnbHydStatic_EXPORT tankMap::iterator ImportTank(const std::shared_ptr<HydStatic_TankShape>& theTank);

			TnbHydStatic_EXPORT void RemoveTank(const Standard_Integer theIndex);
			TnbHydStatic_EXPORT void RemoveTank(const tankMap::const_iterator& iter);

			TnbHydStatic_EXPORT void SetGzEff(const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theGz);
			TnbHydStatic_EXPORT void SetGzEff(std::shared_ptr<hydStcLib::rArmCurve_Eff>&& theGz);

			TnbHydStatic_EXPORT void Import(const std::shared_ptr<StbGMaker_Model>& theModel);

			void SetCurrentAnalysis(const analysisCode code)
			{
				theCode_ = code;
			}
		};
	}
}

#endif // !_HydStatic_SolutionData_GzEff_Header

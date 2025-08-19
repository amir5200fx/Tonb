#pragma once
#ifndef _ISC08_SolutionData_Passenger_Header
#define _ISC08_SolutionData_Passenger_Header

#include <Global_Done.hxx>
#include <Global_Serialization.hxx>
#include <HydStatic_FormDimsFwd.hxx>
#include <HydStatic_FormCoeffFwd.hxx>
#include <HydStatic_ShapesFwd.hxx>
#include <HydStatic_rArmCurve_EffFwd.hxx>
#include <ISC08_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class StbGMaker_Model;
	class Marine_Wave;
	class Marine_Water;
	class HydStatic_FloatBody;
	class HydStatic_ModelShape;

	namespace isc08Lib
	{

		class SolutionData_Passenger
		{

		public:

			typedef std::map
				<
				Standard_Integer,
				std::shared_ptr<HydStatic_TankShape>
				>
				tankMap;

			enum class solutionOrder
			{
				model,
				displacerDim,
				wave,
				floatBody,			
				wettedDim,
				coeff,		
				gzEff,
				isc08Model
			};

		private:

			/*private Data*/

			std::shared_ptr<HydStatic_ModelShape> theModel_;
			std::shared_ptr<Marine_Wave> theWave_;

			//- analyses
			std::shared_ptr<formDim::Displacer> theDisplacerAnalysis_;
			std::shared_ptr<formDim::Wetted> theWettedAnalysis_;

			std::shared_ptr<Marine_Water> theWater_;
			std::shared_ptr<HydStatic_FloatBody> theFloatBody_;

			std::shared_ptr<formCoeff::Wetted> theCoeffAnalysis_;

			//- GZ effective

			std::shared_ptr<HydStatic_HullShape> theHull_;
			std::map<Standard_Integer, std::shared_ptr<HydStatic_TankShape>> theTanks_;

			std::shared_ptr<hydStcLib::rArmCurve_Eff> theGzEff_;


			//- current solution

			solutionOrder theCurrent_;

			//- private functions and operators

			TNB_SERIALIZATION(TnbISC08_EXPORT);

		public:


			//- default constructor

			SolutionData_Passenger()
			{}


			//- constructors


			//- public functions and operators

			const auto& Model() const
			{
				return theModel_;
			}

			const auto& Wave() const
			{
				return theWave_;
			}

			TnbISC08_EXPORT Standard_Boolean IsUpdated(const solutionOrder theSolution) const;


			void LoadModel(const std::shared_ptr<HydStatic_ModelShape>& theModel)
			{
				theModel_ = theModel;
			}

			void LoadWave(const std::shared_ptr<Marine_Wave>& theWave)
			{
				theWave_ = theWave;
			}

			auto CurrentSolution() const
			{
				return theCurrent_;
			}

			void SetCurrentSolution(const solutionOrder theSolution)
			{
				theCurrent_ = theSolution;
			}

			//- analyses

			const auto& DisplacerAnalysis() const
			{
				return theDisplacerAnalysis_;
			}

			const auto& WettedAnalysis() const
			{
				return theWettedAnalysis_;
			}

			const auto& Water() const
			{
				return theWater_;
			}

			const auto& FloatBody() const
			{
				return theFloatBody_;
			}

			const auto& CoeffAnalysis() const
			{
				return theCoeffAnalysis_;
			}

			const auto& Hull() const
			{
				return theHull_;
			}

			const auto& Tanks() const
			{
				return theTanks_;
			}

			const auto& GzEff() const
			{
				return theGzEff_;
			}

			void SetDisplacerAnalysis(const std::shared_ptr<formDim::Displacer>& theAnalysis)
			{
				theDisplacerAnalysis_ = theAnalysis;
			}

			void SetWettedAnalysis(const std::shared_ptr<formDim::Wetted>& theAnalysis)
			{
				theWettedAnalysis_ = theAnalysis;
			}

			void SetWater(const std::shared_ptr<Marine_Water>& theWater)
			{
				theWater_ = theWater;
			}

			void SetFloatBody(const std::shared_ptr<HydStatic_FloatBody>& theBody)
			{
				theFloatBody_ = theBody;
			}

			void SetCoeffAnalysis(const std::shared_ptr<formCoeff::Wetted>& theAnalysis)
			{
				theCoeffAnalysis_ = theAnalysis;
			}

			void SetHull(const std::shared_ptr<HydStatic_HullShape>& theHull)
			{
				theHull_ = theHull;
			}

			void SetGzEff(const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theGz)
			{
				theGzEff_ = theGz;
			}
		};
	}
	
}

#endif // !_ISC08_SolutionData_Passenger_Header

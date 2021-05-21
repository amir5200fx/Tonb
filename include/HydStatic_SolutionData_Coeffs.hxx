#pragma once
#ifndef _HydStatic_SolutionData_Coeffs_Header
#define _HydStatic_SolutionData_Coeffs_Header

#include <Global_Done.hxx>
#include <Global_Serialization.hxx>
#include <HydStatic_FormDimsFwd.hxx>
#include <HydStatic_FormCoeffFwd.hxx>
#include <HydStatic_Module.hxx>
#include <Marine_BodiesFwd.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class StbGMaker_Model;
	class Marine_Wave;
	class Marine_Water;
	class Marine_Domain;
	class HydStatic_FloatBody;
	class HydStatic_ModelShape;

	namespace hydStcLib
	{

		class SolutionData_Coeffs
		{

		public:

			enum class solutionOrder
			{
				model,
				displacerDim,
				wave,
				floatBody,
				wettedDim,
				coeff
			};

		private:

			/*Private Data*/

			std::shared_ptr<marineLib::Body_Displacer> theHull_;
			std::shared_ptr<Marine_Domain> theDomain_;
			std::shared_ptr<Marine_Wave> theWave_;

			//- analyses
			std::shared_ptr<formDim::Displacer> theDisplacerAnalysis_;
			std::shared_ptr<formDim::Wetted> theWettedAnalysis_;

			std::shared_ptr<Marine_Water> theWater_;
			std::shared_ptr<HydStatic_FloatBody> theFloatBody_;

			std::shared_ptr<formCoeff::Wetted> theCoeffAnalysis_;


			//- current solution

			solutionOrder theCurrent_;


			//- private functions and operators

			TNB_SERIALIZATION(TnbHydStatic_EXPORT);


		public:

			//- default constructor

			SolutionData_Coeffs()
			{}


			//- constructors

			explicit SolutionData_Coeffs
			(
				const std::shared_ptr<marineLib::Body_Displacer>& theHull
			)
				: theHull_(theHull)
			{}


			//- public functions and operators

			TnbHydStatic_EXPORT Standard_Boolean 
				IsUpdated
				(
					const solutionOrder theSolution
				) const;

			const auto& Hull() const
			{
				return theHull_;
			}

			const auto& Domain() const
			{
				return theDomain_;
			}

			const auto& Wave() const
			{
				return theWave_;
			}

			auto CurrentSolution() const
			{
				return theCurrent_;
			}

			void SetCurrentSolution(const solutionOrder theSolution)
			{
				theCurrent_ = theSolution;
			}

			void LoadHull(const std::shared_ptr<marineLib::Body_Displacer>& theBody)
			{
				theHull_ = theBody;
			}

			void LoadDomain(const std::shared_ptr<Marine_Domain>& theDomain)
			{
				theDomain_ = theDomain;
			}

			void LoadWave(const std::shared_ptr<Marine_Wave>& theWave)
			{
				theWave_ = theWave;
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

		};
	}
}

#endif // !_HydStatic_SolutionData_Coeffs_Header

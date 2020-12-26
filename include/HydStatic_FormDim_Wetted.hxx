#pragma once
#ifndef _HydStatic_FormDim_Wetted_Header
#define _HydStatic_FormDim_Wetted_Header

#include <Marine_VesselParams.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Global_Done.hxx>
#include <Global_Serialization.hxx>
#include <HydStatic_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Wave;

	namespace formDim
	{

		class Wetted
			: public Global_Done
		{

		public:

			static TnbHydStatic_EXPORT unsigned short verbose;

			enum class appMode
			{
				Auto = 0,
				rudderAxis
			};

			struct Parameter
			{

				Parameter();

				//- Draft at mid
				marineLib::TM Tm;

				//- After perpendicular
				marineLib::APP App;

				//- Forward perpendicular
				marineLib::FPP Fpp;

				//- Middle perpendicular
				marineLib::MPP Mpp;

				//- Length between perpendiculars
				marineLib::LPP Lpp;

				//- Breadth Waterline
				marineLib::BWL Bwl;

				//- Waterline length
				marineLib::LWL Lwl;

				//- Forward Waterline
				marineLib::FWL Fwl;

				//- Aft Waterline
				marineLib::AWL Awl;

				//- Forward Underwater
				marineLib::FUW Fuw;

				//- Aft Underwater
				marineLib::AUW Auw;

				//- Length overall submerged
				marineLib::LOS Los;


				TNB_SERIALIZATION(TnbHydStatic_EXPORT);
			};


		private:

			/*Private Data*/

			std::shared_ptr<marineLib::Body_Wetted> theBody_;
			std::shared_ptr<Marine_Wave> theWave_;

			std::shared_ptr<Parameter> theParameters_;

			appMode theAppMode_;


			//- private functions


			TNB_SERIALIZATION(TnbHydStatic_EXPORT);

			// Calculate Auxiliaries

			TnbHydStatic_EXPORT void CalcTM();

			TnbHydStatic_EXPORT void CalcFUW();

			TnbHydStatic_EXPORT void CalcAUW();

			TnbHydStatic_EXPORT void CalcAWL();

			TnbHydStatic_EXPORT void CalcFWL();


			// Calculate Dimensions

			TnbHydStatic_EXPORT void CalcBWL();

			TnbHydStatic_EXPORT void CalcFPP();

			TnbHydStatic_EXPORT void CalcAPP(const Standard_Real theAxis);

			TnbHydStatic_EXPORT void CalcAPP();

			TnbHydStatic_EXPORT void CalcLPP();

			TnbHydStatic_EXPORT void CalcMPP();

			TnbHydStatic_EXPORT void CalcLWL();

			TnbHydStatic_EXPORT void CalcLOS();


			TnbHydStatic_EXPORT void AllocateMemory();

			auto& ChangeParameters()
			{
				return theParameters_;
			}

		public:

			TnbHydStatic_EXPORT Wetted();

			TnbHydStatic_EXPORT Wetted
			(
				const std::shared_ptr<marineLib::Body_Wetted>& theBody,
				const std::shared_ptr<Marine_Wave>& theWave
			);


			const auto& Body() const
			{
				return theBody_;
			}

			const auto& Wave() const
			{
				return theWave_;
			}

			const auto& Parameters() const
			{
				return theParameters_;
			}

			auto AppMode() const
			{
				return theAppMode_;
			}

			TnbHydStatic_EXPORT void Perform(const Standard_Real theRudderAxis = 0);

			TnbHydStatic_EXPORT void LoadBody
			(
				const std::shared_ptr<marineLib::Body_Wetted>& theBody
			);

			TnbHydStatic_EXPORT void LoadWave
			(
				const std::shared_ptr<Marine_Wave>& theWave
			);

			TnbHydStatic_EXPORT void SetAppMode(const appMode mode = appMode::Auto);
		};
	}
}

#endif // !_HydStatic_FormDim_Wetted_Header

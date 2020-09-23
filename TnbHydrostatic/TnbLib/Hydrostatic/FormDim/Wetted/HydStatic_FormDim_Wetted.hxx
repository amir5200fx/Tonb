#pragma once
#ifndef _HydStatic_FormDim_Wetted_Header
#define _HydStatic_FormDim_Wetted_Header

#include <Marine_VesselParams.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	namespace formDim
	{

		class Wetted
			: public Global_Done
		{

		public:

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
			};


		private:

			/*Private Data*/

			std::shared_ptr<marineLib::Body_Wetted> theBody_;

			std::shared_ptr<Parameter> theParameters_;

			appMode theAppMode_;


			//- private functions

			// Calculate Auxiliaries

			void CalcTM();

			void CalcFUW();

			void CalcAUW();

			void CalcAWL();

			void CalcFWL();


			// Calculate Dimensions

			void CalcBWL();

			void CalcFPP();

			void CalcAPP(const Standard_Real theAxis);

			void CalcAPP();

			void CalcLPP();

			void CalcMPP();

			void CalcLWL();

			void CalcLOS();


			void AllocateMemory();

			auto& ChangeParameters()
			{
				return theParameters_;
			}

		public:

			Wetted();

			Wetted
			(
				const std::shared_ptr<marineLib::Body_Wetted>& theBody
			);


			const auto& Body() const
			{
				return theBody_;
			}

			const auto& Parameters() const
			{
				return theParameters_;
			}

			auto AppMode() const
			{
				return theAppMode_;
			}

			void Perform(const Standard_Real theRudderAxis = 0);

			void LoadBody
			(
				const std::shared_ptr<marineLib::Body_Wetted>& theBody
			);

			void SetAppMode(const appMode mode = appMode::Auto);
		};
	}
}

#endif // !_HydStatic_FormDim_Wetted_Header

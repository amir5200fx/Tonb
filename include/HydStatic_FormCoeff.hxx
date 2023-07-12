#pragma once
#ifndef _HydStatic_FormCoeff_Header
#define _HydStatic_FormCoeff_Header

#include <Marine_BodiesFwd.hxx>
#include <Marine_VesselParams.hxx>
#include <HydStatic_FormDimsFwd.hxx>
#include <HydStatic_Module.hxx>
#include <Global_Done.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	namespace formCoeff
	{

		class Wetted
			: public Global_Done
		{

		public:

			static TnbHydStatic_EXPORT unsigned short verbose;

			struct Parameter
			{

				Parameter();

				//- Block coefficient
				marineLib::CB Cb;

				//- Displacement
				marineLib::DISPV Dispv;

				//- Displacement mass
				//marineLib::DISPM Dispm;

				//- Midship coefficient
				marineLib::CM Cm;

				//- Midship-section area
				marineLib::AM Am;

				//- Prismatic coefficient
				marineLib::CP Cp;

				//- Vertical Prismatic coefficient
				marineLib::CVP Cvp;

				//- Waterplane area
				marineLib::AW Aw;

				//- Waterplane-area coefficient
				marineLib::CWL Cwl;


				TNB_SERIALIZATION(TnbHydStatic_EXPORT);
			};

		private:

			/*Private Data*/

			std::shared_ptr<formDim::Wetted> theWeted_;

			std::shared_ptr<Parameter> theParameters_;


			//- private functions


			TNB_SERIALIZATION(TnbHydStatic_EXPORT);

			TnbHydStatic_EXPORT void CalcDISPV
			(
				const marineLib::Body_Wetted& theBody
			);

			TnbHydStatic_EXPORT void CalcCB
			(
				const marineLib::Body_Wetted& theBody
			);

			TnbHydStatic_EXPORT void CalcAM
			(
				const marineLib::Body_Wetted& theBody
			);

			TnbHydStatic_EXPORT void CalcCP();

			TnbHydStatic_EXPORT void CalcCM();

			TnbHydStatic_EXPORT void CalcAW
			(
				const marineLib::Body_Wetted& theBody
			);

			TnbHydStatic_EXPORT void CalcCWL();

			TnbHydStatic_EXPORT void CalcCVP();


			auto& ParametersRef()
			{
				return theParameters_;
			}

			TnbHydStatic_EXPORT void AllocateMemory();

		public:

			TnbHydStatic_EXPORT Wetted();

			TnbHydStatic_EXPORT Wetted
			(
				const std::shared_ptr<formDim::Wetted>& theForm
			);

			const auto& WettedFormDim() const
			{
				return theWeted_;
			}

			const auto& Parameters() const
			{
				return theParameters_;
			}

			TnbHydStatic_EXPORT void Perform();

			void LoadFormDim
			(
				const std::shared_ptr<formDim::Wetted>& theForm
			)
			{
				theWeted_ = theForm;
			}
		};
	}
}

#endif // !_HydStatic_FormCoeff_Header

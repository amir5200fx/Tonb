#pragma once
#ifndef _HydStatic_FormCoeff_Header
#define _HydStatic_FormCoeff_Header

#include <Marine_BodiesFwd.hxx>
#include <Marine_VesselParams.hxx>
#include <HydStatic_FormDimsFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	namespace formCoeff
	{

		class Wetted
			: public Global_Done
		{

		public:

			struct Parameter
			{

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
			};

		private:

			/*Private Data*/

			const std::shared_ptr<formDim::Wetted> theWeted_;

			std::shared_ptr<Parameter> theParameters_;

			//- private functions

			void CalcDISPV
			(
				const marineLib::Body_Wetted& theBody
			);

			void CalcCB
			(
				const marineLib::Body_Wetted& theBody
			);

			void CalcAM
			(
				const marineLib::Body_Wetted& theBody
			);

			void CalcCP();

			void CalcCM();

			void CalcAW
			(
				const marineLib::Body_Wetted& theBody
			);

			void CalcCWL();

			void CalcCVP();


			auto& ParametersRef()
			{
				return theParameters_;
			}

		public:

			Wetted
			(
				const std::shared_ptr<formDim::Wetted>& theForm
			)
				: theWeted_(theForm)
			{}

			const auto& WettedFormDim() const
			{
				return theWeted_;
			}

			const auto& Parameters() const
			{
				return theParameters_;
			}

			void Perform();
		};
	}
}

#endif // !_HydStatic_FormCoeff_Header

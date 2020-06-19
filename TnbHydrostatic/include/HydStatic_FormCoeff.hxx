#pragma once
#ifndef _HydStatic_FormCoeff_Header
#define _HydStatic_FormCoeff_Header

#include <Marine_BodiesFwd.hxx>
#include <Vessel_FormCoeff.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_FormDim;

	class HydStatic_FormCoeff
		: public Global_Done
		, public Vessel_FormCoeff_Parameters
	{

		/*Private Data*/

		std::shared_ptr<HydStatic_FormDim> theFormDim_;

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

	public:

		HydStatic_FormCoeff();

		HydStatic_FormCoeff
		(
			const std::shared_ptr<HydStatic_FormDim>& theFormDim
		);

		const auto& FormDim() const
		{
			return theFormDim_;
		}

		void Perform();

		void LoadFormDim
		(
			const std::shared_ptr<HydStatic_FormDim>& theFormDim
		)
		{
			theFormDim_ = theFormDim;
		}
	};
}

#endif // !_HydStatic_FormCoeff_Header

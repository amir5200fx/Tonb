#pragma once
#ifndef _HydStatic_FormDim_Header
#define _HydStatic_FormDim_Header

#include <Vessel_FormDim.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_WettedBody;

	class HydStatic_FormDim
		: public Global_Done
		, public Vessel_FormDim_Parameters
	{

		/*Private Data*/

		std::shared_ptr<Marine_WettedBody> theBody_;


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

		void CalcAPP();

		void CalcLPP();

		void CalcMPP();

		void CalcLWL();

		void CalcLOS();

	public:


		HydStatic_FormDim();

		HydStatic_FormDim(const std::shared_ptr<Marine_WettedBody>& theBody);


		const auto& Body() const
		{
			return theBody_;
		}

		void Perform();

		void LoadBody
		(
			const std::shared_ptr<Marine_WettedBody>& theBody
		)
		{
			theBody_ = theBody;
		}

	};
}

#endif // !_HydStatic_FormDim_Header

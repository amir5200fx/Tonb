#pragma once
#ifndef _PtdModel_BladeFormNo1_Pitch_Header
#define _PtdModel_BladeFormNo1_Pitch_Header

#include <PtdModel_BladeFormNo1.hxx>

namespace tnbLib
{

	namespace ptdModel
	{

		class BladeFormNo1_Pitch
			: public PtdModel_BladeFormNo1
		{

		public:

			enum class Parameters
			{
				rootPitch = 0,
				rootSteep,
				tipPitch,
				tipSteep
			};

			static TnbPtdModel_EXPORT word ROOT_PITCH;
			static TnbPtdModel_EXPORT word ROOT_STEEP;
			static TnbPtdModel_EXPORT word TIP_PITCH;
			static TnbPtdModel_EXPORT word TIP_STEEP;

		private:

			/*Private Data*/

			word theParameters_[4];


			//- private functions and operators

			TnbPtdModel_EXPORT void Init();

		public:

			//- default constructor

			BladeFormNo1_Pitch()
			{
				Init();
			}


			//- constructors


			//- public functions and operators

			TnbPtdModel_EXPORT Standard_Integer NbParameters() const override;

			TnbPtdModel_EXPORT word Parameter(const Standard_Integer theIndex) const override;
			inline word Parameter(const Parameters) const;

			TnbPtdModel_EXPORT std::shared_ptr<PtdModel_Form> CreateForm() const override;
			TnbPtdModel_EXPORT std::shared_ptr<PtdModel_BladeProfile> 
				CreateProfile
				(
					const std::shared_ptr<PtdModel_BladeGlobalPars>&,
					const std::shared_ptr<PtdModel_Form>&
				) const override;
		};
	}
}

#include <PtdModel_BladeFormNo1_PitchI.hxx>

#endif // !_PtdModel_BladeFormNo1_Pitch_Header

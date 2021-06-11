#pragma once
#ifndef _PtdModel_BladeFormNo1_Skew_Header
#define _PtdModel_BladeFormNo1_Skew_Header

#include <PtdModel_BladeFormMakerNo1.hxx>

namespace tnbLib
{

	namespace ptdModel
	{

		class BladeFormNo1_Skew
			: public PtdModel_BladeFormMakerNo1
		{

		public:

			enum class Parameters
			{
				rootSteep = 0,
				tipSkew,
				tipSteep
			};

			static TnbPtdModel_EXPORT word ROOT_STEEP;
			static TnbPtdModel_EXPORT word TIP_SKEW;
			static TnbPtdModel_EXPORT word TIP_STEEP;

		private:

			/*Private Data*/

			word theParameters_[3];

			TnbPtdModel_EXPORT void Init();

		public:

			static TnbPtdModel_EXPORT word TypeName_;

			//- default constructor

			BladeFormNo1_Skew()
			{
				Init();
			}


			//- constructors



			//- public functions and operators

			TnbPtdModel_EXPORT Standard_Integer NbParameters() const override;
			TnbPtdModel_EXPORT word GetTypeName() const override;

			TnbPtdModel_EXPORT word Parameter(const Standard_Integer theIndex) const override;
			inline word Parameter(const Parameters) const;

			TnbPtdModel_EXPORT std::shared_ptr<PtdModel_Form> CreateForm() const override;
			TnbPtdModel_EXPORT std::shared_ptr<PtdModel_Profile>
				CreateProfile
				(
					const std::shared_ptr<PtdModel_GlobalPars>&,
					const std::shared_ptr<PtdModel_Form>&
				) const override;
		};
	}
}

#include <PtdModel_BladeFormNo1_SkewI.hxx>

#endif // !_PtdModel_BladeFormNo1_Skew_Header

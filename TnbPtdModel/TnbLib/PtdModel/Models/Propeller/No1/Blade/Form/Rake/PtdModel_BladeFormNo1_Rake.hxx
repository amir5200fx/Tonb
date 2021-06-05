#pragma once
#ifndef _PtdModel_BladeFormNo1_Rake_Header
#define _PtdModel_BladeFormNo1_Rake_Header

#include <PtdModel_BladeFormMakerNo1.hxx>

namespace tnbLib
{

	namespace ptdModel
	{

		class BladeFormNo1_Rake
			: public PtdModel_BladeFormMakerNo1
		{

		public:

			enum class Parameters
			{
				tipRake = 0
			};

			static TnbPtdModel_EXPORT word TIP_RAKE;

		private:

			/*Private Data*/

			word theParameter_;

			//- private functions and operators

			TnbPtdModel_EXPORT void Init();


		public:

			//- default constructor

			BladeFormNo1_Rake()
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

#include <PtdModel_BladeFormNo1_RakeI.hxx>

#endif // !_PtdModel_BladeFormNo1_Rake_Header

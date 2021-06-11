#pragma once
#ifndef _PtdModel_BladeFormNo1_CamberLoc_Header
#define _PtdModel_BladeFormNo1_CamberLoc_Header

#include <PtdModel_BladeFormMakerNo1.hxx>

namespace tnbLib
{

	namespace ptdModel
	{

		class BladeFormNo1_CamberLoc
			: public PtdModel_BladeFormMakerNo1
		{

		public:

			enum class Parameters
			{
				maxCamberLoc = 0
			};

			static TnbPtdModel_EXPORT word MAX_CAMBER_LOC;

		private:

			/*Private Data*/

			word theParameter_;


			//- private functions and operators

			TnbPtdModel_EXPORT void Init();

		public:

			static TnbPtdModel_EXPORT word TypeName_;

			//- default constructor

			BladeFormNo1_CamberLoc()
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

#include <PtdModel_BladeFormNo1_CamberLocI.hxx>

#endif // !_PtdModel_BladeFormNo1_CamberLoc_Header
